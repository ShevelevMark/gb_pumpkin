#ifndef PMK_DRONE_MODEL_H
#define PMK_DRONE_MODEL_H

#include <stdbool.h>

typedef struct pmk_cart {
    unsigned row_pos, col_pos;
    bool is_empty;
} pmk_cart_t;

typedef struct pmk_drone {
    unsigned row_pos, col_pos;
    int row_dir, col_dir;
    unsigned carts_size;
    pmk_cart_t *carts;
} pmk_drone_t;

pmk_drone_t pmk_make_drone(unsigned row_pos, unsigned col_pos, unsigned carts_size, int *errcode);

void pmk_delete_drone(pmk_drone_t *drone);
#endif