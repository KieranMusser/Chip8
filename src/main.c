#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chip8.h"



int main(int argc, char **argv) {
	uint8_t *rom; // [] = {0x60,0x15};
	FILE *fp;
	int filelen;

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
	struct Context *ctx = make_context();
	
	//ctx_disp_regs(ctx);
	memcpy(ctx->memory, rom, filelen);
	
	while (ctx_next(ctx))
		ctx->pc += 2;

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



