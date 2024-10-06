#ifndef PMK_PUMPKIN_VIEW_H
#define PMK_PUMPKIN_VIEW_H

#include <view.h>
#include <pumpkin_model.h>

/**
 * @brief Структура данных для отображения тыквы в консоли.
 * Каждому состоянию соответствует пара {цвет, глиф}. 
 */
typedef struct pmk_pumpkin_view {
    pmk_view_cell_t empty, unripe, ripe; /**< empty->PMK_EMPTY, unripe->PMK_UNRIPE, ripe->PMK_RIPE */
} pmk_pumpkin_view_t;

/**
 * @brief Функция преобразования состояния тыквы в ячейку отображения. 
 * @param state        - состояние тыквы
 * @param pumpkin_view - структура, содержащая ячейки для разных состояний тыквы
 * @return pmk_view_cell_t 
 */
pmk_view_cell_t cell_by_state(pmk_pumpkin_state_t state, pmk_pumpkin_view_t pumpkin_view);
/**
 * @brief Функция размещения тыкв на поле для отображения.
 * @param field        - указатель на структуру поля отображения
 * @param garden       - структура набора тыкв
 * @param pumpkin_view - структура отображения состояния тыкв
 */
void pmk_put_garden(pmk_view_field_t *field, pmk_garden_t garden, pmk_pumpkin_view_t pumpkin_view);

#endif