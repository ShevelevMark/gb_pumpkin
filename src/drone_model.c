#include <drone_model.h>
#include <stdlib.h>

pmk_drone_t pmk_make_drone(unsigned row_pos, unsigned col_pos, unsigned carts_size, pmk_drone_advance_t advance_strategy, void *advance_strategy_context, int *errcode) {
    if (0 == carts_size) {
        *errcode = 0;
        return (pmk_drone_t){row_pos, col_pos, 0u, NULL, advance_strategy, advance_strategy_context};
    }

    pmk_cart_t *carts = (pmk_cart_t*)(malloc(carts_size * sizeof(pmk_cart_t)));
    if (NULL == carts) {
        *errcode = 1;
        return (pmk_drone_t){row_pos, col_pos, 0u, NULL, NULL, NULL};
    }

    *errcode = 0;
    return (pmk_drone_t){row_pos, col_pos,  carts_size, carts, advance_strategy, advance_strategy_context};
}

void pmk_delete_drone(pmk_drone_t *drone) {
    free(drone->carts);
    drone->carts_size = 0u;
    drone->carts = NULL;
}