#ifndef PMK_PUMPKIN_MODEL_H
#define PMK_PUMPKIN_MODEL_H

/**
 * @brief Перечисление состояний грядки с тыквой.
 * PMK_EMPTY  - пустая грядка
 * PMK_UNRIPE - незрелая тыква 
 * PMK_RIPE   - зрелая тыква
 */
typedef enum pmk_pumpkin_state {PMK_EMPTY = 0, PMK_UNRIPE, PMK_RIPE} pmk_pumpkin_state_t;

/**
 * @brief Структура тыквы на грядке. 
 */
typedef struct pmk_pumpkin {
    unsigned row_pos, col_pos; /**< положение тыквы на поле ряд и колонка */
    pmk_pumpkin_state_t state; /**< состояние тыквы */
} pmk_pumpkin_t;

/**
 * @brief Структура набора тыкв.
 * Позволяет создать массив тыкв, сохраняющий свой размер.
 */
typedef struct pmk_garden {
    unsigned size;
    pmk_pumpkin_t *pumpkins;
} pmk_garden_t;

/**
 * @brief Функция создания набора тыкв.
 * Функция выделяет массив под набор тыкв.
 * Если память выделить не удалось, то @param errcode перезаписывается в 1.
 * Поле size перезаписывается в 0, поле pumpkins перезаписывается в NULL. 
 * В случае успеха @param errcode перезаписывается в 0.
 * @param size    - количество тыкв 
 * @param errcode - указатель на код возврата
 * @return pmk_garden_t 
 */
pmk_garden_t pmk_make_garden(unsigned size, int *errcode);

/**
 * @brief Функция удаления набора тыкв. 
 * После удаления поле size перезаписывается в 0,
 * поле pumpkins перезаписывается в NULL.
 * @param garden - указатель на структуру набора тыкв
 */
void pmk_delete_garden(pmk_garden_t *garden);

#endif