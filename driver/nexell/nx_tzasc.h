/*
 * Copyright (C) 2017
 * Author: metro94 <flattiles@gmail.com>
 *
 * Version: v1.0
 * --- Update time: 02/07/2017
 * --- Description: First build; header of driver for Nexell SoC TZASC
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

#ifndef __NX_TZASC_H__
#define __NX_TZASC_H__

#include <common.h>

struct nx_tzasc_regs {
	volatile uint32_t \
		config,				// 0x0
		action,				// 0x4
		ld_range,			// 0x8
		ld_select,			// 0xC
		int_status,			// 0x10
		int_clear,			// 0x14
		__rsvd0[(0x40 - 0x18) / 4];	// 0x18 ~ 0x3C
		
	struct {
		volatile uint32_t \
			addr_low_r,		// 0x0
			addr_high_r,		// 0x4
			ctrl_r,			// 0x8
			id_r,			// 0xC
			addr_low_w,		// 0x10
			addr_high_w,		// 0x14
			ctrl_w,			// 0x18
			id_w;			// 0x1C
	} fail[4];				// 0x40 ~ 0xBC
	
	volatile uint32_t \
		__rsvd1[(0x100 - 0xC0) / 4];	// 0xC0 ~ 0xFC
	
	struct {
		volatile uint32_t \
			low,			// 0x0
			high,			// 0x4
			attr,			// 0x8
			__rsvd;			// 0xC
	} rs[9];				// 0x100 ~ 0x18C
	
	volatile uint32_t \
		__rsvd2[(0xE00 - 0x190) / 4],	// 0x190 ~ 0xDFC
		it_ctrl,			// 0xE00
		it_input,			// 0xE04
		it_output,			// 0xE08
		__rsvd3[(0xF00 - 0xE0C) / 4],	// 0xE0C ~ 0xEFC
		mem_base_config[2],		// 0xF00 ~ 0xF04
		__rsvd4[(0xF10 - 0xF08) / 4],	// 0xF08 ~ 0xF0C
		mem_config[2];			// 0xF10 ~ 0xF14
};

#endif
