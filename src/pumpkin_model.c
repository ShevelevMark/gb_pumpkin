#include <pumpkin_model.h>
#include <stdlib.h>

pmk_garden_t pmk_make_garden(unsigned size, int *errcode) {
    pmk_pumpkin_t *pumpkins = (pmk_pumpkin_t*)malloc(size * sizeof(pmk_pumpkin_t));
    if (NULL == pumpkins) {
        *errcode = 1;
        return (pmk_garden_t){0u, NULL};
    }
    *errcode = 0;
    return (pmk_garden_t){size, pumpkins};
}

void pmk_delete_garden(pmk_garden_t *garden) {
    free(garden->pumpkins);
    garden->size = 0u;
    garden->pumpkins = NULL;
}