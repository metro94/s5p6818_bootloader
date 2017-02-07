/*
 * Copyright (C) 2017
 * Author: metro94 <flattiles@gmail.com>
 *
 * Version: v1.0
 * --- Update time: 02/07/2017
 * --- Description: First build; header for I/O operation
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

#ifndef __IO_H__
#define __IO_H__

#include <common.h>

#define ref64(addr)			(*(volatile uint64_t *)(addr))
#define read64(addr, val)		(val = ref64(addr))
#define write64(addr, val)		(ref64(addr) = val)
#define setbits64(addr, set)		(ref64(addr) |= (set))
#define clrbits64(addr, clr)		(ref64(addr) &= ~(clr))
#define tglbits64(addr, tgl)		(ref64(addr) ^= (tgl))
#define clrsetbits64(addr, clr, set)	(ref64(addr) = (ref64(addr) & ~(clr)) | (set))

#define ref32(addr)			(*(volatile uint32_t *)(addr))
#define read32(addr, val)		(val = ref32(addr))
#define write32(addr, val)		(ref32(addr) = val)
#define setbits32(addr, set)		(ref32(addr) |= (set))
#define clrbits32(addr, clr)		(ref32(addr) &= ~(clr))
#define tglbits32(addr, tgl)		(ref32(addr) ^= (tgl))
#define clrsetbits32(addr, clr, set)	(ref32(addr) = (ref32(addr) & ~(clr)) | (set))

#define ref8(addr)			(*(volatile uint8_t *)(addr))
#define read8(addr, val)		(val = ref8(addr))
#define write8(addr, val)		(ref8(addr) = val)

#endif
