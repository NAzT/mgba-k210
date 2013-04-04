#ifndef ARM_H
#define ARM_H

#include <stdint.h>

enum {
	ARM_SP = 13,
	ARM_LR = 14,
	ARM_PC = 15
};

enum ExecutionMode {
	MODE_ARM = 0,
	MODE_THUMB = 1
};

enum PrivilegeMode {
	MODE_USER = 0x10,
	MODE_FIQ = 0x11,
	MODE_IRQ = 0x12,
	MODE_SUPERVISOR = 0x13,
	MODE_ABORT = 0x17,
	MODE_UNDEFINED = 0x1B,
	MODE_SYSTEM = 0x1F
};

enum ExecutionVector {
	BASE_RESET = 0x00000000,
	BASE_UNDEF = 0x00000004,
	BASE_SWI = 0x00000008,
	BASE_PABT = 0x0000000C,
	BASE_DABT = 0x00000010,
	BASE_IRQ = 0x00000018,
	BASE_FIQ = 0x0000001C
};

union PSR {
	struct {
		int exec : 4;
		int t : 1;
		int f : 1;
		int i : 1;
		int a : 1;
		int : 20;
		int v : 1;
		int c : 1;
		int z : 1;
		int n : 1;
	};

	int32_t packed;
};

struct ARMMemory;
struct ARMBoard;

struct ARMCore {
	int32_t gprs[16];
	union PSR cpsr;
	union PSR spsr;

	int32_t cyclesToEvent;

	int32_t shifterOperand;
	int32_t shifterCarryOut;

	struct ARMMemory* memory;
	struct ARMBoard* board;
};

void ARMInit(struct ARMCore* cpu);
void ARMCycle(struct ARMCore* cpu);

#endif