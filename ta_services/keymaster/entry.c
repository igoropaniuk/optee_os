/* SPDX-License-Identifier: BSD-2-Clause */
/* Copyright (c) 2018, Linaro Limited */

#include <keymaster_ta.h>
#include <tee_internal_api.h>

#include "km.h"

static TEE_Result add_rng_entropy(uint32_t pt,
				  TEE_Param __unused params[TEE_NUM_PARAMS])
{
	const uint32_t exp_pt = TEE_PARAM_TYPES(TEE_PARAM_TYPE_MEMREF_INPUT,
						TEE_PARAM_TYPE_NONE,
						TEE_PARAM_TYPE_NONE,
						TEE_PARAM_TYPE_NONE);

	if (pt != exp_pt)
		return TEE_ERROR_BAD_PARAMETERS;

	return km_add_rng_entropy(params[0].memref.buffer,
				  params[0].memref.size);
}

static TEE_Result generate_key(uint32_t pt,
			       TEE_Param __unused param[TEE_NUM_PARAMS])
{

	const uint32_t exp_pt = TEE_PARAM_TYPES(TEE_PARAM_TYPE_MEMREF_INPUT,
						TEE_PARAM_TYPE_NONE,
						TEE_PARAM_TYPE_NONE,
						TEE_PARAM_TYPE_NONE);

	if (pt != exp_pt)
		return TEE_ERROR_BAD_PARAMETERS;

	return TEE_ERROR_NOT_IMPLEMENTED;
}

static TEE_Result import_key(uint32_t pt,
			     TEE_Param __unused param[TEE_NUM_PARAMS])
{

	const uint32_t exp_pt = TEE_PARAM_TYPES(TEE_PARAM_TYPE_MEMREF_INPUT,
						TEE_PARAM_TYPE_NONE,
						TEE_PARAM_TYPE_NONE,
						TEE_PARAM_TYPE_NONE);

	if (pt != exp_pt)
		return TEE_ERROR_BAD_PARAMETERS;

	return TEE_ERROR_NOT_IMPLEMENTED;
}

static TEE_Result get_key_characteristics(uint32_t pt,
					  TEE_Param __unused
					  param[TEE_NUM_PARAMS])
{

	const uint32_t exp_pt = TEE_PARAM_TYPES(TEE_PARAM_TYPE_MEMREF_INPUT,
						TEE_PARAM_TYPE_NONE,
						TEE_PARAM_TYPE_NONE,
						TEE_PARAM_TYPE_NONE);

	if (pt != exp_pt)
		return TEE_ERROR_BAD_PARAMETERS;

	return TEE_ERROR_NOT_IMPLEMENTED;
}

static TEE_Result export_key(uint32_t pt,
			     TEE_Param __unused param[TEE_NUM_PARAMS])
{

	const uint32_t exp_pt = TEE_PARAM_TYPES(TEE_PARAM_TYPE_MEMREF_INPUT,
						TEE_PARAM_TYPE_NONE,
						TEE_PARAM_TYPE_NONE,
						TEE_PARAM_TYPE_NONE);

	if (pt != exp_pt)
		return TEE_ERROR_BAD_PARAMETERS;

	return TEE_ERROR_NOT_IMPLEMENTED;
}

static TEE_Result attest_key(uint32_t pt,
			     TEE_Param __unused param[TEE_NUM_PARAMS])
{

	const uint32_t exp_pt = TEE_PARAM_TYPES(TEE_PARAM_TYPE_MEMREF_INPUT,
						TEE_PARAM_TYPE_NONE,
						TEE_PARAM_TYPE_NONE,
						TEE_PARAM_TYPE_NONE);

	if (pt != exp_pt)
		return TEE_ERROR_BAD_PARAMETERS;

	return TEE_ERROR_NOT_IMPLEMENTED;
}

static TEE_Result upgrade_key(uint32_t pt,
			      TEE_Param __unused param[TEE_NUM_PARAMS])
{

	const uint32_t exp_pt = TEE_PARAM_TYPES(TEE_PARAM_TYPE_MEMREF_INPUT,
						TEE_PARAM_TYPE_NONE,
						TEE_PARAM_TYPE_NONE,
						TEE_PARAM_TYPE_NONE);

	if (pt != exp_pt)
		return TEE_ERROR_BAD_PARAMETERS;

	return TEE_ERROR_NOT_IMPLEMENTED;
}

static TEE_Result delete_key(uint32_t pt,
			     TEE_Param __unused param[TEE_NUM_PARAMS])
{

	const uint32_t exp_pt = TEE_PARAM_TYPES(TEE_PARAM_TYPE_MEMREF_INPUT,
						TEE_PARAM_TYPE_NONE,
						TEE_PARAM_TYPE_NONE,
						TEE_PARAM_TYPE_NONE);

	if (pt != exp_pt)
		return TEE_ERROR_BAD_PARAMETERS;

	return TEE_ERROR_NOT_IMPLEMENTED;
}


static TEE_Result delete_all_keys(uint32_t pt,
				  TEE_Param __unused param[TEE_NUM_PARAMS])
{

	const uint32_t exp_pt = TEE_PARAM_TYPES(TEE_PARAM_TYPE_MEMREF_INPUT,
						TEE_PARAM_TYPE_NONE,
						TEE_PARAM_TYPE_NONE,
						TEE_PARAM_TYPE_NONE);

	if (pt != exp_pt)
		return TEE_ERROR_BAD_PARAMETERS;

	return TEE_ERROR_NOT_IMPLEMENTED;
}

