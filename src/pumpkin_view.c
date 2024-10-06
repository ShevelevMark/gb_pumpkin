#include <view.h>
#include <pumpkin_view.h>

pmk_view_cell_t cell_by_state(pmk_pumpkin_state_t state, pmk_pumpkin_view_t pumpkin_view) {
    switch (state) {
        case PMK_EMPTY:
            return pumpkin_view.empty;
        case PMK_UNRIPE:
            return pumpkin_view.unripe;
        case PMK_RIPE:
            return pumpkin_view.ripe;
    }
}

void pmk_put_garden(pmk_view_field_t *field, pmk_garden_t garden, pmk_pumpkin_view_t pumpkin_view) {
    for (unsigned idx = 0u; idx != garden.size; ++idx)
        field->cells[garden.pumpkins[idx].row_pos][garden.pumpkins[idx].col_pos] = cell_by_state(garden.pumpkins[idx].state, pumpkin_view); 
}
