/* SPDX-License-Identifier: BSD-2-Clause */
/*
 * Copyright (C) 2021 Foundries.io Ltd
 */

#ifndef __ZYNQMP_PM_H__
#define __ZYNQMP_PM_H__

#include <tee_api_types.h>

/*
 * Information about accessing eFUSES and
 * Physically Uncloneable Function (PUF) Support can be found at
 * https://www.xilinx.com/support/documentation/application_notes/xapp1319-zynq-usp-prog-nvm.pdf
 */
#define ZYNQMP_NONPUF_EFUSE		0
#define ZYNQMP_PUF_EFUSE		1

#define ZYNQMP_EFUSE_VERSION		0x4
#define ZYNQMP_EFUSE_DNA		0xC
#define ZYNQMP_EFUSE_USER0		0x20
#define ZYNQMP_EFUSE_USER1		0x24
#define ZYNQMP_EFUSE_USER2		0x28
#define ZYNQMP_EFUSE_USER3		0x2C
#define ZYNQMP_EFUSE_USER4		0x30
#define ZYNQMP_EFUSE_USER5		0x34
#define ZYNQMP_EFUSE_USER6		0x38
#define ZYNQMP_EFUSE_USER7		0x3C
#define ZYNQMP_EFUSE_MISC_USER		0x40
#define ZYNQMP_EFUSE_SECURE_CONTROL	0x58
#define ZYNQMP_EFUSE_SPK_ID		0x5C
#define ZYNQMP_EFUSE_AES_KEY		0x60
#define ZYNQMP_EFUSE_PPK0_HASH		0xA0
#define ZYNQMP_EFUSE_PPK1_HASH		0xD0

/*
 * Read efuse memory
 * @buf: buffer, where efuse date will be stored. The data is returned
 *       in LE byte order. Buffer must be cache aligned
 * @buf_sz: buffer size in bytes, must be a multiple of the cacheline size
 * @efuse_offset: offset of efuse register
 * @puf: is efuse puf, ZYNQMP_PUF_EFUSE/ZYNQMP_NONPUF_EFUSE
 * Return a TEE_Result compliant status
 */
TEE_Result zynqmp_efuse_read(uint8_t *buf, size_t buf_sz,
			     uint32_t efuse_offset, bool puf);

/*
 * Returns the supported length of the efuse in bytes as per the
 * provided offset. In case of invalid offset, returns 0xFF
 * @offset: offset of efuse register
 */
uint32_t zynqmp_get_efuse_length(uint32_t offset);

/*
 * Returns the buffer size that should allocated for accessing eFUSES
 * @efuse_offset: offset of efuse register
 */
size_t zynqmp_get_buffer_size(uint32_t efuse_offset);
#endif /*__ZYNQMP_PM_H__*/
