/* SPDX-License-Identifier: BSD-2-Clause */
/*
 * Copyright (C) 2021 Foundries.io Ltd
 */

#ifndef __ZYNQMP_PM_H__
#define __ZYNQMP_PM_H__

#include <tee_api_types.h>

/*
 * Write value to register
 * @address: register address
 * @mask: mask
 * @value: value to write
 * Return a TEE_Result compliant status
 */
TEE_Result zynqmp_mmio_write(const uint32_t address,
			     const uint32_t mask,
			     const uint32_t value);

/*
 * Read value from register
 * @address: register address
 * @value: read value to store
 * Return a TEE_Result compliant status
 */
TEE_Result zynqmp_mmio_read(const uint32_t address,
			    uint32_t *value);

/*
 * Stores all required details to
 * read/write efuse memory.
 * @src:	address of the buffer to store the data to be write/read
 * @size:	number of words to be read/write
 * @offset:	offset to be read/write
 * @flag:	0 - represents efuse read and 1- represents efuse write
 * @pufuserfuse:0 - represents non-puf efuses, offset is used for read/write
 *		1 - represents puf user fuse row number.
 */
struct xilinx_efuse {
	uint64_t src;
	uint32_t size;
	uint32_t offset;
	uint32_t flag;
	uint32_t pufuserfuse;
};

/*
 * Provide access to efuse memory
 * @address: Address of the efuse params structure
 * @value: returned output value
 * Return a TEE_Result compliant status
 */
TEE_Result zynqmp_efuse_access(const uint64_t address,
			       uint32_t *value);
#endif /*__ZYNQMP_PM_H__*/
