#include "mygame.h"
#include <string.h>

int main() {
    strcpy(p.name, "dude"); // For now, the player is always named "dude"
    p.x = 11;
    p.y = 11;
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