static TEE_Result destroy_attestation_ids(uint32_t pt,
					  TEE_Param __unused
					  param[TEE_NUM_PARAMS])
{

	const uint32_t exp_pt = TEE_PARAM_TYPES(TEE_PARAM_TYPE_MEMREF_INPUT,
						TEE_PARAM_TYPE_NONE,
						TEE_PARAM_TYPE_NONE,
						TEE_PARAM_TYPE_NONE);

	if (pt != exp_pt)
		return TEE_ERROR_BAD_PARAMETERS;

	return TEE_ERROR_NOT_IMPLEMENTED;
}

static TEE_Result operation_begin(uint32_t pt,
				  TEE_Param __unused param[TEE_NUM_PARAMS])
{

	const uint32_t exp_pt = TEE_PARAM_TYPES(TEE_PARAM_TYPE_MEMREF_INPUT,
						TEE_PARAM_TYPE_NONE,
						TEE_PARAM_TYPE_NONE,
						TEE_PARAM_TYPE_NONE);

	if (pt != exp_pt)
		return TEE_ERROR_BAD_PARAMETERS;

	return TEE_ERROR_NOT_IMPLEMENTED;
}


static TEE_Result operation_update(uint32_t pt,
				   TEE_Param __unused param[TEE_NUM_PARAMS])
{

	const uint32_t exp_pt = TEE_PARAM_TYPES(TEE_PARAM_TYPE_MEMREF_INPUT,
						TEE_PARAM_TYPE_NONE,
						TEE_PARAM_TYPE_NONE,
						TEE_PARAM_TYPE_NONE);

	if (pt != exp_pt)
		return TEE_ERROR_BAD_PARAMETERS;

	return TEE_ERROR_NOT_IMPLEMENTED;
}


static TEE_Result operation_finish(uint32_t pt,
				   TEE_Param __unused param[TEE_NUM_PARAMS])
{

	const uint32_t exp_pt = TEE_PARAM_TYPES(TEE_PARAM_TYPE_MEMREF_INPUT,
						TEE_PARAM_TYPE_NONE,
						TEE_PARAM_TYPE_NONE,
						TEE_PARAM_TYPE_NONE);

	if (pt != exp_pt)
		return TEE_ERROR_BAD_PARAMETERS;

	return TEE_ERROR_NOT_IMPLEMENTED;
}

static TEE_Result operation_abort(uint32_t pt,
				  TEE_Param __unused param[TEE_NUM_PARAMS])
{

	const uint32_t exp_pt = TEE_PARAM_TYPES(TEE_PARAM_TYPE_MEMREF_INPUT,
						TEE_PARAM_TYPE_NONE,
						TEE_PARAM_TYPE_NONE,
						TEE_PARAM_TYPE_NONE);

	if (pt != exp_pt)
		return TEE_ERROR_BAD_PARAMETERS;

	return TEE_ERROR_NOT_IMPLEMENTED;
}
TEE_Result TA_CreateEntryPoint(void)
{
	return TEE_SUCCESS;
}

void TA_DestroyEntryPoint(void)
{
}

TEE_Result TA_OpenSessionEntryPoint(uint32_t __unused pt,
				    TEE_Param __unused params[4],
				    void __unused **session)
{
	return TEE_SUCCESS;
}

void TA_CloseSessionEntryPoint(void __unused *sess)
{
}

TEE_Result TA_InvokeCommandEntryPoint(void __unused *sess, uint32_t cmd,
				      uint32_t pt,
				      TEE_Param params[TEE_NUM_PARAMS])
{
	switch (cmd) {
	case KEYMASTER_CMD_ADD_RNG_ENTROPY:
		return add_rng_entropy(pt, params);
	case KEYMASTER_CMD_GENERATE_KEY:
		return generate_key(pt, params);
	case KEYMASTER_CMD_IMPORT_KEY:
		return import_key(pt, params);
	case KEYMASTER_CMD_EXPORT_KEY:
		return export_key(pt, params);
	case KEYMASTER_CMD_ATTEST_KEY:
		return attest_key(pt, params);
	case KEYMASTER_CMD_UPGRADE_KEY:
		return upgrade_key(pt, params);
	case KEYMASTER_CMD_DELETE_KEY:
		return delete_key(pt, params);
	case KEYMASTER_CMD_DELETE_ALL_KEYS:
		return delete_all_keys(pt, params);
	case KEYMASTER_CMD_GET_KEY_CHARACTERISTICS:
		return get_key_characteristics(pt, params);
	case KEYMASTER_CMD_DESTROY_ATTESTATION_IDS:
		return destroy_attestation_ids(pt, params);
	case KEYMASTER_CMD_BEGIN:
		return operation_begin(pt, params);
	case KEYMASTER_CMD_UPDATE:
		return operation_update(pt, params);
	case KEYMASTER_CMD_FINISH:
		return operation_finish(pt, params);
	case KEYMASTER_CMD_ABORT:
		return operation_abort(pt, params);
	default:
		EMSG("Command ID 0x%x is not supported", cmd);
		return TEE_ERROR_NOT_SUPPORTED;
	}
}
