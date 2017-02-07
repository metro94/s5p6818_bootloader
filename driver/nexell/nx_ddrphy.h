/*
 * Copyright (C) 2017
 * Author: metro94 <flattiles@gmail.com>
 *
 * Version: v1.0
 * --- Update time: 02/07/2017
 * --- Description: First build; header of driver for Nexell SoC DDRPHY
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

#ifndef __NX_DDRPHY_H__
#define __NX_DDRPHY_H__

#include <common.h>

struct nx_ddrphy_regs {
	volatile uint32_t \
		phy_con[6],			// 0x0 ~ 0x14
		lp_con[1],			// 0x18
		r_odt_con[1],			// 0x1C
		offset_r_con[3],		// 0x20 ~ 0x28
		__rsvd0,			// 0x2C
		offset_w_con[3],		// 0x30 ~ 0x38
		__rsvd1,			// 0x3C
		offset_c_con[3],		// 0x40 ~ 0x48
		shift_c_con[1],			// 0x4C
		offset_d_con[1],		// 0x50
		__rsvd2,			// 0x54
		lp_ddr_con[5],			// 0x58 ~ 0x68
		wr_lvl_con[4],			// 0x6C ~ 0x78
		ca_deskew_con[4],		// 0x7C ~ 0x88
		__rsvd3[(0x94 - 0x8C) / 4],	// 0x8C ~ 0x90
		ca_deskew_con4,			// 0x94
		__rsvd4,			// 0x98
		drv_ds_con[2],			// 0x9C ~ 0xA0
		__rsvd5[(0xB0 - 0xA4) / 4],	// 0xA4 ~ 0xAC
		mdll_con[2],			// 0xB0 ~ 0xB4
		__rsvd6[(0xC0 - 0xB8) / 4],	// 0xB8 ~ 0xBC
		zq_con[4],			// 0xC0 ~ 0xCC
		t_rd_data_con[3],		// 0xD0 ~ 0xD8
		cal_wl_stat,			// 0xDC
		cal_fail_stat[4],		// 0xE0 ~ 0xEC
		cal_gt_vwmc[3],			// 0xF0 ~ 0xF8
		cal_gt_cyc,			// 0xFC
		cal_rd_vwmc[3],			// 0x100 ~ 0x108
		__rsvd7,			// 0x10C
		cal_rd_vwml[3],			// 0x110 ~ 0x118
		__rsvd8,			// 0x11C
		cal_rd_vwmr[3],			// 0x120 ~ 0x128
		__rsvd9,			// 0x12C
		cal_wr_vwmc[3],			// 0x130 ~ 0x138
		__rsvd10,			// 0x13C
		cal_wr_vwml[3],			// 0x140 ~ 0x148
		__rsvd11,			// 0x14C
		cal_wr_vwmr[3],			// 0x150 ~ 0x158
		__rsvd12,			// 0x15C
		cal_dm_vwmc[3],			// 0x160 ~ 0x168
		__rsvd13,			// 0x16C
		cal_dm_vwml[3],			// 0x170 ~ 0x178
		__rsvd14,			// 0x17C
		cal_dm_vwmr[3];			// 0x180 ~ 0x188
};

#endif

