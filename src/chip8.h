#include <stdlib.h>

#pragma once

#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32

struct Context {
	uint8_t registers[16];
	uint16_t I;
	uint16_t pc;
	uint16_t sp;

	int delay;
	int sound;

	int tick;

	uint8_t memory[4096];
	uint64_t display[SCREEN_HEIGHT];
};

struct Context* make_context();
int ctx_next(struct Context *ctx);
void ctx_disp_regs(struct Context *ctx);
