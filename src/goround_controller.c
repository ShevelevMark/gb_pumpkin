#include <goround_controller.h>

void pmk_goround_controller_advance(pmk_drone_t *drone, void *cntx_ptr) {
    pmk_goround_controller_context_t *cntx = (pmk_goround_controller_context_t*)cntx_ptr;
    if (cntx->is_invalid_state) return;

    pmk_direction_t on_the_left = pmk_direction_rotate_ccw(cntx->dir);
    if (!pmk_position_is_reachable((pmk_position_t){drone->row_pos, drone->col_pos}, (pmk_position_t){cntx->garden->row_size, cntx->garden->col_size}, on_the_left)) { 
        cntx->is_invalid_state = true; 
        return; 
    }

    pmk_position_t curr_pos = {drone->row_pos, drone->col_pos};
    pmk_position_t left_pos = pmk_position_advance(curr_pos, on_the_left);
    if (PMK_ROAD != cntx->garden->cells[left_pos.row][left_pos.col]) {
        if (!pmk_position_is_reachable(curr_pos, (pmk_position_t){cntx->garden->row_size, cntx->garden->col_size}, cntx->dir)) {
            cntx->is_invalid_state = true;
            return;
        }
    } else {
        cntx->dir = on_the_left;
    }
    pmk_position_t new_pos = pmk_position_advance(curr_pos, cntx->dir);

    pmk_position_swap(&curr_pos, &new_pos);
    drone->row_pos = curr_pos.row;
    drone->col_pos = curr_pos.col;

    for (unsigned cart_cnt = 0u; cart_cnt != drone->carts_size; ++cart_cnt) {
        curr_pos.row = drone->carts[cart_cnt].row_pos;
        curr_pos.col = drone->carts[cart_cnt].col_pos;
        pmk_position_swap(&curr_pos, &new_pos);
        drone->carts[cart_cnt].row_pos = curr_pos.row;
        drone->carts[cart_cnt].col_pos = curr_pos.col;
    }
}