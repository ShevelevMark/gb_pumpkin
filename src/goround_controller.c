#include <goround_controller.h>

void pmk_goround_controller_advance(pmk_drone_t *drone, void *cntx_ptr) {
    pmk_goround_controller_context_t *cntx = (pmk_goround_controller_context_t*)cntx_ptr;
    if (drone->is_unexpected) return;

    pmk_direction_t on_the_left = pmk_direction_rotate_ccw(cntx->dir);
    if (!pmk_position_is_reachable(drone->pos, (pmk_position_t){cntx->garden->row_size, cntx->garden->col_size}, on_the_left)) { 
        drone->is_unexpected = true; 
        return; 
    }

    pmk_position_t left_pos = pmk_position_advance(drone->pos, on_the_left);
    if (PMK_ROAD != cntx->garden->cells[left_pos.row][left_pos.col]) {
        if (!pmk_position_is_reachable(drone->pos, (pmk_position_t){cntx->garden->row_size, cntx->garden->col_size}, cntx->dir)) {
            drone->is_unexpected = true;
            return;
        }
    } else {
        cntx->dir = on_the_left;
    }
    pmk_position_t new_pos = pmk_position_advance(drone->pos, cntx->dir);
    pmk_position_swap(&drone->pos, &new_pos);
    for (unsigned cart_cnt = 0u; cart_cnt != drone->carts_size; ++cart_cnt) {
        pmk_position_swap(&drone->carts[cart_cnt].pos, &new_pos);
    }
}