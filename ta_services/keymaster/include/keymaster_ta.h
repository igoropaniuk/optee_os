/* SPDX-License-Identifier: BSD-2-Clause */
/* Copyright (c) 2018, Linaro Limited */

#ifndef __KEYMASTER_TA_H
#define __KEYMASTER_TA_H

#define TA_KEYMASTER_UUID { 0xd36b30c7, 0x5a5f, 0x472c, \
			    {0xaf, 0x97, 0x7f, 0x38, 0xa2, 0xed, 0xab, 0x7d } }

/*
 * Add (re-seed) caller-provided entropy to the RNG pool. Keymaster
 * implementations need to securely mix the provided entropy into their
 * pool, which also must contain internally-generated entropy from a
 * hardware random number generator.
 *
 * in	params[0].memref: entropy input data
 */
#define KEYMASTER_CMD_ADD_RNG_ENTROPY			0

/*
 * Generates a new cryptographic key, specifying associated authorizations,
 * which are permanently bound to the key.
 *
 * params TODO:
 */
#define KEYMASTER_CMD_GENERATE_KEY			1

/*
 * Imports key material into Keymaster hardware.
 *
 * params TODO:
 */
#define KEYMASTER_CMD_IMPORT_KEY 			2

/*
 * Exports a public key from a Keymaster RSA or EC key pair.
 *
 * params TODO:
 */
#define KEYMASTER_CMD_EXPORT_KEY			3

/*
 * Generates a new cryptographic key, specifying associated authorizations,
 * which are permanently bound to the key.
 *
 * params TODO:
 */
#define KEYMASTER_CMD_ATTEST_KEY			4
/*
 * Generates a new cryptographic key, specifying associated authorizations,
 * which are permanently bound to the key.
 *
 * params TODO:
 */
#define KEYMASTER_CMD_UPGRADE_KEY			5
/*
 * Generates a new cryptographic key, specifying associated authorizations,
 * which are permanently bound to the key.
 *
 * params TODO:
 */
#define KEYMASTER_CMD_DELETE_KEY			6
/*
 * Generates a new cryptographic key, specifying associated authorizations,
 * which are permanently bound to the key.
 *
 * params TODO:
 */
#define KEYMASTER_CMD_DELETE_ALL_KEYS			7
/*
 * Generates a new cryptographic key, specifying associated authorizations,
 * which are permanently bound to the key.
 *
 * params TODO:
 */
#define KEYMASTER_CMD_GET_KEY_CHARACTERISTICS		8
/*
 * Generates a new cryptographic key, specifying associated authorizations,
 * which are permanently bound to the key.
 *
 * params TODO:
 */
#define KEYMASTER_CMD_DESTROY_ATTESTATION_IDS		9

/*
 * Begins a cryptographic operation, using the specified key, for the specified
 * purpose, with the specified parameters (as appropriate), and returns an
 * operation handle that is used with update and finish to complete the
 * operation. The operation handle is also used as the "challenge" token in
 * authenticated operations, and for such operations is included in the
 * challenge field of the authentication token.
 *
 * params TODO:
 */

#define KEYMASTER_CMD_BEGIN				10

/*
 * Provides data to process in an ongoing operation started with begin.
 * The operation is specified by the operationHandle parameter.
 *
 * params TODO:
 */
#define KEYMASTER_CMD_UPDATE				11

/*
 * Finishes an ongoing operation started with begin, processing all of
 * the as-yet-unprocessed data provided by update(s).
 * This method is the last one called in an operation, so all processed
 * data is returned.
 *
 * params TODO:
 */
#define KEYMASTER_CMD_FINISH				12
/*
 * Aborts the in-progress operation
 *
 * params TODO:
 */
#define KEYMASTER_CMD_ABORT				13

#endif /*__KEYMASTER_TA_H*/
