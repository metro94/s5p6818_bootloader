/*
 * Copyright (C) 2017
 * Author: metro94 <flattiles@gmail.com>
 *
 * Version: v1.0
 * --- Update time: 02/07/2017
 * --- Description: First build; code for I2C bus operation
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

#include <i2c.h>

void init_i2c(void)
{
	nx_set_pinctrl_simple(PI_PMIC_I2C_SDA_GPIO_BANK, PI_PMIC_I2C_SDA_GPIO_NUMBER, PI_PMIC_I2C_SDA_GPIO_FN);
	nx_set_pinctrl_simple(PI_PMIC_I2C_SCL_GPIO_BANK, PI_PMIC_I2C_SCL_GPIO_NUMBER, PI_PMIC_I2C_SCL_GPIO_FN);
	
	nx_write_gpio(PI_PMIC_I2C_SDA_GPIO_BANK, PI_PMIC_I2C_SDA_GPIO_NUMBER, 1);
	nx_write_gpio(PI_PMIC_I2C_SCL_GPIO_BANK, PI_PMIC_I2C_SCL_GPIO_NUMBER, 1);
	
	nx_set_gpio_simple(PI_PMIC_I2C_SDA_GPIO_BANK, PI_PMIC_I2C_SDA_GPIO_NUMBER, NX_GPIO_STATE_OUT);
	nx_set_gpio_simple(PI_PMIC_I2C_SCL_GPIO_BANK, PI_PMIC_I2C_SCL_GPIO_NUMBER, NX_GPIO_STATE_OUT);
	
	debug(DEBUG_LEVEL_INFO, "I2C Bus is ready\n");
}

void release_i2c(void)
{
	nx_set_gpio_simple(PI_PMIC_I2C_SDA_GPIO_BANK, PI_PMIC_I2C_SDA_GPIO_NUMBER, NX_GPIO_STATE_IN);
	nx_set_gpio_simple(PI_PMIC_I2C_SCL_GPIO_BANK, PI_PMIC_I2C_SCL_GPIO_NUMBER, NX_GPIO_STATE_IN);
}

void generate_i2c_start(void)
{
	nx_write_gpio(PI_PMIC_I2C_SDA_GPIO_BANK, PI_PMIC_I2C_SDA_GPIO_NUMBER, 0);
	delay_us(5);	// >= 4.7 us
	nx_write_gpio(PI_PMIC_I2C_SCL_GPIO_BANK, PI_PMIC_I2C_SCL_GPIO_NUMBER, 0);
	delay_us(4);	// >= 4 us
}

void generate_i2c_stop(void)
{
	nx_set_gpio_simple(PI_PMIC_I2C_SDA_GPIO_BANK, PI_PMIC_I2C_SDA_GPIO_NUMBER, NX_GPIO_STATE_OUT);
	nx_write_gpio(PI_PMIC_I2C_SDA_GPIO_BANK, PI_PMIC_I2C_SDA_GPIO_NUMBER, 0);
	
	nx_write_gpio(PI_PMIC_I2C_SCL_GPIO_BANK, PI_PMIC_I2C_SCL_GPIO_NUMBER, 1);
	delay_us(4);	// >= 4 us
	nx_write_gpio(PI_PMIC_I2C_SDA_GPIO_BANK, PI_PMIC_I2C_SDA_GPIO_NUMBER, 1);
	delay_us(5);	// >= 4.7 us
}

int send_data_via_i2c(uint8_t data)
{
	int clk;
	int nack;
	
	nx_set_gpio_simple(PI_PMIC_I2C_SDA_GPIO_BANK, PI_PMIC_I2C_SDA_GPIO_NUMBER, NX_GPIO_STATE_OUT);
	
	for (clk = 0; clk < 8; ++clk) {
		nx_write_gpio(PI_PMIC_I2C_SDA_GPIO_BANK, PI_PMIC_I2C_SDA_GPIO_NUMBER, data & 0x80);
		delay_us(5);
		nx_write_gpio(PI_PMIC_I2C_SCL_GPIO_BANK, PI_PMIC_I2C_SCL_GPIO_NUMBER, 1);
		delay_us(5);
		nx_write_gpio(PI_PMIC_I2C_SCL_GPIO_BANK, PI_PMIC_I2C_SCL_GPIO_NUMBER, 0);
		data <<= 1;
	}
	
	nx_set_gpio_simple(PI_PMIC_I2C_SDA_GPIO_BANK, PI_PMIC_I2C_SDA_GPIO_NUMBER, NX_GPIO_STATE_IN);
	delay_us(5);
	nx_write_gpio(PI_PMIC_I2C_SCL_GPIO_BANK, PI_PMIC_I2C_SCL_GPIO_NUMBER, 1);
	delay_us(5);
	nack = nx_read_gpio(PI_PMIC_I2C_SDA_GPIO_BANK, PI_PMIC_I2C_SDA_GPIO_NUMBER);
	nx_write_gpio(PI_PMIC_I2C_SCL_GPIO_BANK, PI_PMIC_I2C_SCL_GPIO_NUMBER, 0);
	
	return nack;
}

uint8_t recv_data_via_i2c(int nack)
{
	int clk;
	uint8_t data;
	
	nx_set_gpio_simple(PI_PMIC_I2C_SDA_GPIO_BANK, PI_PMIC_I2C_SDA_GPIO_NUMBER, NX_GPIO_STATE_IN);
	
	data = 0;
	for (clk = 0; clk < 8; ++clk) {
		delay_us(5);
		nx_write_gpio(PI_PMIC_I2C_SCL_GPIO_BANK, PI_PMIC_I2C_SCL_GPIO_NUMBER, 1);
		delay_us(5);
		data = (data << 1) | nx_read_gpio(PI_PMIC_I2C_SDA_GPIO_BANK, PI_PMIC_I2C_SDA_GPIO_NUMBER);
		nx_write_gpio(PI_PMIC_I2C_SCL_GPIO_BANK, PI_PMIC_I2C_SCL_GPIO_NUMBER, 0);
	}
	
	nx_set_gpio_simple(PI_PMIC_I2C_SDA_GPIO_BANK, PI_PMIC_I2C_SDA_GPIO_NUMBER, NX_GPIO_STATE_OUT);
	nx_write_gpio(PI_PMIC_I2C_SDA_GPIO_BANK, PI_PMIC_I2C_SDA_GPIO_NUMBER, nack ? 1 : 0);
	delay_us(5);
	nx_write_gpio(PI_PMIC_I2C_SCL_GPIO_BANK, PI_PMIC_I2C_SCL_GPIO_NUMBER, 1);
	delay_us(5);
	nx_write_gpio(PI_PMIC_I2C_SCL_GPIO_BANK, PI_PMIC_I2C_SCL_GPIO_NUMBER, 0);
	
	return data;
}

int send_i2c_addr(uint8_t addr, int rnw)	// Read = 1, Write = 0
{
	return send_data_via_i2c((addr << 1) | (rnw ? 1 : 0));
}

void dump_i2c_bus(void)
{
	uint32_t addr;
	
	printf("I2C Bus State Table\n");
	printf("   0 1 2 3 4 5 6 7 8 9 A B C D E F\n");
	
	for (addr = 0; addr < 0x80; ++addr) {
		if ((addr & 0xF) == 0x0)
			printf("%02x", addr);
		generate_i2c_start();
		printf(" %c", send_i2c_addr(addr, 1) ? ' ' : '*');
		generate_i2c_stop();
		if ((addr & 0xF) == 0xF)
			printf("\n");
	}
}
