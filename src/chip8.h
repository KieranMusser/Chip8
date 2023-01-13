struct Context {
	uint8_t registers[16];
	uint16_t I;
	uint16_t pc;
	uint16_t sp;

	int delay;
	int sound;

	uint8_t memory[4096];
	uint64_t display[32];
};

struct Context* make_context();
int ctx_next(struct Context *ctx);
void ctx_disp_regs(struct Context *ctx);

