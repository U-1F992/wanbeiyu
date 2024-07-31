#include <wanbeiyu.h>

#include "internal.h"

void wanbeiyu_button_set(wanbeiyu_button_t *btn,
                         wanbeiyu_button_state_t state) {
    if (btn == NULL || /**/
        !WITHIN(state, WANBEIYU_BUTTON_RELEASE, WANBEIYU_BUTTON_HOLD)) {
        return;
    }
    wanbeiyu_hal_gpio_set(btn->gpio, (wanbeiyu_hal_gpio_state_t)state);
}

void wanbeiyu_button_init(wanbeiyu_button_t *btn, wanbeiyu_hal_gpio_t *gpio) {
    if (btn == NULL) {
        return;
    }
    btn->gpio = gpio;
    wanbeiyu_button_set(btn, WANBEIYU_BUTTON_RELEASE);
}

void wanbeiyu_d_pad_set(wanbeiyu_d_pad_t *d_pad, wanbeiyu_d_pad_state_t state) {

    if (d_pad == NULL || /**/
        !WITHIN(state, WANBEIYU_D_PAD_RELEASE,
                WANBEIYU_D_PAD_UP | WANBEIYU_D_PAD_RIGHT | WANBEIYU_D_PAD_DOWN |
                    WANBEIYU_D_PAD_LEFT)) {
        return;
    }
    wanbeiyu_button_set(&(d_pad->left), (wanbeiyu_button_state_t)(state & 1));
    wanbeiyu_button_set(&(d_pad->down),
                        (wanbeiyu_button_state_t)((state >> 1) & 1));
    wanbeiyu_button_set(&(d_pad->right),
                        (wanbeiyu_button_state_t)((state >> 2) & 1));
    wanbeiyu_button_set(&(d_pad->up),
                        (wanbeiyu_button_state_t)((state >> 3) & 1));
}

void wanbeiyu_d_pad_init(wanbeiyu_d_pad_t *d_pad, wanbeiyu_hal_gpio_t *up,
                         wanbeiyu_hal_gpio_t *right, wanbeiyu_hal_gpio_t *down,
                         wanbeiyu_hal_gpio_t *left) {
    if (d_pad == NULL) {
        return;
    }
    wanbeiyu_button_init(&(d_pad->up), up);
    wanbeiyu_button_init(&(d_pad->right), right);
    wanbeiyu_button_init(&(d_pad->down), down);
    wanbeiyu_button_init(&(d_pad->left), left);
    wanbeiyu_d_pad_set(d_pad, WANBEIYU_D_PAD_RELEASE);
}

void wanbeiyu_circle_pad_set(wanbeiyu_analog_stick_t *cp,
                             wanbeiyu_analog_stick_state_t *state) {
    /**
     *          CPY-
     *           |
     *           |
     * CPX- -----+----- CPX+
     *           |
     *           |
     *          CPY+
     * +: Source
     * -: Sink
     */
    if (cp == NULL || /**/
        state == NULL) {
        return;
    }

    if (state->x >= 128) {
        wanbeiyu_hal_idac_set(cp->cpx_cs2, WANBEIYU_HAL_IDAC_SOURCE,
                              REMAP_0_127_TO_0_255(state->x - 128));
    } else {
        wanbeiyu_hal_idac_set(cp->cpx_cs2, WANBEIYU_HAL_IDAC_SINK,
                              REMAP_0_127_TO_0_255(127 - state->x));
    }

    if (state->y >= 128) {
        wanbeiyu_hal_idac_set(cp->cpy_cs4, WANBEIYU_HAL_IDAC_SINK,
                              REMAP_0_127_TO_0_255(state->y - 128));
    } else {
        wanbeiyu_hal_idac_set(cp->cpy_cs4, WANBEIYU_HAL_IDAC_SOURCE,
                              REMAP_0_127_TO_0_255(127 - state->y));
    }
}

void wanbeiyu_circle_pad_init(wanbeiyu_analog_stick_t *cp,
                              wanbeiyu_hal_idac_t *x, wanbeiyu_hal_idac_t *y) {
    wanbeiyu_analog_stick_state_t state;
    state.x = 128;
    state.y = 128;

    if (cp == NULL) {
        return;
    }
    cp->cpx_cs2 = x;
    cp->cpy_cs4 = y;
    wanbeiyu_circle_pad_set(cp, &state);
}

void wanbeiyu_c_stick_set(wanbeiyu_analog_stick_t *cs,
                          wanbeiyu_analog_stick_state_t *state) {
    /**
     *     CS4+     CS2+
     *       \_     _/
     *         \_ _/
     *          _X_
     *        _/   \_
     *       /       \
     *     CS2-     CS4-
     * +: Source
     * -: Sink
     *
     * CS2: y=x
     * CS4: y=-x+255
     *
     * cs2 = SIGNED_DISTANCE(CS4) / DISTANCE_MAX * UINT8_MAX
     * cs4 = SIGNED_DISTANCE(CS2) / DISTANCE_MAX * UINT8_MAX
     *
     * SIGNED_DISTANCE=(-a*x+y-b)/sqrt(a^2+1)
     * - A positive value indicates the point is above the line.
     * - A negative value indicates the point is below the line.
     * While a=1,-1 thus sqrt(a^2+1) is always sqrt(2).
     *
     * DISTANCE_MAX=UINT8_MAX/2*sqrt(2)
     *
     * ((-a*x+y-b)/sqrt(2)) / (UINT8_MAX/2*sqrt(2)) * UINT8_MAX
     * = -a*x+y-b
     */
    wanbeiyu_int_t cs2;
    wanbeiyu_int_t cs4;

    if (cs == NULL || /**/
        state == NULL) {
        return;
    }

    cs2 = state->x + state->y - 255;
    cs4 = -(state->x) + state->y;
    if (cs2 >= 0) {
        wanbeiyu_hal_idac_set(cs->cpx_cs2, WANBEIYU_HAL_IDAC_SOURCE,
                              (wanbeiyu_uint8_t)cs2);
    } else {
        wanbeiyu_hal_idac_set(cs->cpx_cs2, WANBEIYU_HAL_IDAC_SINK,
                              (wanbeiyu_uint8_t)(-cs2));
    }
    if (cs4 >= 0) {
        wanbeiyu_hal_idac_set(cs->cpy_cs4, WANBEIYU_HAL_IDAC_SOURCE,
                              (wanbeiyu_uint8_t)cs4);
    } else {
        wanbeiyu_hal_idac_set(cs->cpy_cs4, WANBEIYU_HAL_IDAC_SINK,
                              (wanbeiyu_uint8_t)(-cs4));
    }
}

void wanbeiyu_c_stick_init(wanbeiyu_analog_stick_t *cs,
                           wanbeiyu_hal_idac_t *cs2, wanbeiyu_hal_idac_t *cs4) {
    wanbeiyu_analog_stick_state_t state;
    state.x = 128;
    state.y = 128;

    if (cs == NULL) {
        return;
    }
    cs->cpx_cs2 = cs2;
    cs->cpy_cs4 = cs4;
    wanbeiyu_circle_pad_set(cs, &state);
}

void wanbeiyu_touch_screen_set(wanbeiyu_touch_screen_t *ts,
                               wanbeiyu_touch_screen_state_t *state) {
    if (ts == NULL || /**/
        state == NULL) {
        return;
    }

    state->x = state->x <= WANBEIYU_TOUCH_SCREEN_X_MAX
                   ? state->x
                   : WANBEIYU_TOUCH_SCREEN_X_MAX;
    state->y = state->y <= WANBEIYU_TOUCH_SCREEN_Y_MAX
                   ? state->y
                   : WANBEIYU_TOUCH_SCREEN_Y_MAX;

    wanbeiyu_hal_rdac_set(ts->x, REMAP_0_319_TO_0_65535(state->x));
    wanbeiyu_hal_rdac_set(ts->y, REMAP_0_239_TO_0_65535(state->y));
    wanbeiyu_hal_spst_switch_set(
        ts->sw, (wanbeiyu_hal_spst_switch_state_t)(!!(state->hold)));
}

void wanbeiyu_touch_screen_init(wanbeiyu_touch_screen_t *ts,
                                wanbeiyu_hal_rdac_t *x, wanbeiyu_hal_rdac_t *y,
                                wanbeiyu_hal_spst_switch_t *sw) {
    wanbeiyu_touch_screen_state_t state;
    state.hold = WANBEIYU_FALSE;
    state.x = 0;
    state.y = 0;

    if (ts == NULL) {
        return;
    }
    ts->x = x;
    ts->y = y;
    ts->sw = sw;
    wanbeiyu_touch_screen_set(ts, &state);
}

wanbeiyu_bool_t wanbeiyu_console_init(wanbeiyu_console_t *console,
                                      wanbeiyu_hal_board_t *board) {
    if (console == NULL || /**/
        board == NULL) {
        return WANBEIYU_FALSE;
    }

    wanbeiyu_button_init(&(console->a), board->a);
    wanbeiyu_button_init(&(console->b), board->b);
    wanbeiyu_button_init(&(console->x), board->x);
    wanbeiyu_button_init(&(console->y), board->y);
    wanbeiyu_button_init(&(console->l), board->l);
    wanbeiyu_button_init(&(console->zl), board->zl);
    wanbeiyu_button_init(&(console->r), board->r);
    wanbeiyu_button_init(&(console->zr), board->zr);
    wanbeiyu_button_init(&(console->start), board->start);
    wanbeiyu_button_init(&(console->select), board->select);
    wanbeiyu_button_init(&(console->home), board->home);
    wanbeiyu_button_init(&(console->power), board->power);

    wanbeiyu_d_pad_init(&(console->d_pad), board->up, board->right, board->down,
                        board->left);

    wanbeiyu_circle_pad_init(&(console->circle_pad), board->cpx, board->cpy);
    wanbeiyu_c_stick_init(&(console->c_stick), board->cs2, board->cs4);

    wanbeiyu_touch_screen_init(&(console->touch_screen), board->tsx, board->tsy,
                               board->tssw);

    return WANBEIYU_TRUE;
}

void wanbeiyu_console_set(wanbeiyu_console_t *console,
                          wanbeiyu_console_state_t *state) {
    if (console == NULL || /**/
        state == NULL) {
        return;
    }

    wanbeiyu_button_set(&(console->a), state->a);
    wanbeiyu_button_set(&(console->b), state->b);
    wanbeiyu_button_set(&(console->x), state->x);
    wanbeiyu_button_set(&(console->y), state->y);
    wanbeiyu_button_set(&(console->l), state->l);
    wanbeiyu_button_set(&(console->zl), state->zl);
    wanbeiyu_button_set(&(console->r), state->r);
    wanbeiyu_button_set(&(console->zr), state->zr);
    wanbeiyu_button_set(&(console->start), state->start);
    wanbeiyu_button_set(&(console->select), state->select);
    wanbeiyu_button_set(&(console->home), state->home);
    wanbeiyu_button_set(&(console->power), state->power);

    wanbeiyu_d_pad_set(&(console->d_pad), state->d_pad);

    wanbeiyu_circle_pad_set(&(console->circle_pad), &(state->circle_pad));
    wanbeiyu_c_stick_set(&(console->c_stick), &(state->c_stick));

    wanbeiyu_touch_screen_set(&(console->touch_screen), &(state->touch_screen));
}
