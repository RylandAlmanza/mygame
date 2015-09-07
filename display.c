#include "mygame.h"
#include <ncurses.h>

WINDOW *world_window;

struct coord world_coord_to_screen_coord(struct coord world_coord) {
    struct coord screen_coord;
    screen_coord.y = world_coord.y;
    if (world_coord.y % 2 == 0) {
        screen_coord.x = 1 + (2 * world_coord.x);
    } else {
        screen_coord.x = 2 * world_coord.x;
    }
    return screen_coord;
}

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

int display_uninit() {
    clear();
    wrefresh(world_window);
    curs_set(1);
    endwin();
    return 0;
}

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
