#ifndef WANBEIYU_HAL_H
#define WANBEIYU_HAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "compat.h"

typedef enum wanbeiyu_hal_gpio_state_t {
    WANBEIYU_HAL_GPIO_HI_Z,
    WANBEIYU_HAL_GPIO_LOW
} wanbeiyu_hal_gpio_state_t;

typedef struct wanbeiyu_hal_gpio_t {
    void (*set)(struct wanbeiyu_hal_gpio_t *, wanbeiyu_hal_gpio_state_t);
} wanbeiyu_hal_gpio_t;

void wanbeiyu_hal_gpio_set(wanbeiyu_hal_gpio_t *, wanbeiyu_hal_gpio_state_t);

typedef enum wanbeiyu_hal_idac_state_t {
    WANBEIYU_HAL_IDAC_SINK,
    WANBEIYU_HAL_IDAC_SOURCE
} wanbeiyu_hal_idac_state_t;

typedef struct wanbeiyu_hal_idac_t {
    void (*set)(struct wanbeiyu_hal_idac_t *, wanbeiyu_hal_idac_state_t,
                wanbeiyu_uint8_t);
} wanbeiyu_hal_idac_t;

void wanbeiyu_hal_idac_set(wanbeiyu_hal_idac_t *, wanbeiyu_hal_idac_state_t,
                           wanbeiyu_uint8_t);

typedef struct wanbeiyu_hal_rdac_t {
    void (*set)(struct wanbeiyu_hal_rdac_t *, wanbeiyu_uint16_t);
} wanbeiyu_hal_rdac_t;

void wanbeiyu_hal_rdac_set(wanbeiyu_hal_rdac_t *, wanbeiyu_uint16_t);

typedef enum wanbeiyu_hal_spst_switch_state_t {
    WANBEIYU_HAL_SPST_SWITCH_OFF,
    WANBEIYU_HAL_SPST_SWITCH_ON
} wanbeiyu_hal_spst_switch_state_t;

typedef struct wanbeiyu_hal_spst_switch_t {
    void (*set)(struct wanbeiyu_hal_spst_switch_t *,
                wanbeiyu_hal_spst_switch_state_t);
} wanbeiyu_hal_spst_switch_t;

void wanbeiyu_hal_spst_switch_set(wanbeiyu_hal_spst_switch_t *,
                                  wanbeiyu_hal_spst_switch_state_t);

typedef struct wanbeiyu_hal_board_t {
    wanbeiyu_hal_gpio_t *a;
    wanbeiyu_hal_gpio_t *b;
    wanbeiyu_hal_gpio_t *x;
    wanbeiyu_hal_gpio_t *y;
    wanbeiyu_hal_gpio_t *l;
    wanbeiyu_hal_gpio_t *zl;
    wanbeiyu_hal_gpio_t *r;
    wanbeiyu_hal_gpio_t *zr;
    wanbeiyu_hal_gpio_t *start;
    wanbeiyu_hal_gpio_t *select;
    wanbeiyu_hal_gpio_t *home;
    wanbeiyu_hal_gpio_t *power;

    wanbeiyu_hal_gpio_t *up;
    wanbeiyu_hal_gpio_t *right;
    wanbeiyu_hal_gpio_t *down;
    wanbeiyu_hal_gpio_t *left;

    wanbeiyu_hal_idac_t *cpx;
    wanbeiyu_hal_idac_t *cpy;
    wanbeiyu_hal_idac_t *cs2;
    wanbeiyu_hal_idac_t *cs4;

    wanbeiyu_hal_rdac_t *tsx;
    wanbeiyu_hal_rdac_t *tsy;
    wanbeiyu_hal_spst_switch_t *tssw;
} wanbeiyu_hal_board_t;

#ifdef __cplusplus
}
#endif

#endif /* WANBEIYU_HAL_H */