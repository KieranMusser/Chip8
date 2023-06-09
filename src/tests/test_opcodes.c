#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define DBG_DISABLE_DRAW

#include "../chip8.h"




int main(void) {
	struct Context *ctx = make_context();
	ctx->memory[2] = 0xff;
	ctx->memory[3] = 0xff;
	
	ctx->memory[0] = 0x17;
	ctx->memory[1] = 0x89;

	ctx->pc = 0;
	ctx_next(ctx);
	assert(ctx->pc == 0x789);


	free(ctx);
	return 0;
}
