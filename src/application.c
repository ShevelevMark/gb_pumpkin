#include <application.h>

#include <garden_model.h>
#include <drone_model.h>
#include <garden_view.h>
#include <drone_view.h>
#include <view.h>

#include <ncurses.h>

#include <stdlib.h>
#include <time.h>

pmk_application_context_t pmk_allocate_application(unsigned row_size, unsigned col_size, unsigned drones_count, unsigned *cart_sizes, int *errcode) {
    int garden_errcode;
    pmk_garden_t garden = pmk_make_garden(row_size, col_size, &garden_errcode);
    int view_errcode;
    pmk_view_field_t view = pmk_make_view_field(row_size, col_size, &view_errcode);

    int drone_errcode = 0;
    unsigned drone_init_cnt = 0u;
    pmk_drone_t *drones = NULL;
    {
        drones = (pmk_drone_t*)malloc(drones_count * sizeof(pmk_drone_t));
        if (NULL == drones) {
            drone_errcode = 1;
        } else {
            for (; drone_init_cnt != drones_count; ++drone_init_cnt) {
                drones[drone_init_cnt] = pmk_make_drone(0u, 0u, cart_sizes[drone_init_cnt], NULL, NULL, &drone_errcode);
                if (0 != drone_errcode)
                   break; 
            }
        }
    }

    int drone_views_errcode;
    pmk_drone_view_t *drone_views = (pmk_drone_view_t*)malloc(drones_count * sizeof(pmk_drone_view_t));
    drone_views_errcode = NULL == drone_views ? 1 : 0;
    
    pmk_application_context_t application_context;
    application_context.garden = garden;
    application_context.drones_count = drones_count;
    application_context.drones = drones;
    application_context.drone_views = drone_views;
    application_context.view = view;
    
    if (0 == garden_errcode && 0 == view_errcode && 0 == drone_errcode  && 0 == drone_views_errcode) {
        *errcode = 0;        
        return application_context;
    }

    *errcode = 1;
    free(drone_views);
    application_context.drone_views = NULL;
    for (unsigned idx = 0u; idx != drone_init_cnt; ++idx)
            pmk_delete_drone(drones + idx);
    free(drones);
    application_context.drones = NULL;
    pmk_delete_view_field(&view);
    pmk_delete_garden(&garden);
    
    return application_context;
}

void pmk_free_application(pmk_application_context_t *context) {
    free(context->drone_views);
    context->drone_views = NULL;
    for (unsigned idx = 0u; idx != context->drones_count; ++idx)
        pmk_delete_drone(context->drones + idx);
    free(context->drones);
    context->drones = NULL;
    pmk_delete_view_field(&context->view);
    pmk_delete_garden(&context->garden);
}

void pmk_application_advance(pmk_application_context_t *context, clock_t call_time) {
    static unsigned frame_cnt = 0u;
    move(0, 0);
    printw("frame cnt %4u\n", frame_cnt);
    if ((double)(call_time - context->last_call) / (double)CLOCKS_PER_SEC < 1. / context->speed) return;
    context->last_call = call_time;
    ++frame_cnt;
}