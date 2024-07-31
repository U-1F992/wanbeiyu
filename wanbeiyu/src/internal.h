#ifndef WANBEIYU_INTERNAL_H
#define WANBEIYU_INTERNAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <wanbeiyu.h>

#define WITHIN(val, min, max)                                                  \
    ((wanbeiyu_bool_t)(!!((val) >= (min) && (val) <= (max))))

#define REMAP_0_127_TO_0_255(val)                                              \
    ((wanbeiyu_uint8_t)((val) > 127 ? WANBEIYU_UINT8_MAX                       \
                                    : ((((wanbeiyu_uint8_t)(val)) *            \
                                            WANBEIYU_UINT8_MAX +               \
                                        127 / 2) /                             \
                                       127)))

#define REMAP_0_319_TO_0_65535(val)                                            \
    ((wanbeiyu_uint16_t)((val) > 319 ? WANBEIYU_UINT16_MAX                     \
                                     : ((((wanbeiyu_uint16_t)(val)) *          \
                                             WANBEIYU_UINT16_MAX +             \
                                         319 / 2) /                            \
                                        319)))

#define REMAP_0_239_TO_0_65535(val)                                            \
    ((wanbeiyu_uint16_t)((val) > 239 ? WANBEIYU_UINT16_MAX                     \
                                     : ((((wanbeiyu_uint16_t)(val)) *          \
                                             WANBEIYU_UINT16_MAX +             \
                                         239 / 2) /                            \
                                        239)))

#ifdef __cplusplus
}
#endif

#endif /* WANBEIYU_INTERNAL_H */