#include "mygame.h"

int main() {
    gen_map();
    display_init();
    draw_world();
    refresh();
    get_command();
    display_uninit();
}
