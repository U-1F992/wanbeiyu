#include <wanbeiyu.h>

#include <assert.h>
#include <stdio.h>

typedef struct test_gpio_t {
    wanbeiyu_hal_gpio_t base;
    int id;
    wanbeiyu_hal_gpio_state_t state;
} test_gpio_t;

void test_gpio_set(wanbeiyu_hal_gpio_t *base, wanbeiyu_hal_gpio_state_t state) {
    test_gpio_t *gpio = (test_gpio_t *)base;
    assert(gpio != NULL);
    gpio->state = state;
}

wanbeiyu_hal_gpio_t *test_gpio_init(test_gpio_t *gpio, int id) {
    assert(gpio != NULL);
    assert(0 <= id && id <= 16);
    gpio->base.set = test_gpio_set;
    gpio->id = id;
    return &(gpio->base);
}

typedef struct test_idac_t {
    wanbeiyu_hal_idac_t base;
    int id;
    wanbeiyu_hal_idac_state_t state;
    wanbeiyu_uint8_t value;
} test_idac_t;

void test_idac_set(wanbeiyu_hal_idac_t *base, wanbeiyu_hal_idac_state_t state,
                   wanbeiyu_uint8_t value) {
    test_idac_t *idac = (test_idac_t *)base;
    assert(idac != NULL);
    idac->state = state;
    idac->value = value;
}

wanbeiyu_hal_idac_t *test_idac_init(test_idac_t *idac, int id) {
    assert(idac != NULL);
    assert(0 <= id && id <= 4);
    idac->base.set = test_idac_set;
    idac->id = id;
    return &(idac->base);
}

typedef struct test_rdac_t {
    wanbeiyu_hal_rdac_t base;
    int id;
    wanbeiyu_uint16_t value;
} test_rdac_t;

void test_rdac_set(wanbeiyu_hal_rdac_t *base, wanbeiyu_uint16_t value) {
    test_rdac_t *rdac = (test_rdac_t *)base;
    assert(rdac != NULL);
    rdac->value = value;
}

wanbeiyu_hal_rdac_t *test_rdac_init(test_rdac_t *rdac, int id) {
    assert(rdac != NULL);
    assert(0 <= id && id <= 2);
    rdac->base.set = test_rdac_set;
    rdac->id = id;
    return &(rdac->base);
}

typedef struct test_spst_switch_t {
    wanbeiyu_hal_spst_switch_t base;
    wanbeiyu_hal_spst_switch_state_t state;
} test_spst_switch_t;

void test_spst_switch_set(wanbeiyu_hal_spst_switch_t *base,
                          wanbeiyu_hal_spst_switch_state_t state) {
    test_spst_switch_t *sw = (test_spst_switch_t *)base;
    assert(sw != NULL);
    sw->state = state;
}

wanbeiyu_hal_spst_switch_t *test_spst_switch_init(test_spst_switch_t *sw) {
    assert(sw != NULL);
    sw->base.set = test_spst_switch_set;
    return &(sw->base);
}

int main(void) {
    test_gpio_t gpio[16];
    test_idac_t idac[4];
    test_rdac_t rdac[2];
    test_spst_switch_t sw;

    wanbeiyu_hal_board_t board;
    wanbeiyu_console_t console;
    wanbeiyu_console_state_t state;

    board.a = test_gpio_init(&(gpio[0]), 0);
    board.b = test_gpio_init(&(gpio[1]), 1);
    board.x = test_gpio_init(&(gpio[2]), 2);
    board.y = test_gpio_init(&(gpio[3]), 3);
    board.l = test_gpio_init(&(gpio[4]), 4);
    board.zl = test_gpio_init(&(gpio[5]), 5);
    board.r = test_gpio_init(&(gpio[6]), 6);
    board.zr = test_gpio_init(&(gpio[7]), 7);
    board.start = test_gpio_init(&(gpio[8]), 8);
    board.select = test_gpio_init(&(gpio[9]), 9);
    board.home = test_gpio_init(&(gpio[10]), 10);
    board.power = test_gpio_init(&(gpio[11]), 11);
    board.up = test_gpio_init(&(gpio[12]), 12);
    board.right = test_gpio_init(&(gpio[13]), 13);
    board.down = test_gpio_init(&(gpio[14]), 14);
    board.left = test_gpio_init(&(gpio[15]), 15);

    board.cpx = test_idac_init(&(idac[0]), 0);
    board.cpy = test_idac_init(&(idac[1]), 1);
    board.cs2 = test_idac_init(&(idac[2]), 2);
    board.cs4 = test_idac_init(&(idac[3]), 3);

    board.tsx = test_rdac_init(&(rdac[0]), 0);
    board.tsy = test_rdac_init(&(rdac[1]), 1);
    board.tssw = test_spst_switch_init(&sw);

    assert(wanbeiyu_console_init(&console, &board));

    state.a = WANBEIYU_BUTTON_HOLD;
    state.b = WANBEIYU_BUTTON_RELEASE;
    state.x = WANBEIYU_BUTTON_HOLD;
    state.y = WANBEIYU_BUTTON_RELEASE;
    state.l = WANBEIYU_BUTTON_HOLD;
    state.zl = WANBEIYU_BUTTON_RELEASE;
    state.r = WANBEIYU_BUTTON_HOLD;
    state.zr = WANBEIYU_BUTTON_RELEASE;
    state.start = WANBEIYU_BUTTON_HOLD;
    state.select = WANBEIYU_BUTTON_RELEASE;
    state.home = WANBEIYU_BUTTON_HOLD;
    state.power = WANBEIYU_BUTTON_RELEASE;

    state.d_pad = WANBEIYU_D_PAD_UP;

    state.circle_pad.x = 0;
    state.circle_pad.y = 128;
    state.c_stick.x = 128;
    state.c_stick.y = 255;

    state.touch_screen.hold = WANBEIYU_TRUE;
    state.touch_screen.x = 0;
    state.touch_screen.y = WANBEIYU_TOUCH_SCREEN_Y_MAX;

    wanbeiyu_console_set(&console, &state);

    assert(WANBEIYU_HAL_GPIO_LOW == gpio[0].state);
    assert(WANBEIYU_HAL_GPIO_HI_Z == gpio[1].state);
    assert(WANBEIYU_HAL_GPIO_LOW == gpio[2].state);
    assert(WANBEIYU_HAL_GPIO_HI_Z == gpio[3].state);
    assert(WANBEIYU_HAL_GPIO_LOW == gpio[4].state);
    assert(WANBEIYU_HAL_GPIO_HI_Z == gpio[5].state);
    assert(WANBEIYU_HAL_GPIO_LOW == gpio[6].state);
    assert(WANBEIYU_HAL_GPIO_HI_Z == gpio[7].state);
    assert(WANBEIYU_HAL_GPIO_LOW == gpio[8].state);
    assert(WANBEIYU_HAL_GPIO_HI_Z == gpio[9].state);
    assert(WANBEIYU_HAL_GPIO_LOW == gpio[10].state);
    assert(WANBEIYU_HAL_GPIO_HI_Z == gpio[11].state);

    return 0;
}