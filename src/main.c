#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <curses.h>

#include "chip8.h"
#include "render.h"

void itoa(uint64_t val, char* buf, int base){
    int i;
    printf("B %p\n",buf);
    for(i=63; val && i; --i, val /= base) {
        buf[i] = "0123456789abcdef"[val % base];
        printf("%c | ",buf[i]);
    }
    printf("\n");
}
void print_reg(struct Context *ctx){
	int i;
	char buf[65];
    
	for (i=0; i<32; ++i) {
        itoa(ctx->display[i],buf,2);
        printf("%d %s\n",i,buf);
    } 	

}


int main(int argc, char **argv) {
	uint8_t *rom; // [] = {0x60,0x15};
	FILE *fp;
	int filelen;
	int iters;

	struct Context *ctx = make_context();

	printf("%d\n",argc);
	if (argc == 2) {
		fp = fopen(argv[1], "r");
		fseek(fp, 0L, SEEK_END);
		filelen = ftell(fp);
		rewind(fp);

		rom = malloc(sizeof(*rom) * filelen);
		fread(rom, 1, filelen, fp);
		fclose(fp);
	} else {
		printf("Need file argument\n");
		return 1;
	}
	
	//ctx_disp_regs(ctx);
	memcpy(ctx->memory, rom, filelen);
	ctx_init_screen();
	iters = 0;
	while (ctx_next(ctx) && iters < 40 ){
		ctx->pc += 2;
		++iters;
		ctx_redraw(ctx);
	}
	
	getch();
	ctx_end_screen();

	ctx_disp_regs(ctx);

	fp = fopen("memory_dump","w");
	fwrite(ctx->memory, 1, 4096, fp);
	fclose(fp);
	
	fp = fopen("display_dump","w");
	fwrite(ctx->display, 1, sizeof(ctx->display), fp);
	fclose(fp);

	free(ctx);
	return 0;
}



