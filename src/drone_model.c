#include <drone_model.h>

#include <stdlib.h>

pmk_drone_t pmk_allocate_drone(unsigned carts_size, int *errcode) {
    if (0 == carts_size) {
        *errcode = 0;
        return (pmk_drone_t){(pmk_position_t){0u, 0u}, 0u, NULL, NULL, NULL, true};
    }

    pmk_cart_t *carts = (pmk_cart_t*)(malloc(carts_size * sizeof(pmk_cart_t)));
    if (NULL == carts) {
        *errcode = 1;
        return (pmk_drone_t){(pmk_position_t){0u, 0u}, 0u, NULL, NULL, NULL, true};
    }

    *errcode = 0;
    return (pmk_drone_t){(pmk_position_t){0u, 0u},  carts_size, carts, NULL, NULL, true};
}

void pmk_free_drone(pmk_drone_t *drone) {
    free(drone->carts);
    drone->carts_size = 0u;
    drone->carts = NULL;
    drone->is_unexpected = true;
}