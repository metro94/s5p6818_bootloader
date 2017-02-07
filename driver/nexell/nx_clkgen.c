/*
 * Copyright (C) 2017
 * Author: metro94 <flattiles@gmail.com>
 *
 * Version: v1.0
 * --- Update time: 02/07/2017
 * --- Description: First build; code of driver for Nexell SoC Clock Generator
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

#include <nx_clkgen.h>

inline int  nx_get_clkgen_bclk_enb(struct nx_clkgen_regs * const clkgen)
{
	return (clkgen->enb & (3 << 0)) ? 1 : 0;
}

inline int  nx_get_clkgen_pclk_enb(struct nx_clkgen_regs * const clkgen)
{
	return (clkgen->enb & (1 << 3)) ? 1 : 0;
}

inline int  nx_get_clkgen_div_enb(struct nx_clkgen_regs * const clkgen)
{
	return (clkgen->enb & (1 << 2)) ? 1 : 0;
}

inline int  nx_get_clkgen_div(struct nx_clkgen_regs * const clkgen, int clkgen_level)
{
	return ((clkgen->gen[clkgen_level << 1] >> 5) & 0xFF) + 1;
}

inline int  nx_get_clkgen_src(struct nx_clkgen_regs * const clkgen, int clkgen_level)
{
	return (clkgen->gen[clkgen_level << 1] >> 2) & 0x7;
}

inline void nx_set_clkgen_bclk_enb(struct nx_clkgen_regs * const clkgen, int bclk_enb)
{
	if (bclk_enb == 0)
		clkgen->enb &= ~(3 << 0);
	else
		clkgen->enb |=  (3 << 0);
}

inline void nx_set_clkgen_pclk_enb(struct nx_clkgen_regs * const clkgen, int pclk_enb)
{
	if (pclk_enb == 0)
		clkgen->enb &= ~(1 << 3);
	else
		clkgen->enb |=  (1 << 3);
}

inline void nx_set_clkgen_div_enb(struct nx_clkgen_regs * const clkgen, int div_enb)
{
	if (div_enb == 0)
		clkgen->enb &= ~(1 << 2);
	else
		clkgen->enb |=  (1 << 2);
}

inline void nx_set_clkgen_div(struct nx_clkgen_regs * const clkgen, int clkgen_level, int div)
{
	clkgen->gen[clkgen_level] = (clkgen->gen[clkgen_level]	\
					& ~(0xFF << 5))		\
					| ((div - 1) << 5);
}

inline void nx_set_clkgen_src(struct nx_clkgen_regs * const clkgen, int clkgen_level, int src)
{
	clkgen->gen[clkgen_level] = (clkgen->gen[clkgen_level]	\
					& ~(0x7 << 2))		\
					| (src << 2);
}

