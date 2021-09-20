/* SPDX-License-Identifier: BSD-2-Clause */
/*
 * Copyright (C) 2021 Foundries.io Ltd
 */

#ifndef __ZYNQMP_PM_H__
#define __ZYNQMP_PM_H__

#include <tee_api_types.h>

#define ZYNQMP_NONPUF_EFUSE		0
#define ZYNQMP_PUF_EFUSE		1

#define ZYNQMP_DNA_EFUSE_OFFSET		0xC

/*
 * Read efuse memory
 * @buf: Buffer, where efuse date will be stored, should cache aligned
 * @sz: buffer size in bytes
 * @offset: Offset of efuse register
 * @puf: Is EFUSE PUF: ZYNQMP_NONPUF_EFUSE/ZYNQMP_PUF_EFUSE
 * Return a TEE_Result compliant status
 */
TEE_Result zynqmp_efuse_read(uint8_t *buf, size_t sz, uint32_t efuse_offset,
			     uint32_t puf);

/*
 * Write efuse memory
 * @buf: Buffer, contains data that will be written to efuse,
 *       should cache aligned
 * @sz: buffer size in bytes
 * @offset: Offset of efuse register
 * @puf: Is EFUSE PUF: ZYNQMP_NONPUF_EFUSE/ZYNQMP_PUF_EFUSE
 * Return a TEE_Result compliant status
 */
TEE_Result zynqmp_efuse_write(uint8_t *buf, size_t sz, uint32_t efuse_offset,
			      uint32_t puf);
#endif /*__ZYNQMP_PM_H__*/
