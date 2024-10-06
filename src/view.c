#include <view.h>
#include <stdlib.h>
#include <ncurses.h>

pmk_view_field_t pmk_make_view_field(unsigned row_size, unsigned col_size, int *errcode) {
    void *memory = malloc(row_size * sizeof(pmk_view_cell_t*) + row_size * col_size * sizeof(pmk_view_cell_t));
    if (NULL == memory) {
        *errcode = 1;
        return (pmk_view_field_t){0u, 0u, NULL};
    }

    pmk_view_cell_t **cells_index = (pmk_view_cell_t**)memory;
    pmk_view_cell_t *cells_memory = (pmk_view_cell_t*)((unsigned char *)memory + row_size * sizeof(pmk_view_cell_t*));
    for (unsigned row_idx = 0u; row_idx != row_size; ++row_idx)
        cells_index[row_idx] = cells_memory + row_idx * col_size;

    *errcode = 0;
    return (pmk_view_field_t){row_size, col_size, cells_index};
}

void pmk_delete_view_field(pmk_view_field_t *field) {
    free((void*)(field->cells));
    field->cells = NULL;
    field->row_size = 0u;
    field->col_size = 0u;
}

void pmk_print_view_field(pmk_view_field_t field, int inter_ncolor) {
    for (unsigned row_idx = 0u; row_idx != field.row_size; ++row_idx) {
        for (unsigned col_idx = 0u; col_idx != field.col_size; ++col_idx) {
            attron(COLOR_PAIR(field.cells[row_idx][col_idx].ncolor));
            printw("%c", field.cells[row_idx][col_idx].glyph);
            attron(COLOR_PAIR(inter_ncolor));
            printw(" ");
        }
        printw("\n");
    }
}
