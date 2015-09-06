#ifndef MYGAME_H
#define MYGAME_H

#define MAP_SIZE 10
#define nw_of(coord) add_coords(coord, delta(NW, coord.y % 2))
#define ne_of(coord) add_coords(coord, delta(NE, coord.y % 2))
#define e_of(coord) add_coords(coord, delta(E, coord.y % 2))
#define se_of(coord) add_coords(coord, delta(SE, coord.y % 2))
#define sw_of(coord) add_coords(coord, delta(SW, coord.y % 2))
#define w_of(coord) add_coords(coord, delta(W, coord.y % 2))

struct player p;

struct player {
    char name[20];
    int x, y;
};

int map_terrain[MAP_SIZE][MAP_SIZE];

enum terrain_num {
    WALL = 0, FLOOR = 1
};

struct coord {
   int x, y;
};

struct coord_list {
    int length;
    struct coord *coords;
};

enum direction_num {
    NW = 0, NE = 1,
W = 2,            E = 3,
    SW = 4, SE = 5
};

struct coord new_coord(int x, int y);
struct coord_list select_hex(int center_x, int center_y, int radius);

#endif
