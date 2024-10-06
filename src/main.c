#include <ncurses.h>
#include <stdlib.h>
#include <view.h>


int main() {
    initscr();
    start_color();
    raw();
    noecho();
    nodelay(stdscr,TRUE);

    init_pair(1, COLOR_WHITE, COLOR_BLACK);

    unsigned row_size = 20, col_size = 20;
    int errcode;
    pmk_view_field_t field = pmk_make_view_field(row_size, col_size, &errcode);
    if (0 != errcode) {
        printw("Can't allocate view field\nApplication terminated\n");
        goto END;
    }

    for (unsigned row_idx = 0u; row_idx != row_size; ++row_idx)
        for (unsigned col_idx = 0u; col_idx != col_size; ++col_idx)
            field.cells[row_idx][col_idx] = (pmk_view_cell_t){1, '.'};

   pmk_print_view_field(field, 1);
   refresh();

END:
    while(ERR == getch());
    pmk_delete_view_field(&field);
    endwin();

    return 0;
}