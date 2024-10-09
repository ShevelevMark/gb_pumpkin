#ifndef PMK_APPLICATION_H
#define PMK_APPLICATION_H

#include <garden_model.h>
#include <drone_model.h>
#include <garden_view.h>
#include <drone_view.h>
#include <view.h>

#include <time.h>

typedef struct pmk_application_context {
    pmk_garden_t garden;
    pmk_garden_view_t garden_view;
    unsigned drones_count;
    pmk_drone_t *drones;
    pmk_drone_view_t *drone_views;
    pmk_view_field_t view;
    int inter_ncolor;
    clock_t last_call;
    double speed;
} pmk_application_context_t;

pmk_application_context_t pmk_allocate_application(unsigned row_size, unsigned col_size, unsigned drones_count, unsigned *cart_sizes, int *errcode);

void pmk_free_application(pmk_application_context_t *context);

void pmk_application_advance(pmk_application_context_t *context, clock_t call_time);

#endif