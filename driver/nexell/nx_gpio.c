/*
 * Copyright (C) 2017
 * Author: metro94 <flattiles@gmail.com>
 *
 * Version: v1.0
 * --- Update time: 02/07/2017
 * --- Description: First build; code of driver for Nexell SoC GPIO
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

#include <common.h>

#include <nx_gpio.h>

inline void nx_set_gpio(struct nx_gpio_conf const *cur_conf)
{
	while (cur_conf->gpio_bank) {
		nx_set_gpio_simple(
			cur_conf->gpio_bank,
			cur_conf->gpio_number,
			cur_conf->gpio_state
		);
		++cur_conf;
	}
}

inline void nx_set_gpio_simple(struct nx_gpio_regs * const gpio_bank, int gpio_number, enum nx_gpio_state gpio_state)
{
	if (gpio_state == NX_GPIO_STATE_IN)
		gpio_bank->out_enb &= ~(1 << gpio_number);
	else
		gpio_bank->out_enb |=  (1 << gpio_number);
}

inline void nx_set_pinctrl(struct nx_pinctrl_conf const *cur_conf)
{
	while (cur_conf->gpio_bank) {
		nx_set_pinctrl_simple(
			cur_conf->gpio_bank,
			cur_conf->gpio_number,
			cur_conf->pinctrl_state
		);
		++cur_conf;
	}
}

inline void nx_set_pinctrl_simple(struct nx_gpio_regs * const gpio_bank, int gpio_number, enum nx_pinctrl_state pinctrl_state)
{
	if (gpio_number < 16)
		gpio_bank->alt_fn[0] = (gpio_bank->alt_fn[0]	\
					& ~(3 << (gpio_number << 1)))	\
					| (pinctrl_state << (gpio_number << 1));
	else
		gpio_bank->alt_fn[1] = (gpio_bank->alt_fn[1]		\
					& ~(3 << ((gpio_number << 1) - 32)))	\
					| (pinctrl_state << ((gpio_number << 1) - 32));
}

inline int  nx_read_gpio(struct nx_gpio_regs * const gpio_bank, int gpio_number)
{
	return (gpio_bank->pad & (1 << gpio_number)) ? 1 : 0;
}

inline void nx_write_gpio(struct nx_gpio_regs * const gpio_bank, int gpio_number, int gpio_value)
{
	if (gpio_value == 0)
		gpio_bank->out &= ~(1 << gpio_number);
	else
		gpio_bank->out |=  (1 << gpio_number);
}

inline void nx_toggle_gpio(struct nx_gpio_regs * const gpio_bank, int gpio_number)
{
	gpio_bank->out ^= (1 << gpio_number);
}
