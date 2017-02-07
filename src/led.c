/*
 * Copyright (C) 2017
 * Author: metro94 <flattiles@gmail.com>
 *
 * Version: v1.0
 * --- Update time: 02/07/2017
 * --- Description: First build; code for LED on board
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

#include <led.h>

void init_led(void)
{
	nx_set_pinctrl_simple(
		PI_LED_BLUE_GPIO_BANK,
		PI_LED_BLUE_GPIO_NUMBER,
		PI_LED_BLUE_GPIO_FN
	);
	
	nx_set_gpio_simple(
		PI_LED_BLUE_GPIO_BANK,
		PI_LED_BLUE_GPIO_NUMBER,
		NX_GPIO_STATE_OUT
	);
	
	// Sets initial state (led off)
	nx_write_gpio(
		PI_LED_BLUE_GPIO_BANK,
		PI_LED_BLUE_GPIO_NUMBER,
		1
	);
}

void set_led_on(void)
{
	nx_write_gpio(
		PI_LED_BLUE_GPIO_BANK,
		PI_LED_BLUE_GPIO_NUMBER,
		0
	);
}

void set_led_off(void)
{
	nx_write_gpio(
		PI_LED_BLUE_GPIO_BANK,
		PI_LED_BLUE_GPIO_NUMBER,
		1
	);
}

void test_led(void)
{
	// Avoids optimized
	volatile int i, j, k;
	
	k = 0;
	for (i = 0; i < 6; ++i) {
		for (j = 0; j < 500000; ++j)
			k ^= j;
		nx_toggle_gpio(
			PI_LED_BLUE_GPIO_BANK,
			PI_LED_BLUE_GPIO_NUMBER
		);
	}
}
