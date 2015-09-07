#include "mygame.h"

int move_player(enum direction_num direction) {
    struct coord new_pos;
    new_pos = add_coords(new_coord(p.x, p.y), delta(direction, p.y % 2));
    p.x = new_pos.x;
    p.y = new_pos.y;
    return 0;
}
