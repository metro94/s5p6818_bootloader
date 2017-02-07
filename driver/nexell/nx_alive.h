/*
 * Copyright (C) 2017
 * Author: metro94 <flattiles@gmail.com>
 *
 * Version: v1.0
 * --- Update time: 02/07/2017
 * --- Description: First build; header of driver for Nexell SoC Alive
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

#ifndef __NX_ALIVE_H__
#define __NX_ALIVE_H__

#include <common.h>

struct __nx_alive_unit {
	volatile uint32_t \
		reset,				// 0x0
		set,				// 0x4
		read;				// 0x8
} __attribute__ ((packed));

struct nx_alive_regs {
	volatile uint32_t \
		power_gating;			// 0x0
	
	struct __nx_alive_unit \
		gpio_async_det_mode[2],		// 0x4 ~ 0x18
		gpio_det_mode[4],		// 0x1C ~ 0x48
		gpio_det_enb,			// 0x4C ~ 0x54
		gpio_int_enb;			// 0x58 ~ 0x60
	
	volatile uint32_t \
		gpio_det_pending;		// 0x64
	
	struct __nx_alive_unit \
		scratch_0,			// 0x68 ~ 0x70
		gpio_pad_out_enb,		// 0x74 ~ 0x7C
		gpio_pad_pull_up,		// 0x80 ~ 0x88
		gpio_pad_out,			// 0x8C ~ 0x94
		vdd_ctrl;			// 0x98 ~ 0xA0
		
	volatile uint32_t \
		clear_wakeup_stat,		// 0xA4
		sleep_wakeup_stat;		// 0xA8
		
	struct __nx_alive_unit \
		scratch[8],			// 0xAC ~ 0x108
		vdd_off_delay;			// 0x10C ~ 0x114
	
	volatile uint32_t \
		vdd_off_delay_timer,		// 0x118
		gpio_input_value_read,		// 0x11C
		__rsvd[(0x400 - 0x120) / 4];	// 0x120 ~ 0x3FC
		
	struct {
		volatile uint32_t \
			rtc_time_count_setting,		// 0x0
			rtc_time_count_read,		// 0x4
			alarm_time_count_set,		// 0x8
			rtc_ctrl,			// 0xC
			rtc_int_enb,			// 0x10
			rtc_int_pending,		// 0x14
			rtc_core_por_time,		// 0x18
			rtc_scratch,			// 0x1C
			__rsvd[(0x100 - 0x20) / 4];	// 0x20 ~ 0xFC
	} rtc;					// 0x400 ~ 0x4FC
	
	volatile uint32_t \
		pmu_isolate,			// 0x500
		pmu_power_up_precharge,		// 0x504
		pmu_power_up_ack;		// 0x508
};

void nx_set_alive_changable(struct nx_alive_regs *);
void nx_set_alive_unchangable(struct nx_alive_regs *);
void nx_set_alive(struct __nx_alive_unit *, uint32_t);
uint32_t nx_get_alive(struct __nx_alive_unit const *);

#endif

