/*
 * Copyright (C) 2017
 * Author: metro94 <flattiles@gmail.com>
 *
 * Version: v1.2
 * --- Update time: 02/12/2017
 * --- Description: Code for SoC TrustZone Controller
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

#include <trustzone.h>

void set_trustzone(void)
{
	int index, region;
	
	// Sets all Decode Protection to Non-secure
	for (index = 0; index < TZPC_NUMBERS; ++index) {
		tzpc[index].r0_size = 0x200;	// Sets the entire RAM
		for (region = 0; region < 4; ++region) {
			tzpc[index].decode_protection[region].clr = 0x00000000;
			tzpc[index].decode_protection[region].set = 0xFFFFFFFF;
		}
	}
	
	// Sets TZASC disabled
	for (index = 1; index < 16; ++index) {	// Keeps RS[0] in default
		tzasc->region[index].setup_high = 0;
		tzasc->region[index].setup_low  = 0;
		tzasc->region[index].attributes =
			( 0xF << 28) |		// Secure/Non-secure Read/Write is premitted
			(0xFF <<  8) |		// All subregion is disabled
			(0x20 <<  1) |		// Size of region is 128 KB
			(   0 <<  0);		// Region is disabled
	}
	tzasc->speculation_control = 0;		// Read/Write access speculation is disabled
}

