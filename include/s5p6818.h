/*
 * Copyright (C) 2017
 * Author: metro94 <flattiles@gmail.com>
 *
 * Version: v1.0
 * --- Update time: 02/07/2017
 * --- Description: First build; header for Nexell S5P6818 SoC
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __S5P6818_H__
#define __S5P6818_H__

// General settings

#define CPU_NUMBERS			8

#define INTERNAL_SRAM_BASE		0xFFFF0000
#define INTERNAL_SRAM_SIZE		0x00010000

#define STACK_SIZE			0x200

#ifndef __COMPILING_ASM

#include <common.h>

// System Control settings

#include <nexell/nx_sysctrl.h>

struct nx_sysctrl_regs {
	volatile uint32_t \
		clk_mode[2],			// 0x0 ~ 0x4
		pll_set[4],			// 0x8 ~ 0x14
		__rsvd0[(0x20 - 0x18) / 4],	// 0x18 ~ 0x1C
		clk_div[9],			// 0x20 ~ 0x40
		__rsvd1,			// 0x44
		pll_set_sscg[4],		// 0x48 ~ 0x54
		__rsvd2[(0x200 - 0x58) / 4],	// 0x58 ~ 0x1FC
		gpio_wakeup_rise_enb,		// 0x200
		gpio_wakeup_fall_enb,		// 0x204
		gpio_reset_enb,			// 0x208
		gpio_wakeup_enb,		// 0x20C
		gpio_int_enb,			// 0x210
		gpio_int_pend,			// 0x214
		reset_status,			// 0x218
		int_enb,			// 0x21C
		int_pend,			// 0x220
		pwr_ctrl,			// 0x224
		pwr_mode,			// 0x228
		__rsvd3,			// 0x22C
		scratch[3],			// 0x230 ~ 0x238
		sys_rst_config,			// 0x23C
		__rsvd4[(0x2A0 - 0x240) / 4],	// 0x240 ~ 0X29C
		cpu_power_down_req,		// 0x2A0
		cpu_power_on_req,		// 0x2A4
		cpu_reset_mode,			// 0x2A8
		cpu_warm_reset_req,		// 0x2AC
		__rsvd5,			// 0x2B0
		cpu_status,			// 0x2B4
		__rsvd6[(0x400 - 0x2B8) / 4];	// 0x2B8 ~ 0x3FC
};

static struct nx_sysctrl_regs * const nx_sysctrl = (struct nx_sysctrl_regs *)0xC0010000;

// Tie-off settings

#include <nexell/nx_tieoff.h>

#define NX_TIEOFF_REG_NUMBERS		132

static nx_tieoff_regs * const nx_tieoff = (nx_tieoff_regs *)0xC0011000;

// IP Reset settings

#include <nexell/nx_iprst.h>

#define NX_IPRST_ID_NUMBERS		70

enum nx_iprst_id {
	NX_IPRST_ID_AC97 = 0,
	NX_IPRST_ID_CPU_1,
	NX_IPRST_ID_CPU_2,
	NX_IPRST_ID_CPU_3,
	NX_IPRST_ID_WD_1,
	NX_IPRST_ID_WD_2,
	NX_IPRST_ID_WD_3,
	NX_IPRST_ID_CRYPTO,
	NX_IPRST_ID_DEINTERLACE,
	NX_IPRST_ID_DISPLAY_TOP,
	NX_IPRST_ID_DISPLAY_DUAL,
	NX_IPRST_ID_DISPLAY_RESCONV,
	NX_IPRST_ID_LCDIF,
	NX_IPRST_ID_HDMI,
	NX_IPRST_ID_HDMI_VIDEO,
	NX_IPRST_ID_HDMI_SPDIF,
	NX_IPRST_ID_HDMI_TMDS,
	NX_IPRST_ID_HDMI_PHY,
	NX_IPRST_ID_LVDS,
	NX_IPRST_ID_ECID,
	NX_IPRST_ID_I2C_0,
	NX_IPRST_ID_I2C_1,
	NX_IPRST_ID_I2C_2,
	NX_IPRST_ID_I2S_0,
	NX_IPRST_ID_I2S_1,
	NX_IPRST_ID_I2S_2,
	NX_IPRST_ID_DREX_APB,
	NX_IPRST_ID_DREX_AXI,
	NX_IPRST_ID_DREX_CORE,
	NX_IPRST_ID_MIPI,
	NX_IPRST_ID_MIPI_DSI,
	NX_IPRST_ID_MIPI_CSI,
	NX_IPRST_ID_MIPI_PHY_SLAVE,
	NX_IPRST_ID_MIPI_PHY_MASTER,
	NX_IPRST_ID_MPEG_TS,
	NX_IPRST_ID_PDM,
	NX_IPRST_ID_TIMER,
	NX_IPRST_ID_PWM,
	NX_IPRST_ID_SCALER,
	NX_IPRST_ID_SDMMC_0,
	NX_IPRST_ID_SDMMC_1,
	NX_IPRST_ID_SDMMC_2,
	NX_IPRST_ID_SPDIF_RX,
	NX_IPRST_ID_SPDIF_TX,
	NX_IPRST_ID_SSP_0_APB,
	NX_IPRST_ID_SSP_0_CORE,
	NX_IPRST_ID_SSP_1_APB,
	NX_IPRST_ID_SSP_1_CORE,
	NX_IPRST_ID_SSP_2_APB,
	NX_IPRST_ID_SSP_2_CORE,
	NX_IPRST_ID_UART_0,
	NX_IPRST_ID_UART_1,
	NX_IPRST_ID_UART_2,
	NX_IPRST_ID_UART_3,
	NX_IPRST_ID_UART_4,
	NX_IPRST_ID_UART_5,
	NX_IPRST_ID_USB_HOST,
	NX_IPRST_ID_USB_OTG,
	NX_IPRST_ID_WDT_APB,
	NX_IPRST_ID_WDT_POR,
	NX_IPRST_ID_ADC,
	NX_IPRST_ID_CODA960_AXI,
	NX_IPRST_ID_CODA960_APB,
	NX_IPRST_ID_CODA960_CORE,
	NX_IPRST_ID_GMAC,
	NX_IPRST_ID_MALI400,
	NX_IPRST_ID_PPM,
	NX_IPRST_ID_VIP_0,
	NX_IPRST_ID_VIP_1,
	NX_IPRST_ID_RSVD
};

static nx_iprst_regs * const nx_iprst_block = (nx_iprst_regs *)0xC0012000;

// Clock Generator settings

#include <nexell/nx_clkgen.h>

#define NX_CLKGEN_ID_NUMBERS		47

enum nx_clkgen_id {
	NX_CLKGEN_ID_CODA960 = 0,
	NX_CLKGEN_ID_CRYPTO,
	NX_CLKGEN_ID_I2C_0,
	NX_CLKGEN_ID_I2C_1,
	NX_CLKGEN_ID_I2C_2,
	NX_CLKGEN_ID_GR3D,
	NX_CLKGEN_ID_MPEG_TS,
	NX_CLKGEN_ID_PDM,
	NX_CLKGEN_ID_SCALER,
	NX_CLKGEN_ID_DEINTERLACE,
	NX_CLKGEN_ID_MLC_0,
	NX_CLKGEN_ID_MLC_1,
	NX_CLKGEN_ID_MIPI_CSI,
	NX_CLKGEN_ID_PPM,
	NX_CLKGEN_ID_PWM_0,
	NX_CLKGEN_ID_PWM_1,
	NX_CLKGEN_ID_PWM_2,
	NX_CLKGEN_ID_PWM_3,
	NX_CLKGEN_ID_TIMER_0,
	NX_CLKGEN_ID_TIMER_1,
	NX_CLKGEN_ID_TIMER_2,
	NX_CLKGEN_ID_TIMER_3,
	NX_CLKGEN_ID_SDMMC_0,
	NX_CLKGEN_ID_SDMMC_1,
	NX_CLKGEN_ID_SDMMC_2,
	NX_CLKGEN_ID_SPDIF_TX,
	NX_CLKGEN_ID_SSP_0,
	NX_CLKGEN_ID_SSP_1,
	NX_CLKGEN_ID_SSP_2,
	NX_CLKGEN_ID_UART_0,
	NX_CLKGEN_ID_UART_1,
	NX_CLKGEN_ID_UART_2,
	NX_CLKGEN_ID_UART_3,
	NX_CLKGEN_ID_UART_4,
	NX_CLKGEN_ID_UART_5,
	NX_CLKGEN_ID_VIP_0,
	NX_CLKGEN_ID_VIP_1,
	NX_CLKGEN_ID_GMAC,
	NX_CLKGEN_ID_I2S_0,
	NX_CLKGEN_ID_I2S_1,
	NX_CLKGEN_ID_I2S_2,
	NX_CLKGEN_ID_USB_HOST_OTG,
	NX_CLKGEN_ID_DPC_0,
	NX_CLKGEN_ID_DPC_1,
	NX_CLKGEN_ID_LVDS,
	NX_CLKGEN_ID_HDMI,
	NX_CLKGEN_ID_MIPI_DSI
};

static struct nx_clkgen_info const nx_clkgen_table[] = {
	// NX_CLKGEN_ID_CODA960
	{
		(struct nx_clkgen_regs *)0xC00C7000,
		0,
		NX_CLKGEN_MODE_BCLK | NX_CLKGEN_MODE_PCLK
	},
	// NX_CLKGEN_ID_CRYPTO
	{
		(struct nx_clkgen_regs *)0xC00C6000,
		0,
		NX_CLKGEN_MODE_PCLK
	},
	// NX_CLKGEN_ID_I2C_0
	{
		(struct nx_clkgen_regs *)0xC00AE000,
		0,
		NX_CLKGEN_MODE_PCLK
	},
	// NX_CLKGEN_ID_I2C_1
	{
		(struct nx_clkgen_regs *)0xC00AF000,
		0,
		NX_CLKGEN_MODE_PCLK
	},
	// NX_CLKGEN_ID_I2C_2
	{
		(struct nx_clkgen_regs *)0xC00B0000,
		0,
		NX_CLKGEN_MODE_PCLK
	},
	// NX_CLKGEN_ID_GR3D
	{
		(struct nx_clkgen_regs *)0xC00C3000,
		0,
		NX_CLKGEN_MODE_BCLK
	},
	// NX_CLKGEN_ID_MPEG_TS
	{
		(struct nx_clkgen_regs *)0xC00CB700,
		0,
		NX_CLKGEN_MODE_BCLK
	},
	// NX_CLKGEN_ID_PDM
	{
		(struct nx_clkgen_regs *)0xC00CB000,
		0,
		NX_CLKGEN_MODE_BCLK | NX_CLKGEN_MODE_PCLK
	},
	// NX_CLKGEN_ID_SCALER
	{
		(struct nx_clkgen_regs *)0xC00B6000,
		0,
		NX_CLKGEN_MODE_BCLK
	},
	// NX_CLKGEN_ID_DEINTERLACE
	{
		(struct nx_clkgen_regs *)0xC00B5000,
		0,
		NX_CLKGEN_MODE_BCLK
	},
	// NX_CLKGEN_ID_MLC_0
	{
		(struct nx_clkgen_regs *)0xC01023C0,
		0,
		NX_CLKGEN_MODE_BCLK | NX_CLKGEN_MODE_PCLK
	},
	// NX_CLKGEN_ID_MLC_1
	{
		(struct nx_clkgen_regs *)0xC01027C0,
		0,
		NX_CLKGEN_MODE_BCLK | NX_CLKGEN_MODE_PCLK
	},
	// NX_CLKGEN_ID_MIPI_CSI
	{
		(struct nx_clkgen_regs *)0xC00CA000,
		1,
		NX_CLKGEN_MODE_CLKGEN
	},
	// NX_CLKGEN_ID_PPM
	{
		(struct nx_clkgen_regs *)0xC00C4000,
		1,
		NX_CLKGEN_MODE_CLKGEN
	},
	// NX_CLKGEN_ID_PWM_0
	{
		(struct nx_clkgen_regs *)0xC00BA000,
		1,
		NX_CLKGEN_MODE_CLKGEN
	},
	// NX_CLKGEN_ID_PWM_1
	{
		(struct nx_clkgen_regs *)0xC00BE000,
		1,
		NX_CLKGEN_MODE_CLKGEN
	},
	// NX_CLKGEN_ID_PWM_2
	{
		(struct nx_clkgen_regs *)0xC00BF000,
		1,
		NX_CLKGEN_MODE_CLKGEN
	},
	// NX_CLKGEN_ID_PWM_3
	{
		(struct nx_clkgen_regs *)0xC00C0000,
		1,
		NX_CLKGEN_MODE_CLKGEN
	},
	// NX_CLKGEN_ID_TIMER_0
	{
		(struct nx_clkgen_regs *)0xC00B9000,
		1,
		NX_CLKGEN_MODE_CLKGEN
	},
	// NX_CLKGEN_ID_TIMER_1
	{
		(struct nx_clkgen_regs *)0xC00BB000,
		1,
		NX_CLKGEN_MODE_CLKGEN
	},
	// NX_CLKGEN_ID_TIMER_2
	{
		(struct nx_clkgen_regs *)0xC00BC000,
		1,
		NX_CLKGEN_MODE_CLKGEN
	},
	// NX_CLKGEN_ID_TIMER_3
	{
		(struct nx_clkgen_regs *)0xC00BD000,
		1,
		NX_CLKGEN_MODE_CLKGEN
	},
	// NX_CLKGEN_ID_SDMMC_0
	{
		(struct nx_clkgen_regs *)0xC00C5000,
		1,
		NX_CLKGEN_MODE_CLKGEN | NX_CLKGEN_MODE_PCLK
	},
	// NX_CLKGEN_ID_SDMMC_1
	{
		(struct nx_clkgen_regs *)0xC00CC000,
		1,
		NX_CLKGEN_MODE_CLKGEN | NX_CLKGEN_MODE_PCLK
	},
	// NX_CLKGEN_ID_SDMMC_2
	{
		(struct nx_clkgen_regs *)0xC00CD000,
		1,
		NX_CLKGEN_MODE_CLKGEN | NX_CLKGEN_MODE_PCLK
	},
	// NX_CLKGEN_ID_SPDIF_TX
	{
		(struct nx_clkgen_regs *)0xC00B8000,
		1,
		NX_CLKGEN_MODE_CLKGEN
	},
	// NX_CLKGEN_ID_SSP_0
	{
		(struct nx_clkgen_regs *)0xC00AC000,
		1,
		NX_CLKGEN_MODE_CLKGEN
	},
	// NX_CLKGEN_ID_SSP_1
	{
		(struct nx_clkgen_regs *)0xC00AD000,
		1,
		NX_CLKGEN_MODE_CLKGEN
	},
	// NX_CLKGEN_ID_SSP_2
	{
		(struct nx_clkgen_regs *)0xC00A7000,
		1,
		NX_CLKGEN_MODE_CLKGEN
	},
	// NX_CLKGEN_ID_UART_0
	{
		(struct nx_clkgen_regs *)0xC00A9000,
		1,
		NX_CLKGEN_MODE_CLKGEN
	},
	// NX_CLKGEN_ID_UART_1
	{
		(struct nx_clkgen_regs *)0xC00A8000,
		1,
		NX_CLKGEN_MODE_CLKGEN
	},
	// NX_CLKGEN_ID_UART_2
	{
		(struct nx_clkgen_regs *)0xC00AA000,
		1,
		NX_CLKGEN_MODE_CLKGEN
	},
	// NX_CLKGEN_ID_UART_3
	{
		(struct nx_clkgen_regs *)0xC00AB000,
		1,
		NX_CLKGEN_MODE_CLKGEN
	},
	// NX_CLKGEN_ID_UART_4
	{
		(struct nx_clkgen_regs *)0xC006E000,
		1,
		NX_CLKGEN_MODE_CLKGEN
	},
	// NX_CLKGEN_ID_UART_5
	{
		(struct nx_clkgen_regs *)0xC0084000,
		1,
		NX_CLKGEN_MODE_CLKGEN
	},
	// NX_CLKGEN_ID_VIP_0
	{
		(struct nx_clkgen_regs *)0xC00C1000,
		1,
		NX_CLKGEN_MODE_CLKGEN
	},
	// NX_CLKGEN_ID_VIP_1
	{
		(struct nx_clkgen_regs *)0xC00C2000,
		1,
		NX_CLKGEN_MODE_CLKGEN
	},
	// NX_CLKGEN_ID_GMAC
	{
		(struct nx_clkgen_regs *)0xC00C8000,
		2,
		NX_CLKGEN_MODE_CLKGEN
	},
	// NX_CLKGEN_ID_I2S_0
	{
		(struct nx_clkgen_regs *)0xC00B2000,
		2,
		NX_CLKGEN_MODE_CLKGEN
	},
	// NX_CLKGEN_ID_I2S_1
	{
		(struct nx_clkgen_regs *)0xC00B3000,
		2,
		NX_CLKGEN_MODE_CLKGEN
	},
	// NX_CLKGEN_ID_I2S_2
	{
		(struct nx_clkgen_regs *)0xC00B4000,
		2,
		NX_CLKGEN_MODE_CLKGEN
	},
	// NX_CLKGEN_ID_USB_HOST_OTG
	{
		(struct nx_clkgen_regs *)0xC006B000,
		2,
		NX_CLKGEN_MODE_CLKGEN
	},
	// NX_CLKGEN_ID_DPC_0
	{
		(struct nx_clkgen_regs *)0xC0102BC0,
		2,
		NX_CLKGEN_MODE_CLKGEN
	},
	// NX_CLKGEN_ID_DPC_1
	{
		(struct nx_clkgen_regs *)0xC0102FC0,
		2,
		NX_CLKGEN_MODE_CLKGEN
	},
	// NX_CLKGEN_ID_LVDS
	{
		(struct nx_clkgen_regs *)0xC0108000,
		2,
		NX_CLKGEN_MODE_CLKGEN
	},
	// NX_CLKGEN_ID_HDMI
	{
		(struct nx_clkgen_regs *)0xC0109000,
		2,
		NX_CLKGEN_MODE_CLKGEN
	},
	// NX_CLKGEN_ID_MIPI_DSI
	{
		(struct nx_clkgen_regs *)0xC0105000,
		2,
		NX_CLKGEN_MODE_CLKGEN
	}
};

// Bus settings

#include <arm/cci_400.h>

static struct cci_400_regs * const cci_400 = (struct cci_400_regs *)0xE0090000;

enum BUS_ID {
	BUS_ID_CORESIGHT = 0,
	BUS_ID_CODA960,
	BUS_ID_TOP,
	BUS_ID_CPU_CLUSTER_0,
	BUS_ID_CPU_CLUSTER_1
};

// TrustZone settings

#include <arm/tzc_380.h>

static struct tzc_380_regs * const tzasc = (struct tzc_380_regs *)0xC00E5000;

#include <arm/bp_147.h>

#define TZPC_NUMBERS			7

static struct bp_147_regs * const tzpc = (struct bp_147_regs *)0xC0301000;

// GIC settings

#include <arm/gic_400.h>

static struct gic_400_regs * const gic_400 = (struct gic_400_regs *)0xC0008000;

// GPIO settings

#ifdef CONFIG_NX_GPIO

#include <nexell/nx_gpio.h>

#define NX_GPIO_BANK_A			0
#define NX_GPIO_BANK_B			1
#define NX_GPIO_BANK_C			2
#define NX_GPIO_BANK_D			3
#define NX_GPIO_BANK_E			4

static struct nx_gpio_regs * const nx_gpio_bank[] = {
	(struct nx_gpio_regs *)0xC001A000,
	(struct nx_gpio_regs *)0xC001B000,
	(struct nx_gpio_regs *)0xC001C000,
	(struct nx_gpio_regs *)0xC001D000,
	(struct nx_gpio_regs *)0xC001E000
};

#define NX_GPIO_BANK_NUMBERS		(sizeof(nx_gpio_bank) / sizeof(struct nx_gpio_regs *))

#endif	/* CONFIG_NX_GPIO */

