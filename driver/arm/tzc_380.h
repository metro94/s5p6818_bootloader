#ifndef __TZC_380_H__
#define __TZC_380_H__

/*
 * Copyright (C) 2017
 * Author: metro94 <flattiles@gmail.com>
 *
 * Version: v1.2
 * --- Update time: 02/12/2017
 * --- Description: Header for TZASC TZC-380
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

struct tzc_380_regs {
	volatile uint32_t \
		configuration,			// 0x0
		action,				// 0x4
		lockdown_range,			// 0x8
		lockdown_select,		// 0xC
		int_status,			// 0x10
		int_clear,			// 0x14
		__rsvd0[(0x20 - 0x18) / 4],	// 0x18 ~ 0x1C
		fail_address_low,		// 0x20
		fail_address_high,		// 0x24
		fail_control,			// 0x28
		fail_id,			// 0x2C
		speculation_control,		// 0x30
		security_inversion_en,		// 0x34
		__rsvd1[(0x100 - 0x38) / 4];	// 0x38 ~ 0xFC
	
	struct {
		volatile uint32_t \
			setup_low,			// 0x0
			setup_high,			// 0x4
			attributes,			// 0x8
			__rsvd;				// 0xC
	} region[16];				// 0x100 ~ 0x1FC
	
	volatile uint32_t \
		__rsvd2[(0xE00 - 0x200) / 4],	// 0x200 ~ 0xDFC
		itcrg,				// 0xE00
		itip,				// 0xE04
		itop,				// 0xE08
		__rsvd3[(0xFD0 - 0xE0C) / 4],	// 0xE0C ~ 0xFCC
		periph_id_4,			// 0xFD0
		__rsvd4[(0xFE0 - 0xFD4) / 4],	// 0xFD4 ~ 0xFDC
		periph_id[4],			// 0xFE0 ~ 0xFEC
		component_id[4];		// 0xFF0 ~ 0xFFC
};

#endif
