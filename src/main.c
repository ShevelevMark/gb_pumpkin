#include <ncurses.h>
#include <stdlib.h>
#include <view.h>
#include <drone_model.h>
#include <drone_view.h>
#include <garden_model.h>
#include <garden_view.h>

int main() {
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
    int errcode;

    pmk_view_field_t field = pmk_make_view_field(row_size, col_size, &errcode);
    if (0 != errcode) {
        printw("Can't allocate view field\nApplication terminated\n");
        goto END;
    }

    for (unsigned row_idx = 0u; row_idx != row_size; ++row_idx)
        for (unsigned col_idx = 0u; col_idx != col_size; ++col_idx)
            field.cells[row_idx][col_idx] = (pmk_view_cell_t){1, '.'};

    pmk_drone_t drone = pmk_make_drone(10, 10, 3, &errcode);
    if (0 != errcode) {
        printw("Can't allocate drone\nApplication terminated\n");
        goto END;
    }
    drone.carts[0].row_pos = 10; drone.carts[0].col_pos = 11; drone.carts[0].is_empty = true;
    drone.carts[1].row_pos = 10; drone.carts[1].col_pos = 12; drone.carts[1].is_empty = true;
    drone.carts[2].row_pos = 10; drone.carts[2].col_pos = 13; drone.carts[2].is_empty = true;
    pmk_put_drone(&field, drone, (pmk_drone_view_t){{2, '#'}, {2, '*'}, {2, '@'}});

    pmk_garden_t garden = pmk_make_garden(row_size, col_size, &errcode);
    if (0 != errcode) {
        printw("Can't allocate pumpkins\nApplication terminated\n");
        goto END;
    }
    for (unsigned row_idx = 0u; row_idx != garden.row_size; ++row_idx)
        for (unsigned col_idx = 0u; col_idx != garden.col_size; ++col_idx)
            garden.cells[row_idx][col_idx] = PMK_ROAD;

    for (unsigned row_idx = 0u; row_idx + 2 < garden.row_size; row_idx += 3u) {
        for (unsigned col_idx = 1u; col_idx != col_size - 1; ++col_idx) {
            garden.cells[row_idx + 1][col_idx] = PMK_UNRIPE;
            garden.cells[row_idx + 2][col_idx] = PMK_UNRIPE;
        }
    }

    pmk_garden_view_t garden_view = (pmk_garden_view_t){ {{1, '.'}, {1, '~'}, {4, 'o'}, {3, '@'}} };
    pmk_put_garden(&field, garden, garden_view);

    pmk_print_view_field(field, 1);
    refresh();

END:
    while(ERR == getch());
    pmk_delete_garden(&garden);
    pmk_delete_drone(&drone);
    pmk_delete_view_field(&field);
    endwin();

    return 0;
}