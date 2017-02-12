/*
 * Copyright (C) 2017
 * Author: metro94 <flattiles@gmail.com>
 *
 * Version: v1.2
 * --- Update time: 02/12/2017
 * --- Description: Header for TZPC BP-147
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

#ifndef __BP_147_H__
#define __BP_147_H__

#include <common.h>

struct bp_147_regs {
	volatile uint32_t \
		r0_size,			// 0x0
		__rsvd0[(0x800 - 0x4) / 4];	// 0x4 ~ 0x7FC
		
	struct {
		volatile uint32_t \
			stat,				// 0x0
			set,				// 0x4
			clr;				// 0x8
	} decode_protection[4];			// 0x800 ~ 0x82C
	
	volatile uint32_t \
		__rsvd1[(0xFE0 - 0x830) / 4],	// 0x830 ~ 0xFDC
		peripheral_id[4],		// 0xFE0 ~ 0xFEC
		tzpc_id[4];			// 0xFF0 ~ 0xFFC
};

#endif
