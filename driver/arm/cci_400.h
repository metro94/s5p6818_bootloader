/*
 * Copyright (C) 2017
 * Author: metro94 <flattiles@gmail.com>
 *
 * Version: v1.0
 * --- Update time: 02/07/2017
 * --- Description: First build; header of driver for ARM CCI-400
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

#ifndef __CCI_400_H__
#define __CCI_400_H__

#include <common.h>

struct cci_400_regs {
	volatile uint32_t \
		control_override,		// 0x0
		speculation_control,		// 0x4
		secure_access,			// 0x8
		status,				// 0xC
		imprecise_error,		// 0x10
		__rsvd0[(0x100 - 0x14) / 4],	// 0x14 ~ 0xFC
		pmcr,				// 0x100
		__rsvd1[(0xFD0 - 0x104) / 4],	// 0x104 ~ 0xFCC
		peripheral_id[8],		// 0xFD0 ~ 0xFE0
		component_id[4];		// 0xFF0 ~ 0XFFC
		
	struct {
		volatile uint32_t \
			snoop_control,			// 0x0
			shareable_override,		// 0x4
			__rsvd0[(0x100 - 0x8) / 4],	// 0x8 ~ 0xFC
			read_qos_value,			// 0x100
			write_qos_value,		// 0x104
			__rsvd1,			// 0x108
			qos_control,			// 0x10C
			max_ot,				// 0x110
			__rsvd2[(0x130 - 0x114) / 4],	// 0x114 ~ 0x12C
			regulator_target,		// 0x130
			regulator_scale,		// 0x134
			qos_range,			// 0x138
			__rsvd3[(0x1000 - 0x13C) / 4];	// 0x13C ~ 0xFFC
	} slave[5];				// 0x1000 ~ 0x5FFC
	
	volatile uint32_t \
		__rsvd2[(0x9004 - 0x6000) / 4],	// 0x6000 ~ 0x9000
		cycle_counter,			// 0x9004
		count_control,			// 0x9008
		overflow_flag_status,		// 0x900C
		__rsvd3[(0xA000 - 0x9010) / 4];	// 0x9010 ~ 0x9FFC
		
	struct {
		volatile uint32_t \
			event_select,			// 0x0
			event_count,			// 0x4
			counter_control,		// 0x8
			overflow_flag_status,		// 0xC
			__rsvd[(0x1000 - 0x10) / 4];	// 0x10 ~ 0xFFC
	} counter[4];				// 0xA000 ~ 0xDFFC
};

#endif
