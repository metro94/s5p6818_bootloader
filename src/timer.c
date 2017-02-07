/*
 * Copyright (C) 2017
 * Author: metro94 <flattiles@gmail.com>
 *
 * Version: v1.0
 * --- Update time: 02/07/2017
 * --- Description: First build; code for SoC Timers
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

#include <timer.h>

void init_system_counter(void)
{
	int prescaler;
	
	nx_do_iprst(nx_iprst_block, NX_IPRST_ID_TIMER);
	// Uses 1/16 Divider
	// prescaler = round((double)get_pclk_freq() / PI_SYSTEM_COUNTER_FREQ / 16);
	prescaler = 10;
	nx_set_timer_prescaler(nx_timer, PI_SYSTEM_COUNTER_TIMER_CHANNEL, prescaler);
	nx_set_timer_divider(nx_timer, PI_SYSTEM_COUNTER_TIMER_CHANNEL, NX_TIMER_DIVIDER_16);
	nx_set_auto_reload(nx_timer, PI_SYSTEM_COUNTER_TIMER_CHANNEL, 0);
}

void delay_us(uint32_t us)
{
	nx_set_timer_count_buffer(nx_timer, PI_SYSTEM_COUNTER_TIMER_CHANNEL, us);
	nx_start_timer(nx_timer, PI_SYSTEM_COUNTER_TIMER_CHANNEL);
	while (nx_get_timer_count_observation(nx_timer, PI_SYSTEM_COUNTER_TIMER_CHANNEL) > 0);
	nx_stop_timer(nx_timer, PI_SYSTEM_COUNTER_TIMER_CHANNEL);
}

void delay_ms(uint32_t ms)
{
	// Assumes (ms * 1000) < UINT32_MAX
	delay_us(ms * 1000);
}
