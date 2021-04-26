// SPDX-License-Identifier: BSD-2-Clause
/*
 * Copyright 2017-2020 NXP
 *
 * Peng Fan <peng.fan@nxp.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <assert.h>
#include <drivers/imx_wdog.h>
#include <io.h>
#include <keep.h>
#include <kernel/dt.h>
#include <kernel/boot.h>
#include <kernel/panic.h>
#include <libfdt.h>
#include <mm/core_memprot.h>
#include <mm/core_mmu.h>
#include <util.h>

static bool ext_reset;
static vaddr_t wdog_base;

#ifdef CFG_MX7ULP
static inline void __raw_writel(volatile vaddr_t addr, uint32_t val)
{
	asm volatile("str %1, %0"
		     : : "Qo" (*(volatile uint32_t *)addr), "r" (val));
}

static inline void __raw_writeb(volatile vaddr_t addr, uint8_t val)
{
	asm volatile("strb %1, %0"
		     : : "Qo" (*(volatile uint8_t *)addr), "r" (val));
}
#endif

void imx_wdog_restart(bool external_reset)
{
	uint32_t val __attribute__((unused));

	if (!wdog_base) {
		EMSG("No wdog mapped\n");
		panic();
	}

#ifdef CFG_MX7ULP
	dmb();
	__raw_writel(wdog_base + WDOG_CNT, UNLOCK_SEQ0);
	__raw_writel(wdog_base + WDOG_CNT, UNLOCK_SEQ1);
	dmb();
	/* Wait unlock */
	while (!(io_read8(wdog_base + WDOG_CS + 1) & BIT(3)));

	/* these sequence must be completed within 128 clock cycles after unlock */
	dmb();
	__raw_writel(wdog_base + WDOG_TOVAL, 0x400);
	__raw_writeb(wdog_base + WDOG_WIN, 0);
	__raw_writeb(wdog_base + WDOG_CS + 1, BIT(5) | BIT(0));
	__raw_writeb(wdog_base + WDOG_CS,     BIT(7) | BIT(5));
	dmb();

	/* this wait for configuration is not necessary since the driver will
	 * just wait after this operation anyway. However we will leave it here
	 * for formal purposes
	 */
	while (!(io_read32(wdog_base + WDOG_CS) & WDOG_CS_RCS));
#else
	if (external_reset)
		val = 0x14;
	else
		val = 0x24;

	DMSG("val %x\n", val);

	io_write16(wdog_base + WDT_WCR, val);
	dsb();

	if (io_read16(wdog_base + WDT_WCR) & WDT_WCR_WDE) {
		io_write16(wdog_base + WDT_WSR, WDT_SEQ1);
		io_write16(wdog_base + WDT_WSR, WDT_SEQ2);
	}

	io_write16(wdog_base + WDT_WCR, val);
	io_write16(wdog_base + WDT_WCR, val);
#endif

	/* debug tip: during the while loop is worth checking that the
	 * watchdog counter is progressing as the clock could have been stopped
	 * causing the board to wait forever
	 */
	while (1)
		;
}
DECLARE_KEEP_PAGER(imx_wdog_restart);

#if defined(CFG_DT) && !defined(CFG_EXTERNAL_DTB_OVERLAY)
static const char *const dt_match_table[] = {
	"fsl,imx21-wdt",
	"fsl,imx7ulp-wdt",
};

static TEE_Result imx_wdog_base(vaddr_t *wdog_vbase)
{
	int off = -1;
	vaddr_t vbase = 0;
	void *fdt = NULL;
	size_t size = 0;
	unsigned int i = 0;

	fdt = get_dt();

	if (!fdt)
		return TEE_ERROR_NOT_SUPPORTED;

	for (i = 0; i < ARRAY_SIZE(dt_match_table); i++) {
		off = fdt_node_offset_by_compatible(fdt, 0, dt_match_table[i]);

		for (; off != -FDT_ERR_NOTFOUND;
		     off = fdt_node_offset_by_compatible(fdt, off,
							 dt_match_table[i])) {
			if (_fdt_get_status(fdt, off) != DT_STATUS_DISABLED)
				break;
		}

		if (off >= 0)
			break;
	}

	if (off < 0) {
		EMSG("imx-wdog node not found err = 0x%" PRIx32, off);
		return TEE_ERROR_ITEM_NOT_FOUND;
	}

	ext_reset = dt_have_prop(fdt, off, "fsl,ext-reset-output");

	/* Map the device in the system if not already present */
	if (dt_map_dev(fdt, off, &vbase, &size) < 0) {
		EMSG("imx-wdog device not defined or not enabled");
		return TEE_ERROR_NOT_SUPPORTED;
	}

	if (!vbase) {
		EMSG("Unable to get the imx-wdog base address");
		return TEE_ERROR_ITEM_NOT_FOUND;
	}

	*wdog_vbase = vbase;

	return TEE_SUCCESS;
}
#else
register_phys_mem_pgdir(MEM_AREA_IO_SEC, WDOG_BASE, CORE_MMU_PGDIR_SIZE);
static TEE_Result imx_wdog_base(vaddr_t *wdog_vbase)
{
	*wdog_vbase = (vaddr_t)phys_to_virt(WDOG_BASE, MEM_AREA_IO_SEC);
#if defined(CFG_IMX_WDOG_EXT_RESET)
	ext_reset = true;
#endif
	return TEE_SUCCESS;
}
#endif

static TEE_Result imx_wdog_init(void)
{
#if defined(PLATFORM_FLAVOR_mx7dsabresd) || \
	defined(PLATFORM_FLAVOR_mx7dclsom)

	ext_reset = true;
#endif
	return imx_wdog_base(&wdog_base);
}
driver_init(imx_wdog_init);
