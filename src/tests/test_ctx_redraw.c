#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <curses.h>

#include "../chip8.h"
void itoa(uint64_t val, char* buf, int base){
	int i;
	printf("B %p\n",buf);
	for(i=63; val && i; --i, val /= base) {
		buf[i] = "0123456789abcdef"[val % base];
		printf("%c | ",buf[i]);
	}
	printf("\n");
}	
void clearback(int lines) {
	printf("\x1b[");

}

int main() {
	uint8_t rom[] = {};
	struct Context *ctx = make_context();
	int i;
	char buf[65];

	ctx_init_screen();
	memset(buf, 32, 64);
	buf[64] = 0;
	printf("%s\n",buf);
	for (i=0;i<32;++i) {
		ctx->display[i] = i;
	}
	for (i=0; i<32; ++i) {
		itoa(ctx->display[i],buf,2);
		printf("%d %s\n",i,buf);
	}
	ctx_redraw(ctx);
	getch();
	ctx_end_screen();
	free(ctx);
	return 0;
}
