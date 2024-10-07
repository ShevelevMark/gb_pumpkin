#ifndef PMK_GARDEN_MODEL_H
#define PMK_GARDEN_MODEL_H

typedef enum pmk_garden_cell {PMK_ROAD = 0, PMK_EMPTY, PMK_UNRIPE, PMK_RIPE} pmk_garden_cell_t;

typedef struct pmk_garden {
    unsigned row_size, col_size;
    pmk_garden_cell_t **cells;
} pmk_garden_t;

pmk_garden_t pmk_make_garden(unsigned row_size, unsigned col_size, int *errcode);

void pmk_delete_garden(pmk_garden_t *garden);

#endif