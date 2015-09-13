#ifndef MYGAME_H
#define MYGAME_H

#include <stdbool.h>

#define MAP_SIZE 23
#define nw_of(x, y) add_coords(new_coord(x, y), delta(NW, y % 2))
#define ne_of(x, y) add_coords(new_coord(x, y), delta(NE, y % 2))
#define e_of(x, y) add_coords(new_coord(x, y), delta(E, y % 2))
#define se_of(x, y) add_coords(new_coord(x, y), delta(SE, y % 2))
#define sw_of(x, y) add_coords(new_coord(x, y), delta(SW, y % 2))
#define w_of(x, y) add_coords(new_coord(x, y), delta(W, y % 2))
#define adjacent_coord(x, y, dir) add_coords(new_coord(x, y), delta(dir, y % 2))

#define MAX_NPCS 100

struct player player;

struct player {
    char name[20];
    int x, y;
};

enum npc_type_name {
    WOODSMAN
};

struct npc_type {
    char name[20];
};

struct npc_type npc_types[1];

struct npc {
    enum npc_type_name type_name;
    bool used;
    int x, y;
};

struct npc npcs[MAX_NPCS];

int map_terrain[MAP_SIZE][MAP_SIZE];
int map_npcs[MAP_SIZE][MAP_SIZE];

enum terrain_num {
    WALL, FLOOR, DOOR, TREE
};

struct coord {
   int x, y;
};

struct coord_list {
    int length;
    struct coord *coords;
};

enum direction {
    NW = 0, NE = 1,
W = 2,            E = 3,
    SW = 4, SE = 5
};

enum command {
    MOVE
};

int move_player(int x, int y);
int npc_can_pass(int x, int y);

struct coord new_coord(int x, int y);
struct coord add_coords(struct coord c1, struct coord c2);
struct coord delta(enum direction direction, int row_number_odd);
struct coord_list select_hex(int center_x, int center_y, int radius);

#endif
