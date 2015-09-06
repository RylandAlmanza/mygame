#include "mygame.h"
#include <stdlib.h>

int gen_map() {
    int i, j;
    for (j = 0; j < MAP_SIZE; j++) {
        for (i = 0; i < MAP_SIZE; i++) {
            map_terrain[j][i] = WALL;
        }
    }
    struct coord_list hex = select_hex(3, 3, 2);
    for (i = 0; i < hex.length; i++) {
        map_terrain[hex.coords[i].y][hex.coords[i].x] = FLOOR;
    }
    free(hex.coords);
    return 0;
}

