#ifndef PMK_GOROUND_CONTROLLER_H
#define PMK_GOROUND_CONTROLLER_H

#include <utility.h>
#include <drone_model.h>
#include <garden_model.h>

#include <stdbool.h>

typedef struct pmk_goround_controller_context {
    pmk_direction_t dir;
    pmk_garden_t *garden;
    bool is_invalid_state;
} pmk_goround_controller_context_t;

void pmk_goround_controller_advance(pmk_drone_t *drone, void *cntx_ptr);

#endif