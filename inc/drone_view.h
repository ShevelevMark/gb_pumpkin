#ifndef PMK_DRONE_VIEW_H
#define PMK_DRONE_VIEW_H

#include <view.h>
#include <drone_model.h>

/**
 * @brief Структура для хранения данных об отображении дрона в консоли.
 * Структура хранит три пары {цвет, глиф}: для дрона, для пустой тележки,
 * для заполненной тележки.
 */
typedef struct pmk_drone_view {
    pmk_view_cell_t drone, empty_cart, full_cart;
} pmk_drone_view_t;

/**
 * @brief Функция для размещения на поле отображения символов дрона с тележками. 
 * 
 * @param field       - указатель на поле отображения 
 * @param drone       - структура дрона
 * @param drone_view  - структура с данными для отображения
 */
void pmk_put_drone(pmk_view_field_t *field, pmk_drone_t drone, pmk_drone_view_t drone_view);

#endif