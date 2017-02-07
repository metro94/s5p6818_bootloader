/*
 * Copyright (C) 2017
 * Author: metro94 <flattiles@gmail.com>
 *
 * Version: v1.0
 * --- Update time: 02/07/2017
 * --- Description: First build; header for FriendlyARM NanoPi M3
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

#ifndef __NANOPI_M3_H__
#define __NANOPI_M3_H__

// Sets modules enable
#define CONFIG_NX_GPIO
#define CONFIG_NX_SERIAL
#define CONFIG_NX_TIMER
#define CONFIG_NX_DDR3
#define CONFIG_NX_USB_OTG
#define CONFIG_NX_ALIVE
#define CONFIG_NX_SDMMC

#include <s5p6818.h>

// Sets board resources
#define PI_OSC_FREQ				24000000

#define PI_PLL_0_FREQ				1000000000
#define PI_PLL_1_FREQ				1600000000
#define PI_PLL_2_FREQ				1600000000
#define PI_PLL_3_FREQ				1600000000

#define PI_CPU_CLUSTER_0_FCLK_FREQ		1000000000
#define PI_CPU_CLUSTER_0_HCLK_FREQ		250000000
#define PI_CPU_CLUSTER_1_FCLK_FREQ		1000000000
#define PI_CPU_CLUSTER_1_HCLK_FREQ		250000000
#define PI_BCLK_FREQ				320000000
#define PI_PCLK_FREQ				160000000
#define PI_MDCLK_FREQ				800000000
#define PI_MCLK_FREQ				800000000
#define PI_MBCLK_FREQ				400000000
#define PI_MPCLK_FREQ				200000000
#define PI_GR3D_BCLK_FREQ			320000000
#define PI_GR3D_PCLK_FREQ			160000000
#define PI_MPEG_BCLK_FREQ			266666667
#define PI_MPEG_PCLK_FREQ			133333333
#define PI_DISP_BCLK_FREQ			266666667
#define PI_DISP_PCLK_FREQ			133333333
#define PI_HDMI_PCLK_FREQ			100000000
#define PI_FAST_BCLK_FREQ			400000000

#define PI_SYSTEM_COUNTER_TIMER_CHANNEL		4
#define PI_SYSTEM_COUNTER_FREQ			1000000

#define PI_LED_BLUE_GPIO_BANK			nx_gpio_bank[NX_GPIO_BANK_B]
#define PI_LED_BLUE_GPIO_NUMBER			12
#define PI_LED_BLUE_GPIO_FN			NX_PINCTRL_STATE_FN2

#define PI_PMIC_I2C_SDA_GPIO_BANK		nx_gpio_bank[NX_GPIO_BANK_E]
#define PI_PMIC_I2C_SDA_GPIO_NUMBER		31
#define PI_PMIC_I2C_SDA_GPIO_FN			1
#define PI_PMIC_I2C_SCL_GPIO_BANK		nx_gpio_bank[NX_GPIO_BANK_E]
#define PI_PMIC_I2C_SCL_GPIO_NUMBER		30
#define PI_PMIC_I2C_SCL_GPIO_FN			1

#define PI_PMIC_DLDO1_VOLTAGE			0.7
#define PI_PMIC_DLDO2_VOLTAGE			0.7
#define PI_PMIC_DLDO3_VOLTAGE			0.7
#define PI_PMIC_DLDO4_VOLTAGE			0.7
#define PI_PMIC_ELDO1_VOLTAGE			1.8
#define PI_PMIC_ELDO2_VOLTAGE			0.7
#define PI_PMIC_ELDO3_VOLTAGE			0.7
#define PI_PMIC_DC5LDO_VOLTAGE			0.7
#define PI_PMIC_DCDC1_VOLTAGE			3.3
#define PI_PMIC_DCDC2_VOLTAGE			0.6
#define PI_PMIC_DCDC3_VOLTAGE			1.0
#define PI_PMIC_DCDC4_VOLTAGE			1.5
#define PI_PMIC_DCDC5_VOLTAGE			1.5
#define PI_PMIC_ALDO1_VOLTAGE			3.3
#define PI_PMIC_ALDO2_VOLTAGE			1.8
#define PI_PMIC_ALDO3_VOLTAGE			1.0

//#define PI_MEM_TEST
#define PI_MEM_TEST_START_ADDR			0x40000000ULL
#define PI_MEM_TEST_END_ADDR			0x80000000ULL

#define PI_DEBUG_UART_PORT			0
#define PI_DEBUG_UART_BAUDRATE			115200
#define PI_DEBUG_UART_CLKSRC			2
#define PI_DEBUG_UART_CLKGEN_FREQ		100000000

#define PI_SDMMC_PORT				0
#define PI_SDMMC_CLKSRC				2
#define PI_SDMMC_CLKGEN_FREQ			200000000
#define PI_SDMMC_HIGH_SPEED_FREQ		25000000
#define PI_SDMMC_LOW_SPEED_FREQ			4000000

#define PI_SLAVE_CPU_RELEASE_ADDR		0xFFFF0000

#define PI_BOOTLOADER_CONF_FILENAME		"boot.cfg"
#define PI_BOOT_VOLUME_LABEL			"boot"
#define PI_BOOTLOADER_DEFAULT_FILENAME		"boot.bin"
#define PI_BOOTLOADER_DEFAULT_LOAD_ADDR		0x40000000
#define PI_BOOTLOADER_DEFAULT_LAUNCH_ADDR	PI_BOOTLOADER_DEFAULT_LOAD_ADDR

static struct ddr3_conf_table const ddr3_conf = {
	.size = 1 * 1024 * 1024 * 1024,
	.bank = 8,
	.col = 10,
	.row = 15,
	.addr_base = 0x40000000,
	.rank_inter_en = 0,
	.bank_lsb = 2,
	.bit_sel_en = 0,
	.bit_sel = 2,
	.al = 0,
	.bl = 8,
	.cl = 11,
	.wr = 12,
	.cwl = 8,
	.t_pzq = 16384,
	.t_refi = 1560,
	.t_rfc = 104,
	.t_rrd = 3,
	.t_rp = 6,
	.t_rcd = 6,
	.t_rc = 20,
	.t_ras = 15,
	.t_wtr = 3,
	.t_wr = 6,
	.t_rtp = 3,
	.t_faw = 16,
	.t_xsr = 256,
	.t_xp = 10,
	.t_cke = 2,
	.t_mrd = 6,
	.write_leveling = 1,
	.gate_leveling = 1,
	.read_leveling = 1,
	.write_latency_calibration = 1,
	.write_dq_calibration = 1
};

#endif /* __NANOPI_M3_H__ */
