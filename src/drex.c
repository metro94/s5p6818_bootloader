/*
 * Copyright (C) 2017
 * Author: metro94 <flattiles@gmail.com>
 *
 * Version: v1.0
 * --- Update time: 02/07/2017
 * --- Description: First build; code for DREX QoS Setting
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

#include <drex.h>

struct __drex_qos_table const __drex_qos[NX_DREX_QOS_NUMBER] = {
	{0xFFF, 0x0},
	{0xE00, 0x0},
	{0xD00, 0x0},
	{0xC00, 0x0},
	{0xB00, 0x0},
	{0xA00, 0x0},
	{0x900, 0x0},
	{0x800, 0x0},
	{0x700, 0x0},
	{0x600, 0x0},
	{0x500, 0x0},
	{0x400, 0x0},
	{0x300, 0x0},
	{0x200, 0x0}
};

void set_drex_qos(void)
{
	int qos_index;
	
	debug("", "\n");
	debug(DEBUG_LEVEL_INFO, "Setting DREX QoS\n");
	
	nx_drex->brb_rsv_config = \
		(0xF << 28) |
		(0x3 << 24) |	// Bottom bus
		(0x8 << 20) |	// CCI-400 bus
		(0xF << 16) |	// Display bus
		(0xF << 12) |
		(0x3 <<  8) |	// Bottom bus
		(0x8 <<  4) |	// CCI-400 bus
		(0xF <<  0);	// Display bus
		
	nx_drex->brb_rsv_control = \
		(0 << 7) |
		(1 << 6) |	// Bottom bus
		(1 << 5) |	// CCI-400 bus
		(1 << 4) |	// Display bus
		(0 << 3) |
		(1 << 2) |	// Bottom bus
		(1 << 1) |	// CCI-400 bus
		(1 << 0);	// Display bus
		
	for (qos_index = 0; qos_index < NX_DREX_QOS_NUMBER; ++qos_index) {
		nx_drex->qos_control[qos_index << 1] = (__drex_qos[qos_index].timeout << 0) | (__drex_qos[qos_index].threshold << 16);
	}
	
	nx_tieoff[77] = (nx_tieoff[77] & ~(0xF <<  0)) | (0x5 <<  0);
	nx_tieoff[76] = (nx_tieoff[76] & ~(0xF << 26)) | (0x5 << 26);
	
	nx_tieoff[130] =
		( 5 << 24) |	// A53_1_AR
		( 5 << 20) |	// A53_1_AW
		( 5 << 16) |	// A53_0_AR
		( 5 << 12) |	// A53_0_AW
		(14 <<  8) |	// CODA960_AR
		(14 <<  8) |	// CODA960_W
		(14 <<  0);	// CODA960_AW

	nx_tieoff[74] =
		( 5 << 24) |	// GMAC_AR
		( 5 << 20) |	// GMAC_W
		( 5 << 16) |	// GMAC_AW
		( 5 << 12) |	// SCALER_AR
		( 5 <<  8) |	// SCALER_W
		( 5 <<  8) |	// SCALER_AW
		( 5 <<  0);	// DEINTERLACE_AR

	nx_tieoff[73] =
		( 5 << 28) |	// DEINTERLACE_W
		( 5 << 24) |	// DEINTERLACE_AW
		(14 << 20) |	// GR3D_AR
		(14 << 16) |	// GR3D_W
		(14 << 12) |	// GR3D_AW
		(15 <<  8);	// MLC1_AR
		
	nx_tieoff[72] =
		(15 << 27);	// MLC0_AR

	nx_tieoff[71] =
		( 5 << 16) |	// CORESIGHT_AR
		( 5 << 12) |	// CORESIGHT_W
		( 5 <<  8) |	// CORESIGHT_AW
		(10 <<  4) |	// VIP2_AW
		(10 <<  0);	// VIP2_W
		
	nx_tieoff[70] =
		(10 << 24) |	// VIP2_AR
		(10 << 20) |	// VIP1_AW
		(10 << 16) |	// VIP1_W
		(10 << 12) |	// VIP1_AR
		(10 <<  8) |	// VIP0_AW
		(10 <<  4) |	// VIP0_W
		(10 <<  0);	// VIP0_AR

	nx_tieoff[69] = (nx_tieoff[69] & ~(0xFFFFFF << 5)) | (
		( 5 << 25) |	// DMAC_HW
		( 5 << 21) |	// DMAC_HA
		( 5 << 17) |	// SDMMC_HW
		( 5 << 13) |	// SDMMC_HA
		( 5 <<  9) |	// DMAC_MP2TS_HW
		( 5 <<  5));	// DMAC_MP2TS_HA
}
