// SPDX-License-Identifier: BSD-2-Clause
/*
 * Copyright (C) Foundries Ltd. 2022 - All Rights Reserved
 * Author: Igor Opaniuk <igor.opaniuk@foundries.io>
 */

#include <drivers/stm32_i2c.h>
#include <i2c_native.h>
#include <kernel/delay.h>
#include <kernel/dt.h>
#include <kernel/boot.h>
#include <kernel/panic.h>
#include <libfdt.h>
#include <phNxpEsePal_i2c.h>

/* Expect a single SE050 instance */
static struct i2c_handle_s i2c_handle;
static uint32_t se05x_i2c_addr;

static int dt_get_se05x_node(void *fdt)
{
	static int node = -FDT_ERR_BADOFFSET;

	if (node == -FDT_ERR_BADOFFSET)
		node = fdt_node_offset_by_compatible(fdt, -1, "nxp,se050");

	return node;
}

/*
 * Get SE050 and its I2C bus configuration from the device tree.
 * Return 0 on success, 1 if no PMIC node found and a negative value
 * otherwise
 */
static int dt_se05x_i2c_config(struct dt_node_info *i2c_info,
			       struct stm32_pinctrl **pinctrl,
			       size_t *pinctrl_count,
			       struct stm32_i2c_init_s *init)
{
	int se05x_node = 0;
	int i2c_node = 0;
	void *fdt = NULL;
	const fdt32_t *cuint = NULL;

	fdt = get_embedded_dt();
	if (!fdt)
		return -FDT_ERR_NOTFOUND;

	se05x_node = dt_get_se05x_node(fdt);
	if (se05x_node < 0)
		return 1;

	cuint = fdt_getprop(fdt, se05x_node, "reg", NULL);
	if (!cuint)
		return -FDT_ERR_NOTFOUND;

	se05x_i2c_addr = fdt32_to_cpu(*cuint) << 1;
	if (se05x_i2c_addr > UINT16_MAX)
		return -FDT_ERR_BADVALUE;

	i2c_node = fdt_parent_offset(fdt, se05x_node);
	if (i2c_node < 0)
		return -FDT_ERR_NOTFOUND;

	_fdt_fill_device_info(fdt, i2c_info, i2c_node);
	if (!i2c_info->reg)
		return -FDT_ERR_NOTFOUND;

	DMSG("stm32_i2c_get_setup_from_fdt()");
	if (stm32_i2c_get_setup_from_fdt(fdt, i2c_node, init,
					 pinctrl, pinctrl_count))
		panic();

	return 0;
}

int native_i2c_init(void)
{
	int ret = 0;
	struct dt_node_info i2c_info = { };
	struct i2c_handle_s *i2c = &i2c_handle;
	struct stm32_pinctrl *pinctrl = NULL;
	size_t pin_count = 0;
	struct stm32_i2c_init_s i2c_init = { };

	DMSG("Check DT for SE05X I2C device node.");
	ret = dt_se05x_i2c_config(&i2c_info, &pinctrl, &pin_count, &i2c_init);
	if (ret) {
		EMSG("SE05X I2C device tree configuration failed %d", ret);
		panic();
	}
	DMSG("Obtained SE05X I2C device node from DT, slave address = 0x%x, i2c_info.reg = 0x%" PRIxPA,
	     se05x_i2c_addr, i2c_info.reg);

	/* Initialize PMIC I2C */
	i2c->base.pa = i2c_info.reg;
	i2c->base.va = (vaddr_t)phys_to_virt(i2c->base.pa, MEM_AREA_IO_NSEC, 1);
	assert(i2c->base.va);
	i2c->dt_status = i2c_info.status;
	i2c->clock = i2c_init.clock;
	i2c->i2c_state = I2C_STATE_RESET;
	i2c_init.own_address1 = se05x_i2c_addr;
	i2c_init.analog_filter = true;
	i2c_init.digital_filter_coef = 0;

	i2c->pinctrl = pinctrl;
	i2c->pinctrl_count = pin_count;

	ret = stm32_i2c_init(i2c, &i2c_init);
	if (ret) {
		EMSG("SE05X I2C init 0x%" PRIxPA ": %d", i2c_info.reg, ret);
		panic();
	}
	DMSG("SE05X I2C device is successfully initialized.");

	if (!stm32_i2c_is_device_ready(i2c, se05x_i2c_addr, 5, 500)) {
		EMSG("SE05X I2C device is not ready 0x%" PRIxPA ": %d",
		     i2c_info.reg, ret);
		panic();
	}

	DMSG("SE05X I2C device is ready.");

	return 0;
}

TEE_Result native_i2c_transfer(struct rpc_i2c_request *req,
			       size_t *bytes)
{
	TEE_Result ret = TEE_ERROR_GENERIC;
	struct i2c_handle_s *i2c = &i2c_handle;

	if (req->mode == RPC_I2C_MODE_READ)
		ret = stm32_i2c_master_receive(i2c, se05x_i2c_addr,
					       req->buffer, req->buffer_len,
					       100);
	else
		ret = stm32_i2c_master_transmit(i2c, se05x_i2c_addr,
						req->buffer, req->buffer_len,
						100);

	if (!ret)
		*bytes = req->buffer_len;

	return ret;
}
