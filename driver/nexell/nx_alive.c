/*
 * Copyright (C) 2017
 * Author: metro94 <flattiles@gmail.com>
 *
 * Version: v1.0
 * --- Update time: 02/07/2017
 * --- Description: First build; code of driver for Nexell SoC Alive
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

#include <nx_alive.h>

inline void nx_set_alive_changable(struct nx_alive_regs *alive)
{
	alive->power_gating = (1 << 0);
}

inline void nx_set_alive_unchangable(struct nx_alive_regs *alive)
{
	alive->power_gating = (0 << 0);
}

inline void nx_set_alive(struct __nx_alive_unit *alive_unit, uint32_t data)
{
	alive_unit->set   = data;
	alive_unit->reset = 0xFFFFFFFF;
	alive_unit->reset = 0x00000000;
	alive_unit->set   = 0x00000000;
}

inline uint32_t nx_get_alive(struct __nx_alive_unit const *alive_unit)
{
	return alive_unit->read;
}

