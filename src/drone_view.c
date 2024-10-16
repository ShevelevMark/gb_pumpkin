#include <drone_view.h>
#include <view.h>

void pmk_put_drone(pmk_view_field_t *field, pmk_drone_t drone, pmk_drone_view_t drone_view) {
    field->cells[drone.pos.row][drone.pos.col] = drone.is_unexpected ? drone_view.unexpt_drone : drone_view.drone;
    for (unsigned idx = 0u; idx != drone.carts_size; ++idx)
        field->cells[drone.carts[idx].pos.row][drone.carts[idx].pos.col] = drone.carts[idx].is_empty ? drone_view.empty_cart : drone_view.full_cart;
}