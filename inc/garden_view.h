#ifndef PMK_GARDEN_VIEW_H
#define PMK_GARDEN_VIEW_H

#include <view.h>
#include <garden_model.h>

/**
 * @brief Структура для хранения данных об отображении поля с тыквами. 
 */
typedef struct pmk_garden_view {
    pmk_view_cell_t views[4]; /**< массив ячеек с данными для вывода, в котором каждый индекс соответствует значению pmk_garden_cell_state_t */
} pmk_garden_view_t;

/**
 * @brief Функция переноса данных о поле с тыквами на поле для отображения в консоль. 
 * @param field       - указатель на структуру поля для отображения 
 * @param garden      - структура поля с тыквами
 * @param garden_view - структура информации об отображении поля с тыквами
 */
void pmk_put_garden(pmk_view_field_t *field, pmk_garden_t garden, pmk_garden_view_t garden_view);

#endif