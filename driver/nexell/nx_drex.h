/*
 * Copyright (C) 2017
 * Author: metro94 <flattiles@gmail.com>
 *
 * Version: v1.0
 * --- Update time: 02/07/2017
 * --- Description: First build; header of driver for Nexell SoC DREX
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

#ifndef __NX_DREX_H__
#define __NX_DREX_H__

#include <common.h>

#define NX_DREX_QOS_NUMBER			16

struct nx_drex_regs {
	volatile uint32_t \
		con_control,			// 0x0
		mem_control,			// 0x4
		cg_control,			// 0x8
		__rsvd0,			// 0xC
		direct_cmd,			// 0x10
		prech_config_0,			// 0x14
		phy_control[1],			// 0x18
		prech_config_1,			// 0x1C
		timing_rfc_pb,			// 0x20
		__rsvd1,			// 0x24
		pwr_dn_config,			// 0x28
		timing_pzq,			// 0x2C
		timing_aref,			// 0x30
		timing_row,			// 0x34
		timing_data_0,			// 0x38
		timing_power_0,			// 0x3C
		phy_status,			// 0x40
		etc_timing,			// 0x44
		chip_status,			// 0x48
		__rsvd2[(0x54 - 0x4C) / 4],	// 0x4C ~ 0x50
		mr_status,			// 0x54
		__rsvd3[(0x60 - 0x58) / 4],	// 0x58 ~ 0x5C
		qos_control[32],		// 0x60 ~ 0xDC
		timing_set_sw,			// 0xE0
		__rsvd4,			// 0xE4
		timing_data_1,			// 0xE8
		timing_power_1,			// 0xEC
		__rsvd5,			// 0xF0
		wr_tra_config,			// 0xF4
		rd_lvl_config,			// 0xF8
		__rsvd6,			// 0xFC
		brb_rsv_control,		// 0x100
		brb_rsv_config,			// 0x104
		brb_qos_config,			// 0x108
		__rsvd7[(0x120 - 0x10C) / 4],	// 0x10C ~ 0x11C
		wr_lvl_config[2],		// 0x120 ~ 0x124
		wr_lvl_status,			// 0x128
		__rsvd8[(0x150 - 0x12C) / 4],	// 0x12C ~ 0x14C
		ctrl_io_rdata,			// 0x150
		__rsvd9[(0x160 - 0x154) / 4],	// 0x154 ~ 0x15C
		ca_cal_config[2],		// 0x160 ~ 0x164
		ca_cal_status,			// 0x168
		__rsvd10[(0x200 - 0x16C) / 4],	// 0x16C ~ 0x1FC
		emergent_config[2],		// 0x200 ~ 0x204
		__rsvd11[(0x210 - 0x208) / 4];	// 0x208 ~ 0x20C
	
	struct {
		volatile uint32_t \
			control,		// 0x0
			config_r,		// 0x4
			config_w,		// 0x8
			__rsvd;			// 0xC
	} bp[4];				// 0x210 ~ 0x24C
};

#endif

