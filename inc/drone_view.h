#ifndef PMK_DRONE_VIEW_H
#define PMK_DRONE_VIEW_H

#include <view.h>

typedef struct pmk_drone_view {
    pmk_view_cell_t drone, empty_cart, full_cart;
} pmk_drone_view_t;

void pmk_put_drone(pmk_view_field_t *field, pmk_drone_t drone, pmk_drone_view drone_view);

#endif