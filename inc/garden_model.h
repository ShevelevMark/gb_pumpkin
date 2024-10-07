#ifndef PMK_GARDEN_MODEL_H
#define PMK_GARDEN_MODEL_H

/**
 * @brief Перечисление состояний ячейки на сельскохозяйственном поле.
 * PMK_ROAD   - дорога для дрона
 * PMK_EMPTY  - пустая грядка
 * PMK_UNRIPE - незрелая тыква на грядке
 * PMK_RIPE   - зрелая тыква на грядке
 */
typedef enum pmk_garden_cell {PMK_ROAD = 0, PMK_EMPTY, PMK_UNRIPE, PMK_RIPE} pmk_garden_cell_t;

/**
 * @brief Структура хранит данные о ячейках и размерах сельскохозяйственного поля.
 */
typedef struct pmk_garden {
    unsigned row_size, col_size; /**< размеры поля: число рядов, число столбцов */
    pmk_garden_cell_t **cells;   /**< указатель на массив ячеек */
} pmk_garden_t;

/**
 * @brief Функция создания нового поля с тыквами.
 * Функция создаёт новое поле с тыквами заданных размеров.
 * Функция самостоятельно выделяет память под поле и индексный массив (массив указателей для удобного обращения к ячейкам).
 * Если размеры @param row_size или @param col_size нулевы - поведение функции не определено.
 * Если выделить память не удалось, то @param errcode будет перезаписано в 1.
 * При успехе @param errcode будет перезаписано в 0.
 * @param row_size - количество рядов
 * @param col_size - количество стобцов
 * @param errcode  - указатель на целое число, которое используется для кода возврата
 * @return pmk_garden_t 
 */
pmk_garden_t pmk_make_garden(unsigned row_size, unsigned col_size, int *errcode);

/**
 * @brief Функция удаления памяти ячеек поля с тыквами.
 * Функция удаляет память под поле с тыквами и записывает в структуру {0u, 0u, NULL}.
 * @param garden - указатель на структуру поля, для которой необходимо освободить память.
 * @warning переданная структура @param garden должна быть инициализированна функцией pmk_make_garden!
 */
void pmk_delete_garden(pmk_garden_t *garden);

#endif