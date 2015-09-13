#include "mygame.h"
#include <stdlib.h>
#include <time.h>

int create_npc(enum npc_type_name type_name, int x, int y) {
    int npc_id;
    for (npc_id = 0; npc_id < MAX_NPCS; npc_id++) {
        if (npcs[npc_id].used == false) {
            break;
        }
    }
    switch (type_name) {
        case WOODSMAN:
            npcs[npc_id].type_name = type_name;
            npcs[npc_id].used = true;
            npcs[npc_id].x = x;
            npcs[npc_id].y = y;
    }
    return 0;
}

int npc_can_pass(int x, int y) {
    if (map_npcs[y][x] != -1) {
        return 0;
    }
    if (map_terrain[y][x] == WALL) {
        return 0;
    }
    if (player.x == x && player.y == y) {
        return 0;
    }
    return 1;
}

int move_npc(int npc_id, int x, int y) {
    struct npc *npc = npcs + npc_id;
    map_npcs[npc->y][npc->x] = -1;
    npc->x = x;
    npc->y = y;
    map_npcs[y][x] = npc_id;
}

int npc_act(int npc_id) {
    struct npc *npc = npcs + npc_id;
    enum direction direction;
    switch (npc->type_name) {
        case WOODSMAN:
            direction = (random() % 7) - 1;
            if (direction == -1) {
                break;
            }
            struct coord destination = adjacent_coord(npc->x, npc->y, direction);
            if (npc_can_pass(destination.x, destination.y)) {
                move_npc(npc_id, destination.x, destination.y);
            }
            break;
    }
}
