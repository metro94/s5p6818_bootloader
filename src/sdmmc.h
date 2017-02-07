/*
 * Copyright (C) 2017
 * Author: metro94 <flattiles@gmail.com>
 *
 * Version: v1.0
 * --- Update time: 02/07/2017
 * --- Description: First build; header for SD/MMC operation
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

#ifndef __SDMMC_H__
#define __SDMMC_H__

#include <common.h>
#include <io.h>
#include <sd.h>
#include <std/debug.h>
#include <std/math.h>

#include <nexell/nx_alive.h>
#include <nexell/nx_sdmmc.h>
#include <clksrc.h>
#include <clkgen.h>
#include <timer.h>

struct sd_info_table {
	uint32_t rca;
	uint32_t high_capacity;
	uint32_t tran_speed;
	uint32_t block_size;
	uint64_t capacity;
};

int  init_sdcard(void);
void reset_sdmmc(void);
void init_nx_sdmmc(int);
void reset_nx_sdmmc(int);
int  init_sdcard_cmd(void);
void init_sdcard_detect(void);
int  is_sdcard_detected(void);
void set_sdmmc_clk_freq(int, int, int);
void update_sdmmc_clk_reg(void);
uint32_t send_sd_cmd(enum sd_command, uint32_t, uint32_t);
int  calc_sd_tran_speed(int, int);
void read_sd_block(void *, uint32_t, uint32_t);

#endif
