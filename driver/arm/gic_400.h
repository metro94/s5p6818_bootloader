/*
 * Copyright (C) 2017
 * Author: metro94 <flattiles@gmail.com>
 *
 * Version: v1.2
 * --- Update time: 02/12/2017
 * --- Description: Header for GIC-400
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

#ifndef __GIC_400_H__
#define __GIC_400_H__

#include <common.h>

struct gic_400_regs {
	volatile uint32_t \
		__rsvd[(0x1000 - 0x0) / 4];	// 0x0 ~ 0xFFC
		
	struct {
		volatile uint32_t \
			ctrl,				// 0x0
			typer,				// 0x4
			iidr,				// 0x8
			__rsvd0[(0x80 - 0xC) / 4],	// 0xC ~ 0x7C
			igroupr[5],			// 0x80 ~ 0x90
			__rsvd1[(0x100 - 0x94) / 4],	// 0x94 ~ 0xFC
			isenabler[5],			// 0x100 ~ 0x110
			__rsvd2[(0x180 - 0x114) / 4],	// 0x114 ~ 0x17C
			icenabler[5],			// 0x180 ~ 0x190
			__rsvd3[(0x200 - 0x194) / 4],	// 0x194 ~ 0x1FC
			ispendr[5],			// 0x200 ~ 0x210
			__rsvd4[(0x280 - 0x214) / 4],	// 0x214 ~ 0x27C
			icpendr[5],			// 0x280 ~ 0x290
			__rsvd5[(0x300 - 0x294) / 4],	// 0x294 ~ 0x2FC
			isactiver[5],			// 0x300 ~ 0x310
			__rsvd6[(0x380 - 0x314) / 4],	// 0x314 ~ 0x37C
			icactiver[5],			// 0x380 ~ 0x390
			__rsvd7[(0x400 - 0x394) / 4],	// 0x394 ~ 0x3FC
			ipriorityr[40],			// 0x400 ~ 0x49C
			__rsvd8[(0x800 - 0x4A0) / 4],	// 0x4A0 ~ 0x7FC
			itargetsr[40],			// 0x800 ~ 0x89C
			__rsvd9[(0xC00 - 0x8A0) / 4],	// 0x8A0 ~ 0xBFC
			icfgr[10],			// 0xC00 ~ 0xC24
			__rsvd10[(0xD00 - 0xC28) / 4],	// 0xC28 ~ 0xCFC
			ppisr,				// 0xD00
			spisr[4],			// 0xD04 ~ 0xD10
			__rsvd11[(0xF00 - 0xD14) / 4],	// 0xD14 ~ 0xEFC
			sgir,				// 0xF00
			__rsvd12[(0xF10 - 0xF04) / 4],	// 0xF04 ~ 0xF0C
			cpendsgir[4],			// 0xF10 ~ 0xF1C
			spendsgir[4],			// 0xF20 ~ 0xF2C
			__rsvd13[(0x1000 - 0xF30) / 4];	// 0xF30 ~ 0xFFC
	} gicd;					// 0x1000 ~ 0x1FFC
	
	struct {
		volatile uint32_t \
			ctrl,				// 0x0
			pmr,				// 0x4
			bpr,				// 0x8
			iar,				// 0xC
			eoir,				// 0x10
			rpr,				// 0x14
			hppir,				// 0x18
			abpr,				// 0x1C
			aiar,				// 0x20
			aeoir,				// 0x24
			ahippir,			// 0x28
			__rsvd0[(0xD0 - 0x2C) / 4],	// 0x2C ~ 0xCC
			apr0,				// 0xD0
			__rsvd1[(0xE0 - 0xD4) / 4],	// 0xD4 ~ 0xDC
			nsapr0,				// 0xE0
			__rsvd2[(0x1000 - 0xE4) / 4],	// 0xE4 ~ 0xFFC
			dir;				// 0x1000
	} gicc;
};

#endif
