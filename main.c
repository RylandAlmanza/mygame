#include "mygame.h"
#include <string.h>

int main() {
    srand(time(NULL));
    strcpy(player.name, "dude"); // For now, the player is always named "dude"
    player.x = 11;
    player.y = 11;
    load_map();
    display_init();
    draw_world();
    refresh();
    int game_done = 0;
    int i;
    while (!game_done) {
        game_done = get_command();
        for (i = 0; i < MAX_NPCS; i++) {
            if (npcs[i].used == false) {
                continue;
            }
            npc_act(i);
        }
        draw_world();
        refresh();
    }
    display_uninit();
}
