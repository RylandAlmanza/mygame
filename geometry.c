#include "mygame.h"
#include <stdlib.h>

struct coord new_coord(x, y) {
    struct coord c = {x, y};
    return c;
}

struct coord delta(enum direction_num direction, int row_number_odd) {
    switch (direction) {
          case NW:
              return new_coord(row_number_odd ? -1 : 0, -1);
          case NE:
              return new_coord(row_number_odd ? 0 : 1, -1);
          case E:
              return new_coord(1, 0);
          case SE:
              return new_coord(row_number_odd ? 0 : 1, 1);
          case SW:
              return new_coord(row_number_odd ? -1 : 0, 1);
          case W:
              return new_coord(-1, 0);
    }
}

struct coord add_coords(struct coord c1, struct coord c2) {
    return new_coord(c1.x + c2.x, c1.y + c2.y);
}

struct coord_list select_hex(int center_x, int center_y, int radius) {
    struct coord_list hex;
    int i, j;
    int current_index = 0;
    hex.length = 1;
    for (i = 1; i < radius + 1; i++) {
        hex.length += 6 * i;
    }
    hex.coords = malloc((sizeof (struct coord)) * (hex.length + 1) );
    struct coord selection = {center_x, center_y};
    hex.coords[current_index] = selection;
    current_index++;
    for (i = 1; i < radius + 1; i++) {
        selection = add_coords(selection, delta(NW, selection.y % 2));
        hex.coords[current_index] = selection;
        current_index++;
        for (j = 0; j < i; j++) {
            selection = add_coords(selection, delta(E, selection.y % 2));
            hex.coords[current_index] = selection;
            current_index++;
        }
        for (j = 0; j < i; j++) {
            selection = add_coords(selection, delta(SE, selection.y % 2));
            hex.coords[current_index] = selection;
            current_index++;
        }
        for (j = 0; j < i; j++) {
            selection = add_coords(selection, delta(SW, selection.y % 2));
            hex.coords[current_index] = selection;
            current_index++;
        }
        for (j = 0; j < i; j++) {
            selection = add_coords(selection, delta(W, selection.y % 2));
            hex.coords[current_index] = selection;
            current_index++;
        }
        for (j = 0; j < i; j++) {
            selection = add_coords(selection, delta(NW, selection.y % 2));
            hex.coords[current_index] = selection;
            current_index++;
        }
        for (j = 0; j < i - 1; j++) {
            selection = add_coords(selection, delta(NE, selection.y % 2));
            hex.coords[current_index] = selection;
            current_index++;
        }
	selection = add_coords(selection, delta(NE, selection.y % 2));
    }
    return hex;
}
