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
    get_command();
    display_uninit();
}
