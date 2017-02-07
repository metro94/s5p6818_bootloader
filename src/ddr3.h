/*
 * Copyright (C) 2017
 * Author: metro94 <flattiles@gmail.com>
 *
 * Version: v1.0
 * --- Update time: 02/07/2017
 * --- Description: First build; code for DDR3 SDRAM Initialization
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

#ifndef __DDR3_H__
#define __DDR3_H__

#include <common.h>
#include <io.h>
#include <std/debug.h>
#include <std/printf.h>

#include <nexell/nx_iprst.h>
#include <nexell/nx_drex.h>
#include <nexell/nx_tzasc.h>
#include <nexell/nx_ddrphy.h>
#include <timer.h>

enum DDR3_CMD_TYPE {
	DDR3_CMD_MRS	= 0x0,
	DDR3_CMD_PALL	= 0x1,
	DDR3_CMD_PRE	= 0x2,
	DDR3_CMD_DPD	= 0x3,
	DDR3_CMD_REFS	= 0x4,
	DDR3_CMD_REFA	= 0x5,
	DDR3_CMD_CKEL	= 0x6,
	DDR3_CMD_NOP	= 0x7,
	DDR3_CMD_REFSX	= 0x8,
	DDR3_CMD_MRR	= 0x9,
	DDR3_CMD_ZQINIT	= 0xa,
	DDR3_CMD_ZQOPER	= 0xb,
	DDR3_CMD_ZQCS	= 0xc
};

void init_ddr3(void);
void test_ddr3(void);

// No need to export functions below
// void send_ddr3_direct_cmd(enum DDR3_CMD_TYPE, int, int, int);
// void do_ddr3_read_leveling(void)
// void do_ddr3_hw_write_leveling(void);
// void do_ddr3_gate_leveling(void);
// void do_ddr3_zq_calibration(void);
// void do_ddr3_write_latency_calibration(void);
// void do_ddr3_write_dq_calibration(void);

#endif
