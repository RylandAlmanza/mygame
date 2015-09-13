main: main.c display.c map.c geometry.c npc.c npctypes.c mygame.h
	gcc mygame.h *.c -g -o main -lncurses
