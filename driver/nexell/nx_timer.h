/*
 * Copyright (C) 2017
 * Author: metro94 <flattiles@gmail.com>
 *
 * Version: v1.0
 * --- Update time: 02/07/2017
 * --- Description: First build; header of driver for Nexell SoC Timer
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

#ifndef __NX_TIMER_H__
#define __NX_TIMER_H__

struct nx_timer_regs {
	volatile uint32_t \
		cfg[2],		// 0x0 ~ 0x4
		con,		// 0x8
		cntb_0,		// 0xC
		cmpb_0,		// 0x10
		cnto_0,		// 0x14
		cntb_1,		// 0x18
		cmpb_1,		// 0x1C
		cnto_1,		// 0x20
		cntb_2,		// 0x24
		cmpb_2,		// 0x28
		cnto_2,		// 0x2C
		cntb_3,		// 0x30
		cmpb_3,		// 0x34
		cnto_3,		// 0x38
		cntb_4,		// 0x3C
		cnto_4,		// 0x40
		int_cstat;	// 0x44
};

enum NX_TIMER_DIVIDER_MUX {
	NX_TIMER_DIVIDER_1 = 0,
	NX_TIMER_DIVIDER_2,
	NX_TIMER_DIVIDER_4,
	NX_TIMER_DIVIDER_8,
	NX_TIMER_DIVIDER_16,
	NX_TIMER_DIVIDER_TCLK
};

int  nx_get_timer_prescaler(struct nx_timer_regs *, int);
int  nx_get_timer_divider(struct nx_timer_regs *, int);
uint32_t nx_get_timer_count_observation(struct nx_timer_regs *, int);
void nx_set_timer_prescaler(struct nx_timer_regs *, int, int);
void nx_set_timer_divider(struct nx_timer_regs *, int, enum NX_TIMER_DIVIDER_MUX);
void nx_set_auto_reload(struct nx_timer_regs *, int, int);
void nx_set_timer_count_buffer(struct nx_timer_regs *, int, uint32_t);
void nx_set_timer_compare_buffer(struct nx_timer_regs *, int, uint32_t);
void nx_start_timer(struct nx_timer_regs *, int);
void nx_stop_timer(struct nx_timer_regs *, int);

#endif
