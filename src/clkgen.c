/*
 * Copyright (C) 2017
 * Author: metro94 <flattiles@gmail.com>
 *
 * Version: v1.0
 * --- Update time: 02/07/2017
 * --- Description: First build; code for Clock Generator
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

#include <clkgen.h>

inline int  get_clkgen_state(struct nx_clkgen_info const clkgen_info)
{
	if (clkgen_info.level == 0) {
		switch (clkgen_info.mode) {
		case NX_CLKGEN_MODE_BCLK:
			return nx_get_clkgen_bclk_enb(clkgen_info.clkgen);
		case NX_CLKGEN_MODE_PCLK:
			return nx_get_clkgen_pclk_enb(clkgen_info.clkgen);
		default:
			return nx_get_clkgen_bclk_enb(clkgen_info.clkgen) & nx_get_clkgen_pclk_enb(clkgen_info.clkgen);
		}
	} else {
		return nx_get_clkgen_div_enb(clkgen_info.clkgen);
	}
}

inline void set_clkgen_state(struct nx_clkgen_info const clkgen_info, int clkgen_enb)
{
	if (clkgen_info.mode & NX_CLKGEN_MODE_BCLK)
		nx_set_clkgen_bclk_enb(clkgen_info.clkgen, clkgen_enb);
	if (clkgen_info.mode & NX_CLKGEN_MODE_PCLK)
		nx_set_clkgen_pclk_enb(clkgen_info.clkgen, clkgen_enb);
	if (clkgen_info.level > 0) {
		nx_set_clkgen_div_enb(clkgen_info.clkgen, clkgen_enb);
	}
}

inline int  get_clkgen_freq(struct nx_clkgen_info const clkgen_info)
{
	switch (clkgen_info.level) {
	case 0:
		// If Clock Generator uses both BCLK and PCLK, return PCLK frequency
		if (clkgen_info.mode & NX_CLKGEN_MODE_BCLK)
			return get_bclk_freq();
		if (clkgen_info.mode & NX_CLKGEN_MODE_PCLK)
			return get_pclk_freq();
		return 0;
	case 1:
		return get_pll_freq(nx_get_clkgen_src(clkgen_info.clkgen, 0))	\
			/ nx_get_clkgen_div(clkgen_info.clkgen, 0);
	case 2:
		// Assumes using Level 1 input as Level 2 input
		return get_pll_freq(nx_get_clkgen_src(clkgen_info.clkgen, 0))	\
			/ nx_get_clkgen_div(clkgen_info.clkgen, 0)		\
			/ nx_get_clkgen_div(clkgen_info.clkgen, 1);
	default:
		return 0;
	}
}

inline void set_clkgen_freq(struct nx_clkgen_info const clkgen_info, int target_freq)
{
	int divisor;
	
	switch (clkgen_info.level) {
	case 0:
		// Simply not changed
		break;
	case 1:
		divisor = round((double)get_pll_freq(nx_get_clkgen_src(clkgen_info.clkgen, 0)) / target_freq);
		nx_set_clkgen_div(clkgen_info.clkgen, 0, divisor);
		break;
	case 2:
		// Assumes using Level 1 input as Level 2 input
		divisor = round((double)get_pll_freq(nx_get_clkgen_src(clkgen_info.clkgen, 0)) / target_freq);
		if (divisor <= 256) {
			nx_set_clkgen_div(clkgen_info.clkgen, 0, 1);
			nx_set_clkgen_div(clkgen_info.clkgen, 1, divisor);
		} else if (divisor <= 512) {
			nx_set_clkgen_div(clkgen_info.clkgen, 0, 2);
			nx_set_clkgen_div(clkgen_info.clkgen, 1, divisor / 2);
		} else if (divisor <= 1024) {
			nx_set_clkgen_div(clkgen_info.clkgen, 0, 4);
			nx_set_clkgen_div(clkgen_info.clkgen, 1, divisor / 4);
		} else {
			nx_set_clkgen_div(clkgen_info.clkgen, 0, 8);
			nx_set_clkgen_div(clkgen_info.clkgen, 1, divisor / 8);
		}
	default:
		return;
	}
}
