/* SPDX-License-Identifier: BSD-2-Clause */
/*
 * Copyright (C) 2021 Foundries.io Ltd
 */

#include <arm.h>
#include <arm64_macros.S>
#include <asm.S>
#include <generated/asm-defines.h>

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
	store_xregs x4, SMCCC_RES_X0, 0, 3
	ret
END_FUNC smccc_smc
