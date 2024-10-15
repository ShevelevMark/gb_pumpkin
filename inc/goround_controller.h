#ifndef PMK_GOROUND_CONTROLLER_H
#define PMK_GOROUND_CONTROLLER_H

#include <drone_model.h>
#include <garden_model.h>
#include <ncurses.h>

#include <stdbool.h>

typedef struct pmk_position {
    unsigned row, col;
} pmk_position_t;

void swap_position(pmk_position_t *p1, pmk_position_t *p2) {
    pmk_position_t tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}

typedef struct pmk_direction {
    int row, col;
} pmk_direction_t;

pmk_position_t pmk_move(pmk_position_t pos, pmk_direction_t dir) {
    return (pmk_position_t){pos.row + dir.row, pos.col + dir.col};
}

pmk_direction_t rotate_ccw(pmk_direction_t dir) {
    return (pmk_direction_t){-1 * dir.col, dir.row};
}

pmk_direction_t rotate_cw(pmk_direction_t dir) {
    return (pmk_direction_t){dir.col, -1 * dir.row};
}

bool pmk_is_reachable(pmk_direction_t dir, pmk_position_t pos, unsigned row_size, unsigned col_size) {
    return !(
        (dir.row > 0 && pos.row == row_size - 1) ||
        (dir.row < 0 && pos.row == 0) ||
        (dir.col > 0 && pos.col == col_size - 1) ||
        (dir.col < 0 && pos.col == 0)
    );
}

typedef struct pmk_goround_controller_context {
    pmk_direction_t dir;
    pmk_garden_t *garden;
    bool is_invalid_state;
} pmk_goround_controller_context_t;

void pmk_goround_controller_advance(struct pmk_drone *drone, void *cntx_ptr) {
    pmk_goround_controller_context_t *cntx = (pmk_goround_controller_context_t*)cntx_ptr;
    if (cntx->is_invalid_state) return;

    pmk_direction_t on_the_left = rotate_ccw(cntx->dir);
    if (!pmk_is_reachable(on_the_left, (pmk_position_t){drone->row_pos, drone->col_pos}, cntx->garden->row_size, cntx->garden->col_size)) { 
        cntx->is_invalid_state = true; 
        return; 
    }

    pmk_position_t curr_pos = {drone->row_pos, drone->col_pos};
    pmk_position_t new_pos;
    pmk_position_t left_pos = pmk_move(curr_pos, on_the_left);
    if (PMK_ROAD != cntx->garden->cells[left_pos.row][left_pos.col]) {
        if (!pmk_is_reachable(cntx->dir, curr_pos, cntx->garden->row_size, cntx->garden->col_size)) {
            cntx->is_invalid_state = true;
            return;
        }
        new_pos = pmk_move(curr_pos, cntx->dir);
    } else {
        cntx->dir = on_the_left;
        new_pos = pmk_move(curr_pos, on_the_left);
    }

    swap_position(&curr_pos, &new_pos);
    drone->row_pos = curr_pos.row;
    drone->col_pos = curr_pos.col;

    for (unsigned cart_cnt = 0u; cart_cnt != drone->carts_size; ++cart_cnt) {
        curr_pos.row = drone->carts[cart_cnt].row_pos;
        curr_pos.col = drone->carts[cart_cnt].col_pos;
        swap_position(&curr_pos, &new_pos);
        drone->carts[cart_cnt].row_pos = curr_pos.row;
        drone->carts[cart_cnt].col_pos = curr_pos.col;
    }
}

#endif