#include "mygame.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int gen_map() {
    int i, j;
    for (j = 0; j < MAP_SIZE; j++) {
        for (i = 0; i < MAP_SIZE; i++) {
            map_terrain[j][i] = WALL;
        }
    }
    struct coord_list hex = select_hex(11, 11, 10);
    for (i = 0; i < hex.length; i++) {
        map_terrain[hex.coords[i].y][hex.coords[i].x] = FLOOR;
    }
    free(hex.coords);
    return 0;
}

int load_map() {
    FILE *map_file;
    map_file = fopen("mapcompressed.txt", "r");
    int x = 0;
    int y = 0;
    char c = '.';
    bool end_of_file = false;
    int npc_id;
    for (npc_id = 0; npc_id < MAX_NPCS; npc_id++) {
        npcs[npc_id].used = false;
    }

    while (end_of_file == false) {
        c = fgetc(map_file);
        if (c == '\n') {
            y++;
            x = 0;
            c = fgetc(map_file);
        }
        if (c == EOF) {
            end_of_file = true;
            break;
        }
        if (c == '.') {
            map_terrain[y][x] = FLOOR;
        }
        if (c == '#') {
            map_terrain[y][x] = WALL;
        }
        if (c == '+') {
            map_terrain[y][x] = DOOR;
        }
        map_npcs[y][x] = -1;
        if (y == 12 && x == 12) {
            map_npcs[y][x] = create_npc(WOODSMAN, x, y);
        }
        x++;
    }
    fclose(map_file);
}
