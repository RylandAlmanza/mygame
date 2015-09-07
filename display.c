#include "mygame.h"
#include <ncurses.h>

WINDOW *world_window; // This window will be the view of the game world

/* To store the hexagonal map, I am using the "Zigzagged axis" method described
 * on this page: http://www.roguebasin.com/index.php?title=Hexagonal_Tiles.
 * The following function is to determine where a tile should appear on screen,
 * given the tile's array indicies within the map_terrain variable.
 */
struct coord world_coord_to_screen_coord(struct coord world_coord) {
    struct coord screen_coord;
    screen_coord.y = world_coord.y;
    if (world_coord.y % 2 == 0) { // if the row index is even
        screen_coord.x = 1 + (2 * world_coord.x); // add 1 to the screen x coord
    } else {
        screen_coord.x = 2 * world_coord.x;
    }
    return screen_coord;
}

// Given a terrain ID, this will return the character to display
static int terrain_char(enum terrain_num terrain_type) {
    switch (terrain_type) {
        case WALL:
            return '#';
        case FLOOR:
            return '.';
    }
}

int draw_world() {
    int i, j;
    // Loop through map_terrain, and display all tiles.
    // j and i represent y and x coordinates, respectively
    for (j = 0; j < MAP_SIZE; j++) {
        for (i = 0; i < MAP_SIZE; i++) {
            struct coord world_coord = {i, j};
            struct coord pos = world_coord_to_screen_coord(world_coord);
            struct coord ppos = world_coord_to_screen_coord(new_coord(p.x, p.y));
            mvwaddch(world_window, pos.y, pos.x,
                     terrain_char(map_terrain[j][i]));
            mvwaddch(world_window, ppos.y, ppos.x, '@');
        }
    }
}

// Initialize ncurses stuff
int display_init() {
    initscr();
    noecho();
    cbreak();
    start_color();
    curs_set(0);
    init_pair(1, COLOR_WHITE, COLOR_BLACK);

    world_window = newwin(24, 80, 0, 0);
    wclear(world_window);
    scrollok(world_window, FALSE);

    idcok(world_window, FALSE);

    return 0;
}

// Uninitialize ncurses stuff
int display_uninit() {
    clear();
    wrefresh(world_window);
    curs_set(1);
    endwin();
    return 0;
}

// Process user input. Perhaps I should rename this file "interface.c"
int get_command() {
    char ch = wgetch(world_window);
    switch (ch) {
        case 'y':
            move_player(NW);
            break;
        case 'u':
            move_player(NE);
            break;
        case 'l':
            move_player(E);
            break;
        case 'n':
            move_player(SE);
            break;
        case 'b':
            move_player(SW);
            break;
        case 'h':
            move_player(W);
            break;
        case 'q':
            return 1;
    }
    draw_world();
    refresh();
    return 0;
}
