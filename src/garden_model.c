#include <garden_model.h>
#include <stdlib.h>

pmk_garden_t pmk_make_garden(unsigned row_size, unsigned col_size, int *errcode) {
    void *memory = malloc(row_size * sizeof(pmk_garden_cell_t*) + row_size * col_size * sizeof(pmk_garden_cell_t));
    if (NULL == memory) {
        *errcode = 1;
        return (pmk_garden_t){0u, 0u, NULL};
    }

    pmk_garden_cell_t **cells_index = (pmk_garden_cell_t**)memory;
    pmk_garden_cell_t *cells_memory = (pmk_garden_cell_t*)((unsigned char *)memory + row_size * sizeof(pmk_garden_cell_t*));
    for (unsigned row_idx = 0u; row_idx != row_size; ++row_idx)
        cells_index[row_idx] = cells_memory + row_idx * col_size;

    *errcode = 0;
    return (pmk_garden_t){row_size, col_size, cells_index};  
}

void pmk_delete_garden(pmk_garden_t *garden) {
    free(garden->cells);
    garden->row_size = 0u;
    garden->col_size = 0u;
    garden->cells = NULL;
}