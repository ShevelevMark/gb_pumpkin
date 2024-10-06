#include <drone_view.h>
#include <view.h>

void pmk_put_drone(pmk_view_field_t *field, pmk_drone_t drone, pmk_drone_view drone_view) {
    field->cells[drone.row_pos][drone.col_pos] = drone_view.drone;
    for (unsigned idx = 0u; idx != drone.carts_size; ++idx)
        field->cells[drone.carts[idx].row_pos][drone.carts[dix].col_pos] = drone.carts[idx].is_empty ? drone_view.empty_cart : drone_view.full_cart;
}