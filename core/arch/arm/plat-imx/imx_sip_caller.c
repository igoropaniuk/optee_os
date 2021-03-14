// SPDX-License-Identifier: BSD-2-Clause
/*
 * Copyright (C) 2021 Foundries.io Ltd
 */

#include <imx.h>
#include <imx_sip.h>
#include <io.h>

/*
 * This struct defines the way the registers are stored
 * on the stack during an exception.
 */
struct pt_regs {
	unsigned long elr;
	unsigned long regs[31];
};

void smc_call(struct pt_regs *args);

/*
 * void smc_call(arg0, arg1...arg7)
 *
 * issue the secure monitor call
 *
 * x0~x7: input arguments
 * x0~x3: output arguments
 */
void smc_call(struct pt_regs *args)
{
	asm volatile(
		"ldr x0, %0\n"
		"ldr x1, %1\n"
		"ldr x2, %2\n"
		"ldr x3, %3\n"
		"ldr x4, %4\n"
		"ldr x5, %5\n"
		"ldr x6, %6\n"
		"smc	#0\n"
		"str x0, %0\n"
		"str x1, %1\n"
		"str x2, %2\n"
		"str x3, %3\n"
		: "+m" (args->regs[0]), "+m" (args->regs[1]),
		  "+m" (args->regs[2]), "+m" (args->regs[3])
		: "m" (args->regs[4]), "m" (args->regs[5]),
		  "m" (args->regs[6])
		: "x0", "x1", "x2", "x3", "x4", "x5", "x6", "x7",
		  "x8", "x9", "x10", "x11", "x12", "x13", "x14", "x15",
		  "x16", "x17");
}


unsigned long call_imx_sip(unsigned long id, unsigned long reg0,
			   unsigned long reg1, unsigned long reg2,
			   unsigned long reg3)
{
	struct pt_regs regs;

	regs.regs[0] = id;
	regs.regs[1] = reg0;
	regs.regs[2] = reg1;
	regs.regs[3] = reg2;
	regs.regs[4] = reg3;

	smc_call(&regs);

	return regs.regs[0];
}
