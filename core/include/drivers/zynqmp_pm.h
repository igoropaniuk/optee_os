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
 * @buf: buffer, where efuse date will be stored. The data is returned
 *       in LE byte order
 * @sz: buffer size in bytes
 * @offset: offset of efuse register
 * @puf: is efuse puf, ZYNQMP_PUF_EFUSE/ZYNQMP_NONPUF_EFUSE
 * Return a TEE_Result compliant status
 */
TEE_Result zynqmp_efuse_read(uint8_t *buf, size_t sz, uint32_t efuse_offset,
			     bool puf);

/*
 * Write efuse memory
 * @buf: buffer, contains data that will be written to efuse. The data
 *       should be provided in LE byte order
 * @sz: buffer size in bytes
 * @offset: offset of efuse register
 * @puf: is efuse puf, ZYNQMP_PUF_EFUSE/ZYNQMP_NONPUF_EFUSE
 * Return a TEE_Result compliant status
 */
TEE_Result zynqmp_efuse_write(uint8_t *buf, size_t sz, uint32_t efuse_offset,
			      bool puf);
#endif /*__ZYNQMP_PM_H__*/
