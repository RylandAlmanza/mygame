main: main.c display.c map.c geometry.c mygame.h
	gcc main.c display.c map.c geometry.c player.c mygame.h -g -o main -lncurses