// Serial settings

#ifdef CONFIG_NX_SERIAL

#include <nexell/nx_serial.h>

struct nx_serial_extended_regs {
	struct nx_serial_regs const *serial;
	enum nx_clkgen_id clkgen_id;
	enum nx_iprst_id iprst_id;
	struct nx_pinctrl_conf const *pinctrl_conf;
};

static struct nx_serial_regs * const nx_serial_port[] = {
	(struct nx_serial_regs *)0xC00A1000,
//	(struct nx_serial_regs *)0xC00A0000,
//	(struct nx_serial_regs *)0xC00A2000,
//	(struct nx_serial_regs *)0xC00A3000,
//	(struct nx_serial_regs *)0xC006D000,
//	(struct nx_serial_regs *)0xC006F000
};

#define NX_SERIAL_PORT_NUMBERS		(sizeof(nx_serial_port) / sizeof(struct nx_serial_regs *))

static struct nx_pinctrl_conf const nx_pinctrl_uart_0_conf[] = {
	{
		// UART_TXD_0
		(struct nx_gpio_regs *)0xC001D000 /* nx_gpio_bank[NX_GPIO_BANK_D] */,
		18,
		NX_PINCTRL_STATE_FN1
	},
	{
		// UART_RXD_0
		(struct nx_gpio_regs *)0xC001D000 /* nx_gpio_bank[NX_GPIO_BANK_D] */,
		14,
		NX_PINCTRL_STATE_FN1
	},
	{ NULL }
};

static struct nx_pinctrl_conf const nx_pinctrl_uart_1_conf[] = {
	{
		// UART_TXD_1
		(struct nx_gpio_regs *)0xC001D000 /* nx_gpio_bank[NX_GPIO_BANK_D] */,
		19,
		NX_PINCTRL_STATE_FN1
	},
	{
		// UART_RXD_1
		(struct nx_gpio_regs *)0xC001D000 /* nx_gpio_bank[NX_GPIO_BANK_D] */,
		15,
		NX_PINCTRL_STATE_FN1
	},
	{
		// UART_DCD_1
		(struct nx_gpio_regs *)0xC001C000 /* nx_gpio_bank[NX_GPIO_BANK_C] */,
		4,
		NX_PINCTRL_STATE_FN2
	},
	{
		// UART_CTS_1
		(struct nx_gpio_regs *)0xC001C000 /* nx_gpio_bank[NX_GPIO_BANK_C] */,
		5,
		NX_PINCTRL_STATE_FN2
	},
	{
		// UART_RTS_1
		(struct nx_gpio_regs *)0xC001C000 /* nx_gpio_bank[NX_GPIO_BANK_C] */,
		6,
		NX_PINCTRL_STATE_FN2
	},
	{
		// UART_DSR_1
		(struct nx_gpio_regs *)0xC001C000 /* nx_gpio_bank[NX_GPIO_BANK_C] */,
		7,
		NX_PINCTRL_STATE_FN2
	},
	{
		// UART_DTR_1
		(struct nx_gpio_regs *)0xC001C000 /* nx_gpio_bank[NX_GPIO_BANK_C] */,
		8,
		NX_PINCTRL_STATE_FN2
	},
	{
		// UART_RI_1
		(struct nx_gpio_regs *)0xC001C000 /* nx_gpio_bank[NX_GPIO_BANK_C] */,
		28,
		NX_PINCTRL_STATE_FN2
	},
	{ NULL }
};

static struct nx_pinctrl_conf const nx_pinctrl_uart_2_conf[] = {
	{
		// UART_TXD_2
		(struct nx_gpio_regs *)0xC001D000 /* nx_gpio_bank[NX_GPIO_BANK_D] */,
		20,
		NX_PINCTRL_STATE_FN1
	},
	{
		// UART_RXD_2
		(struct nx_gpio_regs *)0xC001D000 /* nx_gpio_bank[NX_GPIO_BANK_D] */,
		16,
		NX_PINCTRL_STATE_FN1
	},
	{ NULL }
};

static struct nx_pinctrl_conf const nx_pinctrl_uart_3_conf[] = {
	{
		// UART_TXD_3
		(struct nx_gpio_regs *)0xC001D000 /* nx_gpio_bank[NX_GPIO_BANK_D] */,
		21,
		NX_PINCTRL_STATE_FN1
	},
	{
		// UART_RXD_3
		(struct nx_gpio_regs *)0xC001D000 /* nx_gpio_bank[NX_GPIO_BANK_D] */,
		17,
		NX_PINCTRL_STATE_FN1
	},
	{ NULL }
};

static struct nx_pinctrl_conf const nx_pinctrl_uart_4_conf[] = {
	{
		// UART_TXD_4
		(struct nx_gpio_regs *)0xC001B000 /* nx_gpio_bank[NX_GPIO_BANK_B] */,
		29,
		NX_PINCTRL_STATE_FN3
	},
	{
		// UART_RXD_4
		(struct nx_gpio_regs *)0xC001B000 /* nx_gpio_bank[NX_GPIO_BANK_B] */,
		28,
		NX_PINCTRL_STATE_FN3
	},
	{ NULL }
};

static struct nx_pinctrl_conf const nx_pinctrl_uart_5_conf[] = {
	{
		// UART_TXD_5
		(struct nx_gpio_regs *)0xC001B000 /* nx_gpio_bank[NX_GPIO_BANK_B] */,
		31,
		NX_PINCTRL_STATE_FN3
	},
	{
		// UART_RXD_5
		(struct nx_gpio_regs *)0xC001B000 /* nx_gpio_bank[NX_GPIO_BANK_B] */,
		30,
		NX_PINCTRL_STATE_FN3
	},
	{ NULL }
};

static const struct nx_serial_extended_regs nx_serial_extended_port[] = {
	{
		(struct nx_serial_regs *)0xC00A1000,
		NX_CLKGEN_ID_UART_0,
		NX_IPRST_ID_UART_0,
		nx_pinctrl_uart_0_conf
	},
//	{
//		(struct nx_serial_regs *)0xC00A0000,
//		NX_CLKGEN_ID_UART_1,
//		NX_IPRST_ID_UART_1,
//		nx_pinctrl_uart_1_conf
//	},
//	{
//		(struct nx_serial_regs *)0xC00A2000,
//		NX_CLKGEN_ID_UART_2,
//		NX_IPRST_ID_UART_2,
//		nx_pinctrl_uart_2_conf
//	},
//	{
//		(struct nx_serial_regs *)0xC00A3000,
//		NX_CLKGEN_ID_UART_3,
//		NX_IPRST_ID_UART_3,
//		nx_pinctrl_uart_3_conf
//	},
//	{
//		(struct nx_serial_regs *)0xC006D000,
//		NX_CLKGEN_ID_UART_4,
//		NX_IPRST_ID_UART_4,
//		nx_pinctrl_uart_4_conf
//	},
//	{
//		(struct nx_serial_regs *)0xC006F000,
//		NX_CLKGEN_ID_UART_5,
//		NX_IPRST_ID_UART_5,
//		nx_pinctrl_uart_5_conf
//	}
};

#endif /* CONFIG_NX_SERIAL */

#ifdef CONFIG_NX_TIMER

#include <nexell/nx_timer.h>

static struct nx_timer_regs * const nx_timer = (struct nx_timer_regs *)0xC0017000;

#endif /* CONFIG_NX_TIMER */

// DDR3 settings
#ifdef CONFIG_NX_DDR3

#ifndef CONFIG_NX_DREX
#define CONFIG_NX_DREX
#endif /* !CONFIG_NX_DREX */

#ifndef CONFIG_NX_TZASC
#define CONFIG_NX_TZASC
#endif /* !CONFIG_NX_TZASC */

#ifndef CONFIG_NX_DDRPHY
#define CONFIG_NX_DDRPHY
#endif /* !CONFIG_NX_DDRPHY */

struct ddr3_conf_table {
	uint32_t \
		size,
		bank,
		col,
		row,
		addr_base,
		rank_inter_en,
		bank_lsb,
		bit_sel_en,
		bit_sel,
		al,
		bl,
		cl,
		wr,
		cwl,
		t_pzq,
		t_refi,
		t_rfc,
		t_rrd,
		t_rp,
		t_rcd,
		t_rc,
		t_ras,
		t_wtr,
		t_wr,
		t_rtp,
		t_faw,
		t_xsr,
		t_xp,
		t_cke,
		t_mrd,
		write_leveling,
		gate_leveling,
		read_leveling,
		write_latency_calibration,
		write_dq_calibration;
};

#endif /* CONFIG_NX_DDR3 */

#ifdef CONFIG_NX_DREX

#include <nexell/nx_drex.h>

static struct nx_drex_regs * const nx_drex = (struct nx_drex_regs *)0xC00E0000;

#endif /* CONFIG_NX_DREX */

#ifdef CONFIG_NX_TZASC

#include <nexell/nx_tzasc.h>

static struct nx_tzasc_regs * const nx_tzasc = (struct nx_tzasc_regs *)0xC00E5000;

#endif /* CONFIG_NX_TZASC */

#ifdef CONFIG_NX_DDRPHY

#include <nexell/nx_ddrphy.h>

static struct nx_ddrphy_regs * const nx_ddrphy = (struct nx_ddrphy_regs *)0xC00E1000;

#endif /* CONFIG_NX_DDRPHY */

// USB OTG settings
#ifdef CONFIG_NX_USB_OTG

#include <nexell/nx_usb_otg.h>

static struct nx_usb_otg_regs * const nx_usb_otg = (struct nx_usb_otg_regs *)0xC0040000;

#endif /* CONFIG_NX_USB_OTG */

#ifdef CONFIG_NX_ALIVE

#include <nexell/nx_alive.h>

static struct nx_alive_regs * const nx_alive = (struct nx_alive_regs *)0xC0010800;

#endif /* CONFIG_NX_ALIVE */

#ifdef CONFIG_NX_SDMMC

#include <nexell/nx_sdmmc.h>

struct nx_sdmmc_extended_regs {
	struct nx_sdmmc_regs const *sdmmc;
	enum nx_clkgen_id clkgen_id;
	enum nx_iprst_id iprst_id;
	struct nx_pinctrl_conf const *pinctrl_conf;
};

static struct nx_sdmmc_regs * const nx_sdmmc_port[] = {
	(struct nx_sdmmc_regs *)0xC0062000,
//	(struct nx_sdmmc_regs *)0xC0068000,
//	(struct nx_sdmmc_regs *)0xC0069000,
};

#define NX_SDMMC_PORT_NUMBERS		(sizeof(nx_sdmmc_port) / sizeof(struct nx_sdmmc_regs *))

static struct nx_pinctrl_conf const nx_pinctrl_sdmmc_0_conf[] = {
	{
		// SDMMC_DAT0_0
		(struct nx_gpio_regs *)0xC001B000 /* nx_gpio_bank[NX_GPIO_BANK_B] */,
		1,
		NX_PINCTRL_STATE_FN1
	},
	{
		// SDMMC_DAT1_0
		(struct nx_gpio_regs *)0xC001B000 /* nx_gpio_bank[NX_GPIO_BANK_B] */,
		3,
		NX_PINCTRL_STATE_FN1
	},
	{
		// SDMMC_DAT2_0
		(struct nx_gpio_regs *)0xC001B000 /* nx_gpio_bank[NX_GPIO_BANK_B] */,
		5,
		NX_PINCTRL_STATE_FN1
	},
	{
		// SDMMC_DAT3_0
		(struct nx_gpio_regs *)0xC001B000 /* nx_gpio_bank[NX_GPIO_BANK_B] */,
		7,
		NX_PINCTRL_STATE_FN1
	},
	{
		// SDMMC_CLK_0
		(struct nx_gpio_regs *)0xC001A000 /* nx_gpio_bank[NX_GPIO_BANK_A] */,
		29,
		NX_PINCTRL_STATE_FN1
	},
	{
		// SDMMC_CMD_0
		(struct nx_gpio_regs *)0xC001A000 /* nx_gpio_bank[NX_GPIO_BANK_A] */,
		31,
		NX_PINCTRL_STATE_FN1
	},
// Not used pins
//	{
//		// SDMMC_WP_0
//		(struct nx_gpio_regs *)0xC001C000 /* nx_gpio_bank[NX_GPIO_BANK_C] */,
//		5,
//		NX_PINCTRL_STATE_FN3
//	},
//	{
//		// SDMMC_CD_0
//		(struct nx_gpio_regs *)0xC001C000 /* nx_gpio_bank[NX_GPIO_BANK_C] */,
//		6,
//		NX_PINCTRL_STATE_FN3
//	},
//	{
//		// SDMMC_RST_0
//		(struct nx_gpio_regs *)0xC001C000 /* nx_gpio_bank[NX_GPIO_BANK_C] */,
//		3,
//		NX_PINCTRL_STATE_FN3
//	},
//	{
//		// SDMMC_INT_0
//		(struct nx_gpio_regs *)0xC001C000 /* nx_gpio_bank[NX_GPIO_BANK_C] */,
//		4,
//		NX_PINCTRL_STATE_FN3
//	},
	{ NULL }
};

static struct nx_pinctrl_conf const nx_pinctrl_sdmmc_1_conf[] = {
	{
		// SDMMC_DAT0_1
		(struct nx_gpio_regs *)0xC001D000 /* nx_gpio_bank[NX_GPIO_BANK_D] */,
		24,
		NX_PINCTRL_STATE_FN1
	},
	{
		// SDMMC_DAT1_1
		(struct nx_gpio_regs *)0xC001D000 /* nx_gpio_bank[NX_GPIO_BANK_D] */,
		25,
		NX_PINCTRL_STATE_FN1
	},
	{
		// SDMMC_DAT2_1
		(struct nx_gpio_regs *)0xC001D000 /* nx_gpio_bank[NX_GPIO_BANK_D] */,
		26,
		NX_PINCTRL_STATE_FN1
	},
	{
		// SDMMC_DAT3_1
		(struct nx_gpio_regs *)0xC001D000 /* nx_gpio_bank[NX_GPIO_BANK_D] */,
		27,
		NX_PINCTRL_STATE_FN1
	},
	{
		// SDMMC_CLK_1
		(struct nx_gpio_regs *)0xC001D000 /* nx_gpio_bank[NX_GPIO_BANK_D] */,
		22,
		NX_PINCTRL_STATE_FN1
	},
	{
		// SDMMC_CMD_1
		(struct nx_gpio_regs *)0xC001D000 /* nx_gpio_bank[NX_GPIO_BANK_D] */,
		23,
		NX_PINCTRL_STATE_FN1
	},
	{
		// SDMMC_WP_1
		(struct nx_gpio_regs *)0xC001D000 /* nx_gpio_bank[NX_GPIO_BANK_D] */,
		20,
		NX_PINCTRL_STATE_FN1
	},
	{
		// SDMMC_CD_1
		(struct nx_gpio_regs *)0xC001D000 /* nx_gpio_bank[NX_GPIO_BANK_D] */,
		21,
		NX_PINCTRL_STATE_FN1
	},
	{
		// SDMMC_RST_1
		(struct nx_gpio_regs *)0xC001C000 /* nx_gpio_bank[NX_GPIO_BANK_C] */,
		7,
		NX_PINCTRL_STATE_FN3
	},
	{
		// SDMMC_INT_1
		(struct nx_gpio_regs *)0xC001C000 /* nx_gpio_bank[NX_GPIO_BANK_C] */,
		8,
		NX_PINCTRL_STATE_FN3
	},
	{ NULL }
};

