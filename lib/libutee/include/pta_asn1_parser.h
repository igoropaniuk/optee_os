/* SPDX-License-Identifier: BSD-2-Clause */
/*
 * Copyright (c) 2017, Linaro Limited
 */

#ifndef __PTA_ASN1_PARSER_H
#define __PTA_ASN1_PARSER_H

/*
 * Interface to the ASN1 pseudo-TA, which is used for using ASN1 parsing
 * functionality within regular trusted applications
 */

#define ASN1_PARSER_UUID \
		{ 0x273fcb14, 0xe831, 0x4cf2, \
			{ 0x93, 0xc4, 0x76, 0x15, 0xdb, 0xd3, 0x0e, 0x90 } }

/*
 * ASN1 PTA supported commands
 */
#define ASN1_PARSER_CMD_DECODE			0
#define ASN1_PARSER_CMD_ENCODE_PUBKEY		1
#define ASN1_PARSER_CMD_EC_SIGN_ENCODE		2
#define ASN1_PARSER_CMD_EC_SIGN_DECODE		3
#define ASN1_PARSER_CMD_GEN_ROOT_RSA_CERT	4
#define ASN1_PARSER_CMD_GEN_ROOT_EC_CERT	5
#define ASN1_PARSER_CMD_GEN_ATT_RSA_CERT	6
#define ASN1_PARSER_CMD_GEN_ATT_EC_CERT		7

#endif /* __PTA_ASN1_PARSER_H */
