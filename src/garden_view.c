#include <garden_view.h>

void pmk_put_garden(pmk_view_field_t *field, pmk_garden_t garden, pmk_garden_view_t garden_view) {
    for (unsigned row_idx = 0u; row_idx != garden.row_size; ++row_idx)
        for (unsigned col_idx = 0u; col_idx != garden.col_size; ++col_idx)
            if (row_idx < field->row_size && col_idx < field->col_size)
                field->cells[row_idx][col_idx] = garden_view.views[garden.cells[row_idx][col_idx]]; 
}