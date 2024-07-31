#include <wanbeiyu.h>

#include "internal.h"

void wanbeiyu_hal_gpio_set(wanbeiyu_hal_gpio_t *gpio,
                           wanbeiyu_hal_gpio_state_t state) {
    if (gpio == NULL || /**/
        !WITHIN(state, WANBEIYU_HAL_GPIO_HI_Z, WANBEIYU_HAL_GPIO_LOW)) {
        return;
    }
    gpio->set(gpio, state);
}

void wanbeiyu_hal_idac_set(wanbeiyu_hal_idac_t *idac,
                           wanbeiyu_hal_idac_state_t state,
                           wanbeiyu_uint8_t value) {
    if (idac == NULL || /**/
        !WITHIN(state, WANBEIYU_HAL_IDAC_SINK, WANBEIYU_HAL_IDAC_SOURCE)) {
        return;
    }
    idac->set(idac, state, value);
}

void wanbeiyu_hal_rdac_set(wanbeiyu_hal_rdac_t *rdac, wanbeiyu_uint16_t value) {
    if (rdac == NULL) {
        return;
    }
    rdac->set(rdac, value);
}

void wanbeiyu_hal_spst_switch_set(wanbeiyu_hal_spst_switch_t *sw,
                                  wanbeiyu_hal_spst_switch_state_t state) {
    if (sw == NULL || /**/
        !WITHIN(state, WANBEIYU_HAL_SPST_SWITCH_OFF,
                WANBEIYU_HAL_SPST_SWITCH_ON)) {
        return;
    }
    sw->set(sw, state);
}
