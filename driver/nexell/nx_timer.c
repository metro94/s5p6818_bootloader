/*
 * Copyright (C) 2017
 * Author: metro94 <flattiles@gmail.com>
 *
 * Version: v1.0
 * --- Update time: 02/07/2017
 * --- Description: First build; code of driver for Nexell SoC Timer
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

#include <nx_timer.h>

inline int  nx_get_timer_prescaler(struct nx_timer_regs *timer, int channel)
{
	if (channel < 2)
		return ((timer->cfg[0] >> 0) & 0xFF) + 1;
	else
		return ((timer->cfg[0] >> 8) & 0xFF) + 1;
}

inline int  nx_get_timer_divider(struct nx_timer_regs *timer, int channel)
{
	switch ((timer->cfg[1] >> (channel * 4)) & 0xF) {
	case NX_TIMER_DIVIDER_1:
		return 1;
	case NX_TIMER_DIVIDER_2:
		return 2;
	case NX_TIMER_DIVIDER_4:
		return 4;
	case NX_TIMER_DIVIDER_8:
		return 8;
	case NX_TIMER_DIVIDER_16:
		return 16;
	default:
		return 0;	// Indicates using TCLK
	}
}

inline uint32_t nx_get_timer_count_observation(struct nx_timer_regs *timer, int channel)
{
	switch (channel) {
	case 0:
		return timer->cnto_0;
	case 1:
		return timer->cnto_1;
	case 2:
		return timer->cnto_2;
	case 3:
		return timer->cnto_3;
	case 4:
		return timer->cnto_4;
	default:
		return 0;
	}
}

inline void nx_set_timer_prescaler(struct nx_timer_regs *timer, int channel, int prescaler)
{
	if (channel < 2)
		timer->cfg[0] = (timer->cfg[0] & ~(0xFF << 0)) | ((prescaler - 1) << 0);
	else
		timer->cfg[0] = (timer->cfg[0] & ~(0xFF << 8)) | ((prescaler - 1) << 8);
}

inline void nx_set_timer_divider(struct nx_timer_regs *timer, int channel, enum NX_TIMER_DIVIDER_MUX divider)
{
	timer->cfg[1] = (timer->cfg[1] & ~(0xF << (channel * 4))) | (divider << (channel * 4));
}

inline void nx_set_auto_reload(struct nx_timer_regs *timer, int channel, int reload)
{
	if (reload)
		switch (channel) {
		case 0:
			timer->con |=  (1 <<  3);
			break;
		case 1:
			timer->con |=  (1 << 11);
			break;
		case 2:
			timer->con |=  (1 << 15);
			break;
		case 3:
			timer->con |=  (1 << 19);
			break;
		case 4:
			timer->con |=  (1 << 22);
			break;
		default:
			break;
		}
	else
		switch (channel) {
		case 0:
			timer->con &= ~(1 <<  3);
			break;
		case 1:
			timer->con &= ~(1 << 11);
			break;
		case 2:
			timer->con &= ~(1 << 15);
			break;
		case 3:
			timer->con &= ~(1 << 19);
			break;
		case 4:
			timer->con &= ~(1 << 22);
			break;
		default:
			break;
		}
}

inline void nx_set_timer_count_buffer(struct nx_timer_regs *timer, int channel, uint32_t value)
{
	switch (channel) {
	case 0:
		timer->cntb_0 = value;
		timer->con |=  (1 <<  1);
		timer->con &= ~(1 <<  1);
		break;
	case 1:
		timer->cntb_1 = value;
		timer->con |=  (1 <<  9);
		timer->con &= ~(1 <<  9);
		break;
	case 2:
		timer->cntb_2 = value;
		timer->con |=  (1 << 13);
		timer->con &= ~(1 << 13);
		break;
	case 3:
		timer->cntb_3 = value;
		timer->con |=  (1 << 17);
		timer->con &= ~(1 << 17);
		break;
	case 4:
		timer->cntb_4 = value;
		timer->con |=  (1 << 21);
		timer->con &= ~(1 << 21);
		break;
	default:
		break;
	}
}

inline void nx_set_timer_compare_buffer(struct nx_timer_regs *timer, int channel, uint32_t value)
{
	switch (channel) {
	case 0:
		timer->cmpb_0 = value;
		timer->con |=  (1 <<  1);
		timer->con &= ~(1 <<  1);
		break;
	case 1:
		timer->cmpb_1 = value;
		timer->con |=  (1 <<  9);
		timer->con &= ~(1 <<  9);
		break;
	case 2:
		timer->cmpb_2 = value;
		timer->con |=  (1 << 13);
		timer->con &= ~(1 << 13);
		break;
	case 3:
		timer->cmpb_3 = value;
		timer->con |=  (1 << 17);
		timer->con &= ~(1 << 17);
		break;
	default:
		break;
	}
}

inline void nx_start_timer(struct nx_timer_regs *timer, int channel)
{
	switch (channel) {
	case 0:
		timer->con |=  (1 <<  0);
		break;
	case 1:
		timer->con |=  (1 <<  8);
		break;
	case 2:
		timer->con |=  (1 << 12);
		break;
	case 3:
		timer->con |=  (1 << 16);
		break;
	case 4:
		timer->con |=  (1 << 20);
		break;
	default:
		break;
	}
}

inline void nx_stop_timer(struct nx_timer_regs *timer, int channel)
{
	switch (channel) {
	case 0:
		timer->con &= ~(1 <<  0);
		break;
	case 1:
		timer->con &= ~(1 <<  8);
		break;
	case 2:
		timer->con &= ~(1 << 12);
		break;
	case 3:
		timer->con &= ~(1 << 16);
		break;
	case 4:
		timer->con &= ~(1 << 20);
		break;
	default:
		break;
	}
}
