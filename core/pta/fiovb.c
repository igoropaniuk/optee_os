// SPDX-License-Identifier: BSD-3-Clause
/*
 * Copyright (C) 2021 Foundries.io Ltd
 */

#include <crypto/crypto.h>
#include <kernel/pseudo_ta.h>
#include <fiovb_pta.h>
#if defined(CFG_MX8MM) || defined(CFG_MX8MQ)
#include <imx_sip.h>
#endif

#define PTA_NAME "fiovb.pta"


static TEE_Result invoke_command(void *pSessionContext __unused,
				 uint32_t nCommandID, uint32_t pt,
				 TEE_Param params[TEE_NUM_PARAMS])
{
	const uint32_t exp_pt = TEE_PARAM_TYPES(TEE_PARAM_TYPE_VALUE_INOUT,
						TEE_PARAM_TYPE_NONE,
						TEE_PARAM_TYPE_NONE,
						TEE_PARAM_TYPE_NONE);
	uint32_t secondary;

	if (pt != exp_pt)
		return TEE_ERROR_BAD_PARAMETERS;

#if defined(CFG_MX8MM) || defined(CFG_MX8MQ)
	switch (nCommandID) {
	case PTA_CMD_SET_SECONDARY_BOOT:
		secondary = params[0].value.a;
		call_imx_sip(IMX_SIP_SRC, IMX_SIP_SRC_SET_SECONDARY_BOOT,
			     secondary, 0, 0);
		DMSG("Secondary boot set to %d\n", secondary);
		return TEE_SUCCESS;
	case PTA_CMD_IS_SECONDARY_BOOT:
		secondary = call_imx_sip(IMX_SIP_SRC,
					 IMX_SIP_SRC_IS_SECONDARY_BOOT,
					 0, 0, 0);
		params[0].value.a = secondary;
		DMSG("Secondary boot is %d\n", secondary);
		return TEE_SUCCESS;
	default:
		break;
	}
#endif

	return TEE_ERROR_NOT_IMPLEMENTED;
}

pseudo_ta_register(.uuid = PTA_FIOVB_UUID, .name = PTA_NAME,
		   .flags = PTA_DEFAULT_FLAGS,
		   .invoke_command_entry_point = invoke_command);
