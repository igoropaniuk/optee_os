/* SPDX-License-Identifier: BSD-2-Clause */
/*
 * Copyright (c) Microsoft Corporation. All rights reserved.
 */

#ifndef __IMX_SIP_H__
#define __IMX_SIP_H__

#define IMX_SIP_PL310_ENABLE			1
#define IMX_SIP_PL310_DISABLE			2
#define IMX_SIP_PL310_ENABLE_WRITEBACK		3
#define IMX_SIP_PL310_DISABLE_WRITEBACK		4
#define IMX_SIP_PL310_ENABLE_WFLZ		5

#define IMX_SIP_SRC				0xC2000005
#define IMX_SIP_SRC_SET_SECONDARY_BOOT		0x10
#define IMX_SIP_SRC_IS_SECONDARY_BOOT		0x11

unsigned long call_imx_sip(unsigned long id, unsigned long reg0,
			   unsigned long reg1, unsigned long reg2,
			   unsigned long reg3);

#endif /* __IMX_SIP_H__ */
