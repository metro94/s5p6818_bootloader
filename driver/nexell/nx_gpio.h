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

#ifndef __NX_GPIO_H__
#define __NX_GPIO_H__

#include <common.h>

struct nx_gpio_regs {
	volatile uint32_t \
		out,				// 0x0
		out_enb,			// 0x4
		det_mode[2],			// 0x8 ~ 0xC
		int_enb,			// 0x10
		det,				// 0x14
		pad,				// 0x18
		__rsvd0,			// 0x1C
		alt_fn[2],			// 0x20 ~ 0x24
		det_mode_ex,			// 0x28
		__rsvd1[(0x3C - 0x2C) / 4],	// 0x2C ~ 0x38
		det_enb,			// 0x3C
		slew,				// 0x40
		slew_disable_default,		// 0x44
		drv1,				// 0x48
		drv1_disable_default,		// 0x4C
		drv0,				// 0x50
		drv0_disable_default,		// 0x54
		pull_sel,			// 0x58
		pull_sel_disable_default,	// 0x5C
		pull_enb,			// 0x60
		pull_enb_disable_default;	// 0x64
};

enum nx_gpio_state {
	NX_GPIO_STATE_IN = 0,
	NX_GPIO_STATE_OUT
};

enum nx_pinctrl_state {
	NX_PINCTRL_STATE_FN0 = 0,
	NX_PINCTRL_STATE_FN1,
	NX_PINCTRL_STATE_FN2,
	NX_PINCTRL_STATE_FN3
};

struct nx_gpio_conf {
	struct nx_gpio_regs * const gpio_bank;
	int gpio_number;
	enum nx_gpio_state gpio_state;
};

struct nx_pinctrl_conf {
	struct nx_gpio_regs * const gpio_bank;
	int gpio_number;
	enum nx_pinctrl_state pinctrl_state;
};

void nx_set_gpio(struct nx_gpio_conf const *);
void nx_set_gpio_simple(struct nx_gpio_regs * const, int, enum nx_gpio_state);

void nx_set_pinctrl(struct nx_pinctrl_conf const *);
void nx_set_pinctrl_simple(struct nx_gpio_regs * const, int, enum nx_pinctrl_state);

int  nx_read_gpio(struct nx_gpio_regs * const, int);
void nx_write_gpio(struct nx_gpio_regs * const, int, int);
void nx_toggle_gpio(struct nx_gpio_regs * const, int);

#endif
