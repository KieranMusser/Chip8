#include <curses.h>


#include "chip8.h"



void render_init_screen() {
	initscr();
	cbreak();
	noecho();
	nonl();
	intrflush(stdscr, FALSE);
	keypad(stdscr, TRUE);
	box(stdscr, 0,0);
	curs_set(0);
}
void render_end_screen() {
	endwin();
}

void render_redraw(struct Context *ctx) {
#ifndef DBG_DISABLE_DRAW
	int i;
	uint64_t x,bi;
	for (i=0; i<32; ++i) {
		x = ctx->display[i];
		move(i+1,1);
		for (bi=64; bi > 0; --bi) {
			if (x & ((uint64_t)1 << (bi-1))) {
				addch('#');
			} else {
				addch(' ');
			}
		}
	}
#endif
}
