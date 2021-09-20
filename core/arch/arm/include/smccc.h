/* SPDX-License-Identifier: BSD-2-Clause */
/*
 * Copyright (c) 2018, Linaro Limited
 */

#ifndef __SMCCC_H
#define __SMCCC_H

/*
 * Describes features of SMC Calling Convention from v1.1
 * See also https://developer.arm.com/-/media/developer/pdf/ARM_DEN_0070A_Firmware_interfaces_for_mitigating_CVE-2017-5715.pdf
 */

/*
 * Retrieve the implemented version of the SMC Calling Convention
 * Mandatory from SMCCC v1.1
 * Optional in SMCCC v1.0
 */
#define SMCCC_VERSION		0x80000000

/*
 * Determine the availability and capability of Arm Architecture Service
 * functions.
 * Mandatory from SMCCC v1.1
 * Optional for SMCCC v1.0
 */
#define SMCCC_ARCH_FEATURES	0x80000001

/*
 * Execute the mitigation for CVE-2017-5715 on the calling PE
 * Optional from SMCCC v1.1
 * Not supported in SMCCC v1.0
 */
#define SMCCC_ARCH_WORKAROUND_1	0x80008000

#ifndef __ASSEMBLER__
#ifdef ARM64
/**
 * Result from SMC call
 * a0-a3: result values from registers 0 to 3
 */
struct smccc_res {
	unsigned long a0;
	unsigned long a1;
	unsigned long a2;
	unsigned long a3;
};

/*
 * smccc_smc() - make SMC calls
 * a0-a7: arguments passed in registers 0 to 7
 * res: result values from registers 0 to 3
 */
void smccc_smc(unsigned long a0, unsigned long a1, unsigned long a2,
	       unsigned long a3, unsigned long a4, unsigned long a5,
	       unsigned long a6, unsigned long a7, struct smccc_res *res);
#endif /* ARM64 */
#endif /* __ASSEMBLER__ */

#endif /*__SMCCC_H*/
