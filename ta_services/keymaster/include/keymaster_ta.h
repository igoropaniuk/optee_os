/* SPDX-License-Identifier: BSD-2-Clause */
/* Copyright (c) 2018, Linaro Limited */

#ifndef __KEYMASTER_TA_H
#define __KEYMASTER_TA_H

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

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


enum keymaster_tag_type_t {
	KM_INVALID = (int)(0u << 28),
	KM_ENUM = (int)(1u << 28),
	KM_ENUM_REP = (int)(2u << 28),
	KM_UINT = (int)3u << 28,
	KM_UINT_REP = (int)(4u << 28),
	KM_ULONG = (int)(5u << 28),
	KM_DATE = (int)(6u << 28),
	KM_BOOL = (int)(7u << 28),
	KM_BIGNUM = (int)(8u << 28),
	KM_BYTES = (int)(9u << 28),
	KM_ULONG_REP = (int)(10u << 28)
};

enum keymaster_tag_t {
	KM_TAG_INVALID = KM_INVALID | 0,
	KM_TAG_PURPOSE = KM_ENUM_REP | 1,
	KM_TAG_ALGORITHM = KM_ENUM | 2,
	KM_TAG_KEY_SIZE = KM_UINT | 3,
	KM_TAG_BLOCK_MODE = KM_ENUM_REP | 4,
	KM_TAG_DIGEST = KM_ENUM_REP | 5,
	KM_TAG_PADDING = KM_ENUM_REP | 6,
	KM_TAG_CALLER_NONCE = KM_BOOL | 7,
	KM_TAG_MIN_MAC_LENGTH = KM_UINT | 8,
	KM_TAG_KDF = KM_ENUM_REP | 9,
	KM_TAG_EC_CURVE = KM_ENUM | 10,

	/* Algorithm-specific. */
	KM_TAG_RSA_PUBLIC_EXPONENT = KM_ULONG | 200,
	KM_TAG_ECIES_SINGLE_HASH_MODE = KM_BOOL | 201,
	KM_TAG_INCLUDE_UNIQUE_ID = KM_BOOL | 202,
	KM_TAG_BLOB_USAGE_REQUIREMENTS = KM_ENUM | 301,
	KM_TAG_BOOTLOADER_ONLY = KM_BOOL | 302,

	/* Key validity period */
	KM_TAG_ACTIVE_DATETIME = KM_DATE | 400,
	KM_TAG_ORIGINATION_EXPIRE_DATETIME = KM_DATE | 401,
	KM_TAG_USAGE_EXPIRE_DATETIME = KM_DATE | 402,
	KM_TAG_MIN_SECONDS_BETWEEN_OPS = KM_UINT | 403,
	KM_TAG_MAX_USES_PER_BOOT = KM_UINT | 404,

	/* User authentication */
	KM_TAG_ALL_USERS = KM_BOOL | 500,
	KM_TAG_USER_ID = KM_UINT | 501,
	KM_TAG_USER_SECURE_ID = KM_ULONG_REP | 502,
	KM_TAG_NO_AUTH_REQUIRED = KM_BOOL | 503,
	KM_TAG_USER_AUTH_TYPE = KM_ENUM | 504,
	KM_TAG_AUTH_TIMEOUT = KM_UINT | 505,
	KM_TAG_ALLOW_WHILE_ON_BODY = KM_BOOL | 506,

	/* Application access control */
	KM_TAG_ALL_APPLICATIONS = KM_BOOL | 600,
	KM_TAG_APPLICATION_ID = KM_BYTES | 601,
	KM_TAG_EXPORTABLE = KM_BOOL | 602,

	/*
	 * Semantically unenforceable tags, either because they have no
	 * specific meaning or because they're informational only.
	 */
	KM_TAG_APPLICATION_DATA = KM_BYTES | 700,
	KM_TAG_CREATION_DATETIME = KM_DATE | 701,
	KM_TAG_ORIGIN = KM_ENUM | 702,
	KM_TAG_ROLLBACK_RESISTANT = KM_BOOL | 703,
	KM_TAG_ROOT_OF_TRUST = KM_BYTES | 704,
	KM_TAG_OS_VERSION = KM_UINT | 705,
	KM_TAG_OS_PATCHLEVEL = KM_UINT | 706,
	KM_TAG_UNIQUE_ID = KM_BYTES | 707,
	KM_TAG_ATTESTATION_CHALLENGE = KM_BYTES | 708,
	KM_TAG_ATTESTATION_APPLICATION_ID = KM_BYTES | 709,

	/* Tags used only to provide data to or receive data from operations */
	KM_TAG_ASSOCIATED_DATA = KM_BYTES | 1000,
	KM_TAG_NONCE = KM_BYTES | 1001,
	KM_TAG_AUTH_TOKEN = KM_BYTES | 1002,
	KM_TAG_MAC_LENGTH = KM_UINT | 1003,
	KM_TAG_RESET_SINCE_ID_ROTATION = KM_BOOL | 1004,
};

/*
 * Algorithms that may be provided by keymaster implementations.
 */

enum keymaster_algorithm_t {
	KM_ALGORITHM_RSA = 1,
	// KM_ALGORITHM_DSA = 2, -- Removed, do not re-use value 2.
	KM_ALGORITHM_EC = 3,
	KM_ALGORITHM_AES = 32,
	KM_ALGORITHM_HMAC = 128,
};

/*
 * Digests provided by keymaster implementations.
 */
enum keymaster_digest_t {
	KM_DIGEST_NONE = 0,
	KM_DIGEST_MD5 = 1,
	KM_DIGEST_SHA1 = 2,
	KM_DIGEST_SHA_2_224 = 3,
	KM_DIGEST_SHA_2_256 = 4,
	KM_DIGEST_SHA_2_384 = 5,
	KM_DIGEST_SHA_2_512 = 6,
};

struct keymaster_blob_t {
	uint8_t *data;
	size_t data_length;
};

struct keymaster_key_param_t {
	enum keymaster_tag_t tag;
	union {
		uint32_t enumerated;
		bool boolean;
		uint32_t integer;
		uint64_t long_integer;
		uint64_t date_time;
		struct keymaster_blob_t blob;
	} key_param;
};

struct keymaster_key_param_set_t {
	struct keymaster_key_param_t *params;
	size_t length;
};

/*
 * Parameters that define a key's characteristics, including authorized modes
 * of usage and access control restrictions.  The parameters are divided into
 * two categories, those that are enforced by
 * secure hardware, and those that are not.  For a software-only keymaster
 * implementation the enforced array must NULL.
 * Hardware implementations must enforce everything in the enforced
 * array.
 */
struct keymaster_key_characteristics_t {
	struct keymaster_key_param_set_t hw_enforced;
	struct keymaster_key_param_set_t sw_enforced;
};

#endif /*__KEYMASTER_TA_H*/
