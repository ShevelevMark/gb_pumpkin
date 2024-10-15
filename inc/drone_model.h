#ifndef PMK_DRONE_MODEL_H
#define PMK_DRONE_MODEL_H

#include <utility.h>

#include <stdbool.h>

/**
 * @brief Структура моделирует тележки. 
 */
typedef struct pmk_cart {
    pmk_position_t pos; /**< положение тележки на поле */
    bool is_empty;      /**< является ли тележка пустой */
} pmk_cart_t;

/**
 * @brief Предварительная декларация структуры дрона, чтобы мы могли объявить тип указателя на функцию работы дрона
 */
struct pmk_drone;

/**
 * @brief Объявляем тип указателя на функцию, которая будет двигать дрона.
 * С каждым дроном связана некоторая функция, которая получает на вход 
 * указатель на структуру дрона и некоторый произвольный контекст.
 * Функция вызывается, чтобы дрон производил работу.
 */
typedef void (*pmk_drone_advance_t)(struct pmk_drone *, void *context);

/**
 * @brief Структура моделирует дрон с тележками.  
 */
typedef struct pmk_drone {
    pmk_position_t pos;           /**< положение дрона */
    unsigned carts_size;          /**< количество тележек, прицепленных к дрону */
    pmk_cart_t *carts;            /**< указатель на массив тележек */
    pmk_drone_advance_t advance;  /**< указатель на функцию работы дрона */
    void *advance_context;        /**< дополнительное окружение для функции работы дрона */
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
 * @param pos                      - начальное положение дрона (головы поезда тележек) 
 * @param carts_size               - количество тележек
 * @param advance_strategy         - указатель на функцию работы дрона, может быть NULL
 * @param advance_strategy_context - указатель на контекст функции работы дрона, может быть NULL
 * @param errcode                  - указатель на целое число, в которое записывается код ошибки
 * @return pmk_drone_t структура дрона 
 */
pmk_drone_t pmk_make_drone(pmk_position_t init_pos, unsigned carts_size, pmk_drone_advance_t advance_strategy, void *advance_strategy_context, int *errcode);

/**
 * @brief Функция удаления памяти, выделенной под тележки.
 * Функция удаляет память выделенную под тележки, записывает 0 в 
 * поле carts_size и NULL в поле carts. 
 * 
 * @param drone указатель на структуру дрона 
 */
void pmk_delete_drone(pmk_drone_t *drone);

#endif