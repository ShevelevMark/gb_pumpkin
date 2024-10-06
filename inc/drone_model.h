#ifndef PMK_DRONE_MODEL_H
#define PMK_DRONE_MODEL_H

#include <stdbool.h>

/**
 * @brief Структура моделирует тележки. 
 */
typedef struct pmk_cart {
    unsigned row_pos, col_pos; /**< положение тележки на поле */
    bool is_empty; /**< является ли тележка пустой */
} pmk_cart_t;

/**
 * @brief Структура моделирует дрон с тележками.  
 */
typedef struct pmk_drone {
    unsigned row_pos, col_pos; /**< положение дрона */
    int row_dir, col_dir;      /**< скорость дрона, направление перемещения дрона */
    unsigned carts_size;       /**< количество тележек, прицепленных к дрону */
    pmk_cart_t *carts;         /**< указатель на массив тележек */
} pmk_drone_t;

/**
 * @brief Функция создания нового дрона с набором тележек.
 * Функция создаёт нового дрона в определённой позиции с нулевой скоростью.
 * Функция выделяет память под @param carts_size количество тележек.
 * Если выделить память не удаётся, то @param errcode перезаписывается в 1.
 * Если количество тележек равно нулю, то память не выделяется.
 * В случае успеха @param errcode перезаписывается в 0.
 * Если выделить память не удаётся или количество тележек равно нулю,
 * поле carts получает значение NULL.
 * 
 * @param row_pos     - ряд, в котором находится дрон 
 * @param col_pos     - колонка, в котором находится дрон
 * @param carts_size  - количество тележек
 * @param errcode     - указатель на целое число, в которое записывается код ошибки
 * @return pmk_drone_t структура дрона 
 */
pmk_drone_t pmk_make_drone(unsigned row_pos, unsigned col_pos, unsigned carts_size, int *errcode);

/**
 * @brief Функция удаления памяти, выделенной под тележки.
 * Функция удаляет память выделенную под тележки, записывает 0 в 
 * поле carts_size и NULL в поле carts. 
 * 
 * @param drone указатель на структуру дрона 
 */
void pmk_delete_drone(pmk_drone_t *drone);

#endif