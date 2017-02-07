/*
 * Copyright (C) 2017
 * Author: metro94 <flattiles@gmail.com>
 *
 * Version: v1.0
 * --- Update time: 02/07/2017
 * --- Description: First build; code for PMIC on board
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

#include <nanopi_m3.h>

#include <pmic.h>

void init_pmic(void)
{
	debug(DEBUG_LEVEL_INFO, "Initializing PMIC\n");
	// Set Voltage
	set_pmic_register(
		AXP228_REG_VOLTAGE_SET_DLDO1,
		(uint8_t)round((PI_PMIC_DLDO1_VOLTAGE - 0.7) / 0.1)
	);
	set_pmic_register(
		AXP228_REG_VOLTAGE_SET_DLDO2,
		(uint8_t)round((PI_PMIC_DLDO2_VOLTAGE - 0.7) / 0.1)
	);
	set_pmic_register(
		AXP228_REG_VOLTAGE_SET_DLDO3,
		(uint8_t)round((PI_PMIC_DLDO3_VOLTAGE - 0.7) / 0.1)
	);
	set_pmic_register(
		AXP228_REG_VOLTAGE_SET_DLDO4,
		(uint8_t)round((PI_PMIC_DLDO4_VOLTAGE - 0.7) / 0.1)
	);
	set_pmic_register(
		AXP228_REG_VOLTAGE_SET_ELDO1,
		(uint8_t)round((PI_PMIC_ELDO1_VOLTAGE - 0.7) / 0.1)
	);
	set_pmic_register(
		AXP228_REG_VOLTAGE_SET_ELDO2,
		(uint8_t)round((PI_PMIC_ELDO2_VOLTAGE - 0.7) / 0.1)
	);
	set_pmic_register(
		AXP228_REG_VOLTAGE_SET_ELDO3,
		(uint8_t)round((PI_PMIC_ELDO3_VOLTAGE - 0.7) / 0.1)
	);
	set_pmic_register(
		AXP228_REG_VOLTAGE_SET_DC5LDO,
		(uint8_t)round((PI_PMIC_DC5LDO_VOLTAGE - 0.7) / 0.1)
	);
	set_pmic_register(
		AXP228_REG_VOLTAGE_SET_DCDC1,
		(uint8_t)round((PI_PMIC_DCDC1_VOLTAGE - 1.6) / 0.1)
	);
	set_pmic_register(
		AXP228_REG_VOLTAGE_SET_DCDC2,
		(uint8_t)round((PI_PMIC_DCDC2_VOLTAGE - 0.6) / 0.02)
	);
	set_pmic_register(
		AXP228_REG_VOLTAGE_SET_DCDC3,
		(uint8_t)round((PI_PMIC_DCDC3_VOLTAGE - 0.6) / 0.02)
	);
	set_pmic_register(
		AXP228_REG_VOLTAGE_SET_DCDC4,
		(uint8_t)round((PI_PMIC_DCDC4_VOLTAGE - 0.6) / 0.02)
	);
	set_pmic_register(
		AXP228_REG_VOLTAGE_SET_DCDC5,
		(uint8_t)round((PI_PMIC_DCDC5_VOLTAGE - 0.6) / 0.02)
	);
	set_pmic_register(
		AXP228_REG_VOLTAGE_SET_ALDO1,
		(uint8_t)round((PI_PMIC_ALDO1_VOLTAGE - 0.7) / 0.1)
	);
	set_pmic_register(
		AXP228_REG_VOLTAGE_SET_ALDO2,
		(uint8_t)round((PI_PMIC_ALDO2_VOLTAGE - 0.7) / 0.1)
	);
	set_pmic_register(
		AXP228_REG_VOLTAGE_SET_ALDO3,
		(uint8_t)round((PI_PMIC_ALDO3_VOLTAGE - 0.7) / 0.1)
	);
	
	// Chooses output channels
	set_pmic_register(
		AXP228_REG_POWER_SET_0,
		(1 << 7) |	// ALDO2
		(1 << 6) |	// ALDO1
		(1 << 5) |	// DCDC5
		(1 << 4) |	// DCDC4
		(1 << 3) |	// DCDC3
		(0 << 2) |	// DCDC2
		(1 << 1) |	// DCDC1
		(0 << 0)	// DC5LDO
	);
	set_pmic_register(
		AXP228_REG_POWER_SET_1,
		(1 << 7) |	// DC1SW
		(0 << 6) |	// DLDO4
		(0 << 5) |	// DLDO3
		(0 << 4) |	// DLDO2
		(1 << 3) |	// DLDO1
		(0 << 2) |	// ELDO3
		(0 << 1) |	// ELDO2
		(1 << 0)	// ELDO1
	);
	set_pmic_register(
		AXP228_REG_POWER_SET_2,
		(get_pmic_register(AXP228_REG_POWER_SET_2) & ~(1 << 7)) |
		(1 << 7)	// ALDO3
	);
	
	// Enables internal temperature ADC
	set_pmic_register(AXP228_REG_ADC_ENABLE, (1 << 5));
}

uint8_t get_pmic_register(uint8_t addr)
{
	uint8_t value;
	
	generate_i2c_start();
	send_i2c_addr(AXP228_I2C_ADDR, 0);
	send_data_via_i2c(addr);
	generate_i2c_stop();
	generate_i2c_start();
	send_i2c_addr(AXP228_I2C_ADDR, 1);
	value = recv_data_via_i2c(1);
	generate_i2c_stop();
	
	return value;
}

void set_pmic_register(uint8_t addr, uint8_t value)
{
//	printf("addr = %02x, value = %02x\n", addr, value);
	generate_i2c_start();
	send_i2c_addr(AXP228_I2C_ADDR, 0);
	send_data_via_i2c(addr);
	send_data_via_i2c(value);
	generate_i2c_stop();
}

void dump_pmic(void)
{
	uint32_t addr;
	
	printf("PMIC Register Table\n");
	printf("    0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\n");
	
	for (addr = 0; addr < 0x100; ++addr) {
		if ((addr & 0xF) == 0x0)
			printf("%02x", addr);
		printf(" %02x", get_pmic_register(addr));
		if ((addr & 0xF) == 0xF)
			printf("\n");
	}
}
