/*
 * Copyright (C) 2017
 * Author: metro94 <flattiles@gmail.com>
 *
 * Version: v1.0
 * --- Update time: 02/07/2017
 * --- Description: First build; header of driver for Nexell SoC Clock Generator
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

#ifndef __NX_CLKGEN_H__
#define __NX_CLKGEN_H__

#include <common.h>

enum nx_clkgen_mode {
	NX_CLKGEN_MODE_BCLK = 1,
	NX_CLKGEN_MODE_PCLK = 2,
	NX_CLKGEN_MODE_CLKGEN = 4
};

struct nx_clkgen_regs {
	volatile uint32_t \
		enb,		// 0x0
		gen[4];		// 0x4 ~ x
};

struct nx_clkgen_info {
	struct nx_clkgen_regs * const clkgen;
	int level;
	enum nx_clkgen_mode mode;
};

int  nx_get_clkgen_bclk_enb(struct nx_clkgen_regs * const);
int  nx_get_clkgen_pclk_enb(struct nx_clkgen_regs * const);
int  nx_get_clkgen_div_enb(struct nx_clkgen_regs * const);
int  nx_get_clkgen_div(struct nx_clkgen_regs * const, int);
int  nx_get_clkgen_src(struct nx_clkgen_regs * const, int);
void nx_set_clkgen_bclk_enb(struct nx_clkgen_regs * const, int);
void nx_set_clkgen_pclk_enb(struct nx_clkgen_regs * const, int);
void nx_set_clkgen_div_enb(struct nx_clkgen_regs * const, int);
void nx_set_clkgen_div(struct nx_clkgen_regs * const, int, int);
void nx_set_clkgen_src(struct nx_clkgen_regs * const, int, int);

#endif

