#include <view.h>
#include <drone_model.h>
#include <drone_view.h>
#include <garden_model.h>
#include <garden_view.h>
#include <application.h>
#include <goround_controller.h>

#include <time.h>
#include <ncurses.h>
#include <stdlib.h>

void swap_pos(unsigned *pa, unsigned *pb) {
    unsigned tmp = *pa;
    *pa = *pb;
    *pb = tmp;
}

int main() {
    pmk_goround_controller_context_t controller_cntx;
    initscr();
    start_color();
    raw();
    noecho();
    nodelay(stdscr,TRUE);

    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);

    unsigned row_size = 22, col_size = 21;
    unsigned cart_sizes[1] = {3};
    int app_errcode;
    pmk_application_context_t app_cntx =  pmk_allocate_application(row_size, col_size, 1, cart_sizes, &app_errcode);
    if (0 != app_errcode) {
        printw("Can't allocate memory\nApplication terminated\n");
        goto APP_ERR;
    }

    /** INIT ******************************************************************************** */
    {
        pmk_garden_t garden = app_cntx.garden;
        for (unsigned row_idx = 0u; row_idx != garden.row_size; ++row_idx)
            for (unsigned col_idx = 0u; col_idx != garden.col_size; ++col_idx)
                garden.cells[row_idx][col_idx] = PMK_ROAD;

        for (unsigned row_idx = 0u; row_idx + 2 < garden.row_size; row_idx += 3u) {
            for (unsigned col_idx = 1u; col_idx != col_size - 1; ++col_idx) {
                garden.cells[row_idx + 1][col_idx] = PMK_UNRIPE;
                garden.cells[row_idx + 2][col_idx] = PMK_RIPE;
            }
        }

        app_cntx.garden_view = (pmk_garden_view_t){ {{1, '.'}, {1, '~'}, {4, 'o'}, {3, '@'}} };
    }
    pmk_put_garden(&app_cntx.view, app_cntx.garden, app_cntx.garden_view);
      
    {
        app_cntx.drones[0].row_pos = 0;
        app_cntx.drones[0].col_pos = 10;
        app_cntx.drone_views[0] = (pmk_drone_view_t){{2, '#'}, {2, '*'}, {2, '@'}};

        pmk_drone_t drone = app_cntx.drones[0];
        drone.carts[0].row_pos = drone.row_pos; drone.carts[0].col_pos = drone.col_pos + 1; drone.carts[0].is_empty = true;
        drone.carts[1].row_pos = drone.row_pos; drone.carts[1].col_pos = drone.col_pos + 2; drone.carts[1].is_empty = true;
        drone.carts[2].row_pos = drone.row_pos; drone.carts[2].col_pos = drone.col_pos + 3; drone.carts[2].is_empty = true;

        controller_cntx.dir = (pmk_direction_t){0, -1};
        controller_cntx.garden = &app_cntx.garden;
        controller_cntx.is_invalid_state = false;

        app_cntx.drones[0].advance = pmk_goround_controller_advance;
        app_cntx.drones[0].advance_context = &controller_cntx;
    } 
    pmk_put_drone(&app_cntx.view, app_cntx.drones[0], app_cntx.drone_views[0]);
    
    app_cntx.inter_ncolor = 1;
    app_cntx.speed = 3.;
    app_cntx.last_call = (double)clock();
    /** END INIT ******************************************************************************** */
    
    while (ERR == getch()) {
        pmk_application_advance(&app_cntx, clock());
        move(0, 0);
        pmk_print_view_field(app_cntx.view, app_cntx.inter_ncolor); 
        refresh();
    }
    printw("Simulation success!\n");
    pmk_free_application(&app_cntx);

APP_ERR:
    while(ERR == getch());
    endwin();

    return 0;
}