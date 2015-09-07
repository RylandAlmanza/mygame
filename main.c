#include "mygame.h"
#include <string.h>

int main() {
    strcpy(p.name, "dude");
    p.x = 3;
    p.y = 3;
    gen_map();
    display_init();
    draw_world();
    refresh();
    int game_done = 0;
    while (!game_done) {
        game_done = get_command();
    }
    display_uninit();
}
