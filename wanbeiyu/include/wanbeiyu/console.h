#ifndef WANBEIYU_CONSOLE_H
#define WANBEIYU_CONSOLE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "hal.h"

typedef enum wanbeiyu_button_state_t {
    WANBEIYU_BUTTON_RELEASE,
    WANBEIYU_BUTTON_HOLD
} wanbeiyu_button_state_t;

typedef struct wanbeiyu_button_t {
    wanbeiyu_hal_gpio_t *gpio;
} wanbeiyu_button_t;

void wanbeiyu_button_set(wanbeiyu_button_t *, wanbeiyu_button_state_t);
void wanbeiyu_button_init(wanbeiyu_button_t *, wanbeiyu_hal_gpio_t *);

typedef enum wanbeiyu_d_pad_state_t {
    WANBEIYU_D_PAD_RELEASE = 0,
    WANBEIYU_D_PAD_LEFT = 1,
    WANBEIYU_D_PAD_DOWN = 2,
    WANBEIYU_D_PAD_RIGHT = 4,
    WANBEIYU_D_PAD_UP = 8
} wanbeiyu_d_pad_state_t;

typedef struct wanbeiyu_d_pad_t {
    wanbeiyu_button_t up;
    wanbeiyu_button_t right;
    wanbeiyu_button_t down;
    wanbeiyu_button_t left;
} wanbeiyu_d_pad_t;

void wanbeiyu_d_pad_set(wanbeiyu_d_pad_t *, wanbeiyu_d_pad_state_t);
void wanbeiyu_d_pad_init(wanbeiyu_d_pad_t *, wanbeiyu_hal_gpio_t *,
                         wanbeiyu_hal_gpio_t *, wanbeiyu_hal_gpio_t *,
                         wanbeiyu_hal_gpio_t *);

typedef struct wanbeiyu_analog_stick_state_t {
    wanbeiyu_uint8_t x;
    wanbeiyu_uint8_t y;
} wanbeiyu_analog_stick_state_t;

typedef struct wanbeiyu_analog_stick_t {
    wanbeiyu_hal_idac_t *cpx_cs2;
    wanbeiyu_hal_idac_t *cpy_cs4;
} wanbeiyu_analog_stick_t;

void wanbeiyu_circle_pad_set(wanbeiyu_analog_stick_t *,
                             wanbeiyu_analog_stick_state_t *);
void wanbeiyu_circle_pad_init(wanbeiyu_analog_stick_t *, wanbeiyu_hal_idac_t *,
                              wanbeiyu_hal_idac_t *);
void wanbeiyu_c_stick_set(wanbeiyu_analog_stick_t *,
                          wanbeiyu_analog_stick_state_t *);
void wanbeiyu_c_stick_init(wanbeiyu_analog_stick_t *, wanbeiyu_hal_idac_t *,
                           wanbeiyu_hal_idac_t *);

#define WANBEIYU_TOUCH_SCREEN_X_MAX ((wanbeiyu_uint16_t)319)
#define WANBEIYU_TOUCH_SCREEN_Y_MAX ((wanbeiyu_uint8_t)239)

typedef struct wanbeiyu_touch_screen_state_t {
    wanbeiyu_bool_t hold;
    wanbeiyu_uint16_t x;
    wanbeiyu_uint8_t y;
} wanbeiyu_touch_screen_state_t;

typedef struct wanbeiyu_touch_screen_t {
    wanbeiyu_hal_rdac_t *x;
    wanbeiyu_hal_rdac_t *y;
    wanbeiyu_hal_spst_switch_t *sw;
} wanbeiyu_touch_screen_t;

void wanbeiyu_touch_screen_set(wanbeiyu_touch_screen_t *,
                               wanbeiyu_touch_screen_state_t *);
void wanbeiyu_touch_screen_init(wanbeiyu_touch_screen_t *,
                                wanbeiyu_hal_rdac_t *, wanbeiyu_hal_rdac_t *,
                                wanbeiyu_hal_spst_switch_t *);

typedef struct wanbeiyu_console_state_t {
    wanbeiyu_button_state_t a;
    wanbeiyu_button_state_t b;
    wanbeiyu_button_state_t x;
    wanbeiyu_button_state_t y;
    wanbeiyu_button_state_t l;
    wanbeiyu_button_state_t zl;
    wanbeiyu_button_state_t r;
    wanbeiyu_button_state_t zr;
    wanbeiyu_button_state_t start;
    wanbeiyu_button_state_t select;
    wanbeiyu_button_state_t home;
    wanbeiyu_button_state_t power;

    wanbeiyu_d_pad_state_t d_pad;

    wanbeiyu_analog_stick_state_t circle_pad;
    wanbeiyu_analog_stick_state_t c_stick;

    wanbeiyu_touch_screen_state_t touch_screen;
} wanbeiyu_console_state_t;

typedef struct wanbeiyu_console_t {
    wanbeiyu_button_t a;
    wanbeiyu_button_t b;
    wanbeiyu_button_t x;
    wanbeiyu_button_t y;
    wanbeiyu_button_t l;
    wanbeiyu_button_t zl;
    wanbeiyu_button_t r;
    wanbeiyu_button_t zr;
    wanbeiyu_button_t start;
    wanbeiyu_button_t select;
    wanbeiyu_button_t home;
    wanbeiyu_button_t power;

    wanbeiyu_d_pad_t d_pad;

    wanbeiyu_analog_stick_t circle_pad;
    wanbeiyu_analog_stick_t c_stick;

    wanbeiyu_touch_screen_t touch_screen;
} wanbeiyu_console_t;

void wanbeiyu_console_set(wanbeiyu_console_t *, wanbeiyu_console_state_t *);
wanbeiyu_bool_t wanbeiyu_console_init(wanbeiyu_console_t *,
                                      wanbeiyu_hal_board_t *);

#ifdef __cplusplus
}
#endif

#endif /* WANBEIYU_CONSOLE_H */