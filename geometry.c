#include "mygame.h"
#include <stdlib.h>

// Function to create coordinate structs
struct coord new_coord(x, y) {
    struct coord c = {x, y};
    return c;
}

/* Given a direction (NW, NE, E, SE, SW, or W,) and whether or not the row
 * index of the coordinate is odd, this function will determine what the x and
 * y deltas towards the given direction are.
 */
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

// Adds two coordinates together.
struct coord add_coords(struct coord c1, struct coord c2) {
    return new_coord(c1.x + c2.x, c1.y + c2.y);
}

/* This function returns a list of all coordinates which lie inside the hexagon
 * defined by it's center coordinate, and it's radius
 */
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
        selection = nw_of(selection);
        hex.coords[current_index] = selection;
        current_index++;
        for (j = 0; j < i; j++) {
            selection = e_of(selection);
            hex.coords[current_index] = selection;
            current_index++;
        }
        for (j = 0; j < i; j++) {
            selection = se_of(selection);
            hex.coords[current_index] = selection;
            current_index++;
        }
        for (j = 0; j < i; j++) {
            selection = sw_of(selection);
            hex.coords[current_index] = selection;
            current_index++;
        }
        for (j = 0; j < i; j++) {
            selection = w_of(selection);
            hex.coords[current_index] = selection;
            current_index++;
        }
        for (j = 0; j < i; j++) {
            selection = nw_of(selection);
            hex.coords[current_index] = selection;
            current_index++;
        }
        for (j = 0; j < i - 1; j++) {
            selection = ne_of(selection);
            hex.coords[current_index] = selection;
            current_index++;
        }
	selection = ne_of(selection);
    }
    return hex;
}
