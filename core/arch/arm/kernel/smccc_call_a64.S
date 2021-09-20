/* SPDX-License-Identifier: BSD-2-Clause */
/*
 * Copyright (C) 2021 Foundries.io Ltd
 */

#include <arm.h>
#include <asm.S>
#include <generated/asm-defines.h>
#include <smccc.h>

/*
 * void smccc_smc(unsigned long a0, unsigned long a1, unsigned long a2,
 *		  unsigned long a3, unsigned long a4, unsigned long a5,
 *		  unsigned long a6, unsigned long a7, struct smccc_res *res)
 * a0~a7: input arguments
 * res: output arguments from register 0-3
 */
FUNC smccc_smc , :
	smc	#0
	ldr	x4, [sp]
	/* Put results to res struct */
	stp	x0, x1, [x4, #SMCCC_RES_X0_OFFS]
	stp	x2, x3, [x4, #SMCCC_RES_X2_OFFS]
	ret
END_FUNC smccc_smc
