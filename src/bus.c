/*
 * Copyright (C) 2017
 * Author: metro94 <flattiles@gmail.com>
 *
 * Version: v1.0
 * --- Update time: 02/07/2017
 * --- Description: First build; code for SoC bus
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

#include <bus.h>

void init_bus(void)
{
	debug("", "\n");
	debug(DEBUG_LEVEL_INFO, "Initializing CCI-400 bus\n");
	
	cci_400->speculation_control |= (1 << 0);
	cci_400->speculation_control |= (1 << 1);
	
	cci_400->control_override = (1 << 3);
	
	cci_400->slave[BUS_ID_CORESIGHT].snoop_control = 0;
	cci_400->slave[BUS_ID_CODA960].snoop_control = 0;
	cci_400->slave[BUS_ID_TOP].snoop_control = 0;
	
	cci_400->slave[BUS_ID_CPU_CLUSTER_0].snoop_control = 0x3;
	while (cci_400->status & (1 << 0));
	
	cci_400->slave[BUS_ID_CPU_CLUSTER_1].snoop_control = 0x3;
	while (cci_400->status & (1 << 0));
}
