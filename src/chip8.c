#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
//#include <curses.h>


#include "chip8.h"


uint8_t fonts[][5] = {
	{0xf0,0x90,0x90,0x90,0xf0},
	{0x20,0x60,0x20,0x20,0x70},
	{0xf0,0x10,0xf0,0x80,0xf0},
	{0xf0,0x10,0xf0,0x10,0xf0},
	{0x90,0x90,0xf0,0x10,0x10}
};

struct Context* make_context() {
	struct Context *ctx;
	ctx = malloc(sizeof(*ctx));
	ctx->sp = 4095;
	ctx->tick = -1;
	memcpy(ctx->memory + 0x200, fonts, sizeof(fonts)/sizeof(**fonts));
	return ctx;
}


int ctx_next(struct Context *ctx) {
	uint16_t opcode = (ctx->memory[ctx->pc] << 8) + ctx->memory[ctx->pc+1];
	int x,y;
	if (ctx->tick == -1)
		ctx->tick = time(0);
	if (time(0) - ctx->tick > 1) {
		if (ctx->delay > 0)
			--ctx->delay;
		if (ctx->sound > 0)
			--ctx->sound;
		ctx->tick = time(0);
	}
	//printf("%x\n",opcode);
	if (opcode == 0xffff) return 0;
	switch (opcode>>12) {
	case 0x0:
		if (opcode == 0x00E0) {
			memset(ctx->display, 0, sizeof(ctx->display));
		} else if (opcode == 0x00EE) {
			ctx->pc = ctx->sp;
			ctx->sp += 2;
		} else {
			// 0NNN ignored
		}
		break;
	case 0x1:
		ctx->pc = opcode & 0x0FFF;
		break;
	case 0x2:
		ctx->sp -= 2;
		ctx->memory[ctx->sp] = ctx->pc >> 8;
		ctx->memory[ctx->sp+1] = ctx->pc & 0xFF;
		ctx->pc = opcode & 0xFFF;
		break;
	case 0x3:
		if (ctx->registers[(opcode & 0x0F00)>>8] == (opcode & 0x00FF))
			ctx->pc += 2;
		break;
	case 0x4:
		if (ctx->registers[(opcode & 0x0F00)>>8] != (opcode & 0x00FF))
			ctx->pc += 2;
		break;
	case 0x5:
		if ((opcode & 0xF) == 0) 
			if (ctx->registers[(opcode & 0x0F00)>>8] == ctx->registers[(opcode & 0x00F0)>>4])
				ctx->pc += 2;
		break;
	case 0x6:
		ctx->registers[(opcode & 0x0F00)>>8] = (opcode & 0x00FF);
		break;
	case 0x7:
		ctx->registers[(opcode & 0x0F00)>>8] += (opcode & 0x00FF);
		break;
	case 0x8:
		switch(opcode & 0xF) {
		case 0x0:
			ctx->registers[(opcode & 0x0F00)>>8] = ctx->registers[(opcode & 0x00F0)>>4];
			break;
		
		case 0x1:
			ctx->registers[(opcode & 0x0F00)>>8] |= ctx->registers[(opcode & 0x00F0)>>4];
			break;
		
		case 0x2:
			ctx->registers[(opcode & 0x0F00)>>8] &= ctx->registers[(opcode & 0x00F0)>>4];
			break;
		
		case 0x3:
			ctx->registers[(opcode & 0x0F00)>>8] ^= ctx->registers[(opcode & 0x00F0)>>4];
			break;
		
		case 0x4:
			ctx->registers[(opcode & 0x0F00)>>8] += ctx->registers[(opcode & 0x00F0)>>4];
			break;
		
		case 0x5:
			ctx->registers[(opcode & 0x0F00)>>8] -= ctx->registers[(opcode & 0x00F0)>>4];
			break;
		
		case 0x6:
			ctx->registers[(opcode & 0x00F0)>>4] = ctx->registers[(opcode & 0x0F00)>>8] & 0x1; 
			ctx->registers[(opcode & 0x0F00)>>8] >>= 1;
			break;
		
		case 0x7:
			ctx->registers[(opcode & 0x0F00)>>8] = ctx->registers[(opcode & 0x00F0)>>4] - ctx->registers[(opcode & 0x0F00)>>8];
			break;

		case 0xE:
			ctx->registers[(opcode & 0x00F0)>>4] = ctx->registers[(opcode & 0x0F00)>>8] & 0x80; 
			ctx->registers[(opcode & 0x0F00)>>8] <<= 1;
			break;
		}
		break;
	case 0x9:
		if ((opcode & 0xF) == 0) 
			if (ctx->registers[(opcode & 0x0F00)>>8] != ctx->registers[(opcode & 0x00F0)>>4])
				ctx->pc += 2;
		break;
	
	case 0xA:
		ctx->I = opcode & 0x0FFF;
		break;

	case 0xB:
		ctx->pc = ctx->registers[0] + (opcode & 0xFF);
		break;

	case 0xC:
		break;

	case 0xD:
		x = ctx->registers[(opcode >> 8) & 0xF] % SCREEN_WIDTH;
		y = ctx->registers[(opcode >> 4) & 0xF] % SCREEN_HEIGHT;
		//printf("--- %d %d %d\n",ctx->I,ctx->memory[ctx->I],opcode & 0xF);
		for (int i=0; i < (opcode & 0xF); ++i) {
			//printf("[%x]",ctx->memory[ctx->I + i]);
			ctx->display[y+i] ^= ctx->memory[ctx->I + i] << (x);
		}
		//printf("\n");
		
		break;
	}
	return 1;
}

void ctx_disp_regs(struct Context *ctx) {
	int i;
	printf("PC = %x\n",ctx->pc);
	printf("I = %x\n",ctx->I);	
	for (i=0; i<0xF; ++i)
		printf("V%X = %x\n",i,ctx->registers[i]);
}












