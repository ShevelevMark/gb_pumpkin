#ifndef PMK_UTILITY_H
#define PMK_UTILITY_H

#include <stdbool.h>

typedef struct pmk_direction {
    int row, col;
} pmk_direction_t;

inline
pmk_direction_t pmk_direction_rotate_ccw(pmk_direction_t dir) {
    return (pmk_direction_t){-1 * dir.col, dir.row};
}

inline
pmk_direction_t pmk_direction_rotate_cw(pmk_direction_t dir) {
    return (pmk_direction_t){dir.col, -1 * dir.row};
}

inline
pmk_direction_t pmk_direction_reverse(pmk_direction_t dir) {
    return (pmk_direction_t){ -1 * dir.row, -1 * dir.col};
}

typedef struct pmk_position {
    unsigned row, col;
} pmk_position_t;

inline
void pmk_position_swap(pmk_position_t *p1, pmk_position_t *p2) {
    pmk_position_t tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}

inline
pmk_position_t pmk_position_advance(pmk_position_t pos, pmk_direction_t dir) {
    return (pmk_position_t){pos.row + dir.row, pos.col + dir.col};
}

inline
bool pmk_position_is_valid(pmk_position_t pos, pmk_position_t limit) {
    return pos.row < limit.row && pos.col < limit.col;
}

inline
bool pmk_position_is_reachable(pmk_position_t pos, pmk_position_t limit, pmk_direction_t dir) {
    return !(
        (dir.row > 0 && pos.row == limit.row - 1) ||
        (dir.row < 0 && pos.row == 0) ||
        (dir.col > 0 && pos.col == limit.col - 1) ||
        (dir.col < 0 && pos.col == 0)
    );
}

#endif