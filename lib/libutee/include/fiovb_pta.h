/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (C) 2021 Foundries.io Ltd
 */

#ifndef __FIOVB_PTA_H
#define __FIOVB_PTA_H

#define PTA_FIOVB_UUID { 0x8287620a, 0x84e5, 0x11eb, \
			{ 0x8d, 0xcd, 0x02, 0x42, 0xac, 0x13, 0x00, 0x03 } }

/*
 * Set PERSIST_SECONDARY_BOOT bit using TF-A SiP service
 *
 * [in]     value[0].a    bit value to set (0, 1)
 *
 * Result:
 * TEE_SUCCESS - Invoke command success
 * TEE_ERROR_BAD_PARAMETERS - Incorrect input param
 * TEE_ERROR_NOT_IMPLEMENTED - Invoke command not implemented
 */
#define PTA_CMD_SET_SECONDARY_BOOT		0
/*
 * Check of PERSIST_SECONDARY_BOOT bit is set using TF-A SiP service
 *
 * [in]     value[0].a    read bit value (0, 1)
 *
 * Result:
 * TEE_SUCCESS - Invoke command success
 * TEE_ERROR_BAD_PARAMETERS - Incorrect input param
 * TEE_ERROR_NOT_IMPLEMENTED - Invoke command not implemented
 */
#define PTA_CMD_IS_SECONDARY_BOOT		1

#endif /* __FIOVB_PTA_H */
