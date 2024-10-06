#ifndef PMK_PUMPKIN_VIEW_H
#define PMK_PUMPKIN_VIEW_H

#include <view.h>

/**
 * @brief Структура данных для отображения тыквы в консоли.
 * Каждому состоянию соответствует пара {цвет, глиф}. 
 */
typedef struct pmk_pumpkin_view {
    pmk_view_cell_t empty, unripe, ripe; /**< empty->PMK_EMPTY, unripe->PMK_UNRIPE, ripe->PMK_RIPE */
} pmk_pumpkin_view_t;

#endif