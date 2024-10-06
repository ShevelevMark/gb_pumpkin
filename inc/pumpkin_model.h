#ifndef PMK_PUMPKIN_H
#define PMK_PUMPKIN_H

/**
 * @brief Перечисление состояний грядки с тыквой.
 * PMK_EMPTY  - пустая грядка
 * PMK_UNRIPE - незрелая тыква 
 * PMK_RIPE   - зрелая тыква
 */
typedef enum pmk_pumpkin_state {PMK_EMPTY = 0, PMK_UNRIPE, PMK_RIPE} pmk_pumpkin_t;

/**
 * @brief Структура тыквы на грядке. 
 */
typedef pmk_pumpkin {
    unsigned row_pos, col_pos; /**< положение тыквы на поле ряд и колонка */
    pmk_pumpkin_state_t state; /**< состояние тыквы */
} pmk_pumpkin_t;

#endif