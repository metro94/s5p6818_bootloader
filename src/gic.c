/*
 * Copyright (C) 2017
 * Author: metro94 <flattiles@gmail.com>
 *
 * Version: v1.2
 * --- Update time: 02/12/2017
 * --- Description: Code for SoC GIC
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

#include <gic.h>

void set_gic(void)
{
	int index, ppi_index, ppi_cnt;
	
	// Sets Master CPU
	gic_400->gicc.pmr = 0xFF;
	gic_400->gicc.ctrl =
		(0 << 10) |
		(0 <<  9) |
		(1 <<  8) |
		(1 <<  7) |
		(1 <<  6) |
		(0 <<  5) |
		(0 <<  4) |
		(1 <<  3) |
		(0 <<  2) |
		(1 <<  1) |
		(1 <<  0);
	for (index = 0; index < 8; ++index)
		gic_400->gicd.ipriorityr[index] = 0;
	gic_400->gicd.icenabler[0] = 0xFFFFFFFF;	// Disables the forwarding of corresponding interrupt
	gic_400->gicd.icpendr[0]   = 0xFFFFFFFF;	// Inactives interrupts
	gic_400->gicd.igroupr[0]   = 0xFFFFFFFF;	// Group 1
	
	// Sets All interrupts
	gic_400->gicd.ctrl =	// Disables Group0 & Group1
		(0 << 1) |
		(0 << 0);
	ppi_cnt = gic_400->gicd.typer & 0x1F;	// Maximum number of interrupts
	for (ppi_index = 1; ppi_index <= ppi_cnt; ++ppi_index) {
		gic_400->gicd.icenabler[ppi_index] = 0xFFFFFFFF;
		gic_400->gicd.icpendr[ppi_index]   = 0xFFFFFFFF;
		for (index = 0; index < 8; ++index)
			gic_400->gicd.ipriorityr[ppi_index * 8 + index] = 0x80808080;	// Lowest priority
		gic_400->gicd.igroupr[ppi_index]   = 0xFFFFFFFF;
	}
	gic_400->gicd.ctrl =	// Enables Group0 & Group1
		(1 << 1) |
		(1 << 0);
}
