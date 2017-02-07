/*
 * Copyright (C) 2017
 * Author: metro94 <flattiles@gmail.com>
 *
 * Version: v1.0
 * --- Update time: 02/07/2017
 * --- Description: First build; header of driver for Nexell SoC SD/MMC
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

#ifndef __NX_SDMMC_H__
#define __NX_SDMMC_H__

#include <common.h>

struct nx_sdmmc_regs {
	volatile uint32_t \
		ctrl,				// 0x0
		power_enb,			// 0x4
		clk_div,			// 0x8
		clk_src,			// 0xC
		clk_enb,			// 0x10
		timeout,			// 0x14
		card_type,			// 0x18
		block_size,			// 0x1C
		byte_count,			// 0x20
		int_mask,			// 0x24
		cmd_arg,			// 0x28
		cmd,				// 0x2C
		resp[4],			// 0x30 ~ 0x3C
		masked_int_stat,		// 0x40
		raw_int_stat,			// 0x44
		stat,				// 0x48
		fifo_threshold,			// 0x4C
		card_detect,			// 0x50
		write_protect,			// 0x54
		__rsvd0,			// 0x58
		ciu_byte_count,			// 0x5C
		biu_byte_count,			// 0x60
		debounce_count,			// 0x64
		user_id,			// 0x68
		ver_id,				// 0x6C
		__rsvd1,			// 0x70
		uhs,				// 0x74
		rst,				// 0x78
		__rsvd2,			// 0x7C
		bus_mode,			// 0x80
		poll_demand,			// 0x84
		desc_list_base_addr,		// 0x88
		dmac_stat,			// 0x8C
		dmac_int_enb,			// 0x90
		cur_host_desc_addr,		// 0x94
		cur_buf_desc_addr,		// 0x98
		__rsvd3[(0x100 - 0x9C) / 4],	// 0x9C ~ 0xFC
		card_threshold_ctrl,		// 0x100
		back_end_power,			// 0x104
		__rsvd4,			// 0x108
		emmc_ddr,			// 0x10C
		__rsvd5,			// 0x110
		phase_shift,			// 0x114
		__rsvd6[(0x200 - 0x118) / 4],	// 0x118
		data;				// 0x11C
};

enum nx_sdmmc_cmd_flag {
	nx_sdmmc_cmd_flag_start_cmd		= (1 << 31),
	nx_sdmmc_cmd_flag_use_hold_reg		= (1 << 29),
	nx_sdmmc_cmd_flag_volt_switch		= (1 << 28),
	nx_sdmmc_cmd_flag_boot_mode		= (1 << 27),
	nx_sdmmc_cmd_flag_disable_boot		= (1 << 26),
	nx_sdmmc_cmd_flag_expect_boot_ack	= (1 << 25),
	nx_sdmmc_cmd_flag_enable_boot		= (1 << 24),
	nx_sdmmc_cmd_flag_ccs_expected		= (1 << 23),
	nx_sdmmc_cmd_flag_read_ceata_device	= (1 << 22),
	nx_sdmmc_cmd_flag_update_clk_register	= (1 << 21),
	nx_sdmmc_cmd_flag_send_initialization	= (1 << 15),
	nx_sdmmc_cmd_flag_stop_abort_cmd	= (1 << 14),
	nx_sdmmc_cmd_flag_wait_prev_data	= (1 << 13),
	nx_sdmmc_cmd_flag_send_auto_stop	= (1 << 12),
	nx_sdmmc_cmd_flag_stream_transfer_mode	= (1 << 11),
	nx_sdmmc_cmd_flag_write_to_card		= (1 << 10),
	nx_sdmmc_cmd_flag_data_expected		= (1 <<  9),
	nx_sdmmc_cmd_flag_check_resp_crc	= (1 <<  8),
	nx_sdmmc_cmd_flag_resp_long		= (1 <<  7),
	nx_sdmmc_cmd_flag_resp_expected		= (1 <<  6)
};

void nx_set_sdmmc_power(struct nx_sdmmc_regs *, int);
void nx_set_sdmmc_clk_div(struct nx_sdmmc_regs *, int, int);
void nx_set_sdmmc_clk_src(struct nx_sdmmc_regs *, int);
void nx_set_sdmmc_clk_enb(struct nx_sdmmc_regs *, int, int);
void nx_set_sdmmc_timeout(struct nx_sdmmc_regs *, int, int);
void nx_set_sdmmc_card_type(struct nx_sdmmc_regs *, int);
void nx_set_sdmmc_block_size(struct nx_sdmmc_regs *, int);
void nx_set_sdmmc_byte_count(struct nx_sdmmc_regs *, int);
void nx_set_sdmmc_fifo_threshold(struct nx_sdmmc_regs *, int, int);
void nx_reset_sdmmc_all(struct nx_sdmmc_regs *);
void nx_reset_sdmmc_fifo(struct nx_sdmmc_regs *);
void nx_reset_sdcard(struct nx_sdmmc_regs *);

#endif