static struct nx_pinctrl_conf const nx_pinctrl_sdmmc_2_conf[] = {
	{
		// SDMMC_DAT0_2
		(struct nx_gpio_regs *)0xC001C000 /* nx_gpio_bank[NX_GPIO_BANK_C] */,
		20,
		NX_PINCTRL_STATE_FN2
	},
	{
		// SDMMC_DAT1_2
		(struct nx_gpio_regs *)0xC001C000 /* nx_gpio_bank[NX_GPIO_BANK_C] */,
		21,
		NX_PINCTRL_STATE_FN2
	},
	{
		// SDMMC_DAT2_2
		(struct nx_gpio_regs *)0xC001C000 /* nx_gpio_bank[NX_GPIO_BANK_C] */,
		22,
		NX_PINCTRL_STATE_FN2
	},
	{
		// SDMMC_DAT3_2
		(struct nx_gpio_regs *)0xC001C000 /* nx_gpio_bank[NX_GPIO_BANK_C] */,
		23,
		NX_PINCTRL_STATE_FN2
	},
	{
		// SDMMC_DAT4_2
		(struct nx_gpio_regs *)0xC001E000 /* nx_gpio_bank[NX_GPIO_BANK_E] */,
		21,
		NX_PINCTRL_STATE_FN2
	},
	{
		// SDMMC_DAT5_2
		(struct nx_gpio_regs *)0xC001E000 /* nx_gpio_bank[NX_GPIO_BANK_E] */,
		22,
		NX_PINCTRL_STATE_FN2
	},
	{
		// SDMMC_DAT6_2
		(struct nx_gpio_regs *)0xC001E000 /* nx_gpio_bank[NX_GPIO_BANK_E] */,
		23,
		NX_PINCTRL_STATE_FN2
	},
	{
		// SDMMC_DAT7_2
		(struct nx_gpio_regs *)0xC001E000 /* nx_gpio_bank[NX_GPIO_BANK_E] */,
		24,
		NX_PINCTRL_STATE_FN2
	},
	{
		// SDMMC_CLK_2
		(struct nx_gpio_regs *)0xC001C000 /* nx_gpio_bank[NX_GPIO_BANK_C] */,
		18,
		NX_PINCTRL_STATE_FN2
	},
	{
		// SDMMC_CMD_2
		(struct nx_gpio_regs *)0xC001C000 /* nx_gpio_bank[NX_GPIO_BANK_C] */,
		19,
		NX_PINCTRL_STATE_FN2
	},
	{
		// SDMMC_WP_2
		(struct nx_gpio_regs *)0xC001D000 /* nx_gpio_bank[NX_GPIO_BANK_D] */,
		18,
		NX_PINCTRL_STATE_FN3
	},
	{
		// SDMMC_CD_2
		(struct nx_gpio_regs *)0xC001D000 /* nx_gpio_bank[NX_GPIO_BANK_D] */,
		19,
		NX_PINCTRL_STATE_FN3
	},
	{
		// SDMMC_RST_2
		(struct nx_gpio_regs *)0xC001C000 /* nx_gpio_bank[NX_GPIO_BANK_C] */,
		12,
		NX_PINCTRL_STATE_FN3
	},
	{
		// SDMMC_INT_2
		(struct nx_gpio_regs *)0xC001C000 /* nx_gpio_bank[NX_GPIO_BANK_C] */,
		13,
		NX_PINCTRL_STATE_FN3
	},
	{ NULL }
};

static const struct nx_sdmmc_extended_regs nx_sdmmc_extended_port[] = {
	{
		(struct nx_sdmmc_regs *)0xC0062000,
		NX_CLKGEN_ID_SDMMC_0,
		NX_IPRST_ID_SDMMC_0,
		nx_pinctrl_sdmmc_0_conf
	},
//	{
//		(struct nx_sdmmc_regs *)0xC0068000,
//		NX_CLKGEN_ID_SDMMC_1,
//		NX_IPRST_ID_SDMMC_1,
//		nx_pinctrl_sdmmc_1_conf
//	},
//	{
//		(struct nx_sdmmc_regs *)0xC0069000,
//		NX_CLKGEN_ID_SDMMC_2,
//		NX_IPRST_ID_SDMMC_2,
//		nx_pinctrl_SDMMC_2_conf
//	}
};

#endif /* CONFIG_NX_SDMMC */

#endif /* !__COMPILING_ASM */

#endif	/* __S5P6818_H__ */
