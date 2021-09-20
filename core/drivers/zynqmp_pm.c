// SPDX-License-Identifier: BSD-2-Clause
/*
 * Copyright (C) 2021 Foundries.io Ltd
 */

#include <arm.h>
#include <drivers/zynqmp_pm.h>
#include <smccc.h>
#include <tee_api_types.h>

#define ZYNQMP_MMIO_WRITE	0xC2000013
#define ZYNQMP_MMIO_READ	0xC2000014
#define ZYNQMP_EFUSE_ACCESS	0xC2000035

static uint32_t zynqmp_sip_call(uint32_t pm_api_id, uint32_t arg0,
				uint32_t arg1, uint32_t arg2, uint32_t arg3,
				uint32_t *payload)
{
	struct smccc_res res = { };

	smccc_smc(pm_api_id,
		  ((uint64_t)arg1 << 32) | arg0,
		  ((uint64_t)arg3 << 32) | arg2,
		  0, 0, 0, 0, 0, &res);

	if (payload)
		*payload = res.a0 >> 32;

	return res.a0;
}

TEE_Result zynqmp_mmio_write(const uint32_t address,
			     const uint32_t mask,
			     const uint32_t value)
{
	uint32_t ret = 0;

	ret = zynqmp_sip_call(ZYNQMP_MMIO_WRITE, address, mask,
			      value, 0, NULL);

	if (ret)
		return TEE_ERROR_GENERIC;

	return TEE_SUCCESS;
}

TEE_Result zynqmp_mmio_read(const uint32_t address,
			    uint32_t *value)
{
	uint32_t ret = 0;
	uint32_t payload = 0;

	if (!value)
		return TEE_ERROR_BAD_PARAMETERS;

	ret = zynqmp_sip_call(ZYNQMP_MMIO_READ, address,
			      0, 0, 0, &payload);
	*value = payload;
	if (ret)
		return TEE_ERROR_GENERIC;

	return TEE_SUCCESS;
}

TEE_Result zynqmp_efuse_access(const uint64_t address,
			       uint32_t *value)
{
	uint32_t ret = 0;
	uint32_t payload = 0;

	if (!value)
		return TEE_ERROR_BAD_PARAMETERS;

	ret = zynqmp_sip_call(ZYNQMP_EFUSE_ACCESS,
			      (uint32_t)(address >> 32),
			      (uint32_t)(address),
			      0, 0, &payload);
	*value = payload;
	if (ret)
		return TEE_ERROR_GENERIC;

	return TEE_SUCCESS;
}
