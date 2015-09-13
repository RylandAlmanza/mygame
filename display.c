#include "mygame.h"
#include <ncurses.h>

WINDOW *world_window; // This window will be the view of the game world
WINDOW *message_window;

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
        case DOOR:
            return '+';
        case TREE:
            return 'T';
    }
}

static int npc_char(enum npc_type_name npc_type) {
    switch (npc_type) {
        case WOODSMAN:
            return '@';
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
            mvwaddch(world_window, pos.y, pos.x,
                     terrain_char(map_terrain[j][i]));
            if (map_npcs[j][i] != -1) {
                mvwaddch(world_window, pos.y, pos.x, npc_char(map_npcs[j][i]));
            }
        }
    }
    struct coord ppos = world_coord_to_screen_coord(new_coord(player.x, player.y));
    mvwaddch(world_window, ppos.y, ppos.x, '@');
}

// Initialize ncurses stuff
int display_init() {
    initscr();
    noecho();
    cbreak();
    start_color();
    curs_set(0);
    init_pair(1, COLOR_WHITE, COLOR_BLACK);

    world_window = newwin(24, 48, 0, 0);
    message_window = newwin(24, 32, 0, 48);
    wclear(world_window);
    wclear(message_window);
    scrollok(world_window, FALSE);
    scrollok(message_window, TRUE);

    idcok(world_window, FALSE);
    idcok(message_window, FALSE);

    return 0;
}

int print_message(char *message) {
    wclear(message_window);
    wprintw(message_window, message, 0, 0);
    wrefresh(message_window);
    return 0;
}

// Uninitialize ncurses stuff
int display_uninit() {
    clear();
    wrefresh(world_window);
    wrefresh(message_window);
    curs_set(1);
    endwin();
    return 0;
}

// Process user input. Perhaps I should rename this file "interface.c"
int get_command() {
    char ch = wgetch(world_window);
    enum direction direction;
    enum command command;
    switch (ch) {
        case 'y':
            direction = NW;
            command = MOVE;
            break;
        case 'u':
            direction = NE;
            command = MOVE;
            break;
        case 'l':
            direction = E;
            command = MOVE;
            break;
        case 'n':
            direction = SE;
            command = MOVE;
            break;
        case 'b':
            direction = SW;
            command = MOVE;
            break;
        case 'h':
            direction = W;
            command = MOVE;
            break;
        case 't':
            command = GREET;
            print_message("In which direction is the being you'd like to speak with?");
            break;
        case 'q':
            return 1;
    }
    if (command == MOVE) {
        struct coord destination = adjacent_coord(player.x, player.y,
                                                            direction);
        if (npc_can_pass(destination.x, destination.y)) {
            move_player(destination.x, destination.y);
        }
    }
    return 0;
}
