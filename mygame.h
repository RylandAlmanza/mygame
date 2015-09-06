#ifndef MYGAME_H
#define MYGAME_H

#define MAP_SIZE 10

int map_terrain[MAP_SIZE][MAP_SIZE];

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

enum terrain_num {
    WALL = 0, FLOOR = 1
};

struct coord_list select_hex(int center_x, int center_y, int radius);

#endif
