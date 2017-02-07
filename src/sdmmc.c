/*
 * Copyright (C) 2017
 * Author: metro94 <flattiles@gmail.com>
 *
 * Version: v1.0
 * --- Update time: 02/07/2017
 * --- Description: First build; code for SD/MMC operation
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

#include <sdmmc.h>

static struct nx_sdmmc_regs * sdmmc;

static struct sd_info_table sd_info;

int  init_sdcard(void)
{
	uint32_t ret;
	
	init_nx_sdmmc(PI_SDMMC_PORT);
	
	nx_reset_sdcard(sdmmc);
	
	ret = init_sdcard_cmd();
	
	if (ret) {
		debug("", "\n");
		debug(DEBUG_LEVEL_INFO, "SD Card Information:\n");
		debug(DEBUG_LEVEL_INFO, "Transport Speed = %d\n", sd_info.tran_speed);
		debug(DEBUG_LEVEL_INFO, "Block Size = %d\n", sd_info.block_size);
		debug(DEBUG_LEVEL_INFO, "Capacity = %lld\n", sd_info.capacity);
	}
	
	return ret;
}

void reset_sdmmc(void)
{
	reset_nx_sdmmc(PI_SDMMC_PORT);
}

void init_nx_sdmmc(int port_num)
{
	// Sets default SDMMC device
	sdmmc = nx_sdmmc_port[port_num];
	
	// Resets SDMMC IP
	nx_do_iprst(nx_iprst_block, nx_sdmmc_extended_port[port_num].iprst_id);
	
	// Sets SDMMC clock
	nx_set_clkgen_src(nx_clkgen_table[nx_sdmmc_extended_port[port_num].clkgen_id].clkgen, 0, PI_SDMMC_CLKSRC);
	set_clkgen_freq(nx_clkgen_table[nx_sdmmc_extended_port[port_num].clkgen_id], PI_SDMMC_CLKGEN_FREQ);
	set_clkgen_state(nx_clkgen_table[nx_sdmmc_extended_port[port_num].clkgen_id], 1);
	
	// Sets SDMMC
	nx_set_sdmmc_power(nx_sdmmc_port[port_num], 0);
	nx_sdmmc_port[port_num]->phase_shift =
		(0 << 24) |
		(2 << 16) |
		(0 <<  8) |
		(0 <<  0);
	nx_reset_sdmmc_all(nx_sdmmc_port[port_num]);
	nx_set_sdmmc_power(nx_sdmmc_port[port_num], 1);
	
	set_sdmmc_clk_freq(port_num, 0, PI_SDMMC_LOW_SPEED_FREQ);
	set_sdmmc_clk_freq(port_num, 1, PI_SDMMC_HIGH_SPEED_FREQ);
	nx_set_sdmmc_clk_src(nx_sdmmc_port[port_num], 0);
	nx_set_sdmmc_clk_enb(nx_sdmmc_port[port_num], 1, 0);
	update_sdmmc_clk_reg();
	
	nx_set_sdmmc_timeout(nx_sdmmc_port[port_num], 0xFFFFFF, 0x64);
	nx_set_sdmmc_card_type(nx_sdmmc_port[port_num], 1);
	nx_set_sdmmc_block_size(sdmmc, 512);
	nx_set_sdmmc_fifo_threshold(nx_sdmmc_port[port_num], 8, 7);
	
	nx_sdmmc_port[port_num]->int_mask = 0;
	nx_sdmmc_port[port_num]->raw_int_stat = 0x1FFF;
	
	// Sets pinctrl
	nx_set_pinctrl(nx_sdmmc_extended_port[port_num].pinctrl_conf);
}

void reset_nx_sdmmc(int port_num)
{
	nx_reset_sdcard(sdmmc);
	set_clkgen_state(nx_clkgen_table[nx_sdmmc_extended_port[port_num].clkgen_id], 0);
	nx_assert_iprst(nx_iprst_block, nx_sdmmc_extended_port[port_num].iprst_id);
}

int  init_sdcard_cmd(void)
{
	uint32_t int_stat;
	uint32_t retry;
	
	// Go Idle
	send_sd_cmd(
		SD_CMD0,
		0,
		nx_sdmmc_cmd_flag_send_initialization	|
		nx_sdmmc_cmd_flag_stop_abort_cmd
	);
	
	// Sends interface condition
	int_stat = send_sd_cmd(
		SD_CMD8,
		0x1aa,
		nx_sdmmc_cmd_flag_check_resp_crc	|
		nx_sdmmc_cmd_flag_wait_prev_data	|
		nx_sdmmc_cmd_flag_resp_expected
	);
	if (int_stat)
		return 0;
	
	/* TODO */
	if (sdmmc->resp[0] != 0x1aa)
		return 0;
	
	// Sends OSR
	retry = 10000;
	while (1) {
		int_stat = send_sd_cmd(
			SD_CMD55,
			0,
			nx_sdmmc_cmd_flag_check_resp_crc	|
			nx_sdmmc_cmd_flag_wait_prev_data	|
			nx_sdmmc_cmd_flag_resp_expected
		);
		if (int_stat)
			return 0;
		
		send_sd_cmd(
			SD_ACMD41,
			(1 << 30) | 0xFF8000,
			nx_sdmmc_cmd_flag_wait_prev_data	|
			nx_sdmmc_cmd_flag_resp_expected
		);
		if (int_stat)
			return 0;
		
		if (sdmmc->resp[0] & (1 << 31))
			break;
		
		if (retry-- == 0) {
			debug(DEBUG_LEVEL_WARN, "Timeout when sending ACMD41\n");
			return 0;
		}
		
		delay_us(1000);
	}
	
	sd_info.high_capacity = (sdmmc->resp[0] & (1 << 30)) ? 1 : 0;
	
	// Sends CID
	int_stat = send_sd_cmd(
		SD_CMD2,
		0,
		nx_sdmmc_cmd_flag_check_resp_crc	|
		nx_sdmmc_cmd_flag_wait_prev_data	|
		nx_sdmmc_cmd_flag_resp_expected		|
		nx_sdmmc_cmd_flag_resp_long
	);
	if (int_stat)
		return 0;
	
	// Sends RCA
	int_stat = send_sd_cmd(
		SD_CMD3,
		(1 << 16),
		nx_sdmmc_cmd_flag_check_resp_crc	|
		nx_sdmmc_cmd_flag_wait_prev_data	|
		nx_sdmmc_cmd_flag_resp_expected
	);
	if (int_stat)
		return 0;
	sd_info.rca = (sdmmc->resp[0] >> 16) & 0xFFFF;
	
	// Sends CSD
	int_stat = send_sd_cmd(
		SD_CMD9,
		sd_info.rca << 16,
		nx_sdmmc_cmd_flag_check_resp_crc	|
		nx_sdmmc_cmd_flag_wait_prev_data	|
		nx_sdmmc_cmd_flag_resp_expected		|
		nx_sdmmc_cmd_flag_resp_long
	);
	if (int_stat)
		return 0;
	
	sd_info.tran_speed = calc_sd_tran_speed(sdmmc->resp[3] & 0x7, (sdmmc->resp[3] >> 3) & 0xF);
	if (sd_info.tran_speed > PI_SDMMC_HIGH_SPEED_FREQ)
		sd_info.tran_speed = PI_SDMMC_HIGH_SPEED_FREQ;
	sd_info.block_size = 1 << ((sdmmc->resp[2] >> 16) & 0xF);
	if (sd_info.high_capacity)
		sd_info.capacity =
			((((sdmmc->resp[2] & 0x3F) << 16) | ((sdmmc->resp[1] >> 16) & 0xFFFF)) + 1) <<
			(8 + 2);
	else 
		sd_info.capacity =
			((((sdmmc->resp[2] & 0x3FF) << 2) | ((sdmmc->resp[1] >> 30) & 0x3)) + 1) <<
			(((sdmmc->resp[1] >> 15) & 0x7) + 2);
	sd_info.capacity *= sd_info.block_size;
	
	// Selects card
	int_stat = send_sd_cmd(
		SD_CMD7,
		sd_info.rca << 16,
		nx_sdmmc_cmd_flag_check_resp_crc	|
		nx_sdmmc_cmd_flag_wait_prev_data	|
		nx_sdmmc_cmd_flag_resp_expected
	);
	if (int_stat)
		return 0;
	
	// Sets bus width to 4-bit
	int_stat = send_sd_cmd(
		SD_CMD55,
		sd_info.rca << 16,
		nx_sdmmc_cmd_flag_check_resp_crc	|
		nx_sdmmc_cmd_flag_wait_prev_data	|
		nx_sdmmc_cmd_flag_resp_expected
	);
	int_stat = send_sd_cmd(
		SD_ACMD6,
		2,
		nx_sdmmc_cmd_flag_check_resp_crc	|
		nx_sdmmc_cmd_flag_wait_prev_data	|
		nx_sdmmc_cmd_flag_resp_expected
	);
	if (int_stat)
		return 0;
	
	// Updates SDMMC settings
	nx_set_sdmmc_card_type(sdmmc, 4);
	nx_set_sdmmc_clk_src(sdmmc, 1);
	update_sdmmc_clk_reg();
		
	int_stat = send_sd_cmd(
		SD_CMD7,
		sd_info.rca << 16,
		nx_sdmmc_cmd_flag_check_resp_crc	|
		nx_sdmmc_cmd_flag_wait_prev_data	|
		nx_sdmmc_cmd_flag_resp_expected
	);
	int_stat = send_sd_cmd(
		SD_CMD16,
		512,
		nx_sdmmc_cmd_flag_check_resp_crc	|
		nx_sdmmc_cmd_flag_wait_prev_data	|
		nx_sdmmc_cmd_flag_resp_expected
	);
	if (int_stat)
		return 0;
		
	return 1;
}

void init_sdcard_detect(void)
{
	nx_set_alive_changable(nx_alive);
	nx_set_alive(
		&nx_alive->gpio_pad_out_enb,
		nx_get_alive(&nx_alive->gpio_pad_out_enb) & ~(1 << 1)
	);
	nx_set_alive(
		&nx_alive->gpio_pad_pull_up,
		nx_get_alive(&nx_alive->gpio_pad_pull_up) |  (1 << 1)
	);
	nx_set_alive_unchangable(nx_alive);
}

int  is_sdcard_detected(void)
{
	return (nx_alive->gpio_input_value_read & (1 << 1)) ? 0 : 1;
}

void set_sdmmc_clk_freq(int port_num, int clk_src, int target_freq)
{
	nx_set_sdmmc_clk_div(
		nx_sdmmc_port[port_num],
		clk_src,
		round((double)get_clkgen_freq(nx_clkgen_table[nx_sdmmc_extended_port[port_num].clkgen_id]) / target_freq)
	);
}

void update_sdmmc_clk_reg(void)
{
	sdmmc->cmd =
		nx_sdmmc_cmd_flag_start_cmd		|
		nx_sdmmc_cmd_flag_update_clk_register;
}

uint32_t send_sd_cmd(enum sd_command cmd, uint32_t arg, uint32_t flag)
{
//	debug(DEBUG_LEVEL_INFO, "CMD = %02d, Argument = %08x, Flag = %08x\n", cmd, arg, flag);
	
	sdmmc->raw_int_stat = 0x1FFF;
	
	// Sends command
	do {
		sdmmc->raw_int_stat = (1 << 12);	// HLE
		sdmmc->cmd_arg = arg;
		sdmmc->cmd = flag | cmd | nx_sdmmc_cmd_flag_use_hold_reg | nx_sdmmc_cmd_flag_start_cmd;
		while (sdmmc->cmd & nx_sdmmc_cmd_flag_start_cmd);
	} while (sdmmc->raw_int_stat & (1 << 12));	// HLE
	
	// Checks if command is done
	while (!(sdmmc->raw_int_stat & (1 << 2)));
	sdmmc->raw_int_stat = (1 << 2) | (1 << 14);
	
	return sdmmc->raw_int_stat;
}

int  calc_sd_tran_speed(int fbase, int mult)
{
	static int const __sd_tran_speed_fbase[8] = {
		1,
		10,
		100,
		1000,
		0,
		0,
		0,
		0
	};
	
	static int const __sd_tran_speed_mult[16] = {
		0,
		100000,
		120000,
		130000,
		150000,
		200000,
		250000,
		300000,
		350000,
		400000,
		450000,
		500000,
		550000,
		600000,
		700000,
		800000
	};
	
	return __sd_tran_speed_fbase[fbase] * __sd_tran_speed_mult[mult];
}

void read_sd_block(void *buf, uint32_t block_base, uint32_t block_cnt)
{
	int size;
	int len;
	
	uint32_t *p = buf;
	
	// Resets FIFO
	nx_reset_sdmmc_fifo(sdmmc);
	
	size = block_cnt * 512 / 4;
	nx_set_sdmmc_byte_count(sdmmc, size * 4);
	
	// Sends request
	if (block_cnt == 1) {
		send_sd_cmd(
			SD_CMD17,
			block_base,
			nx_sdmmc_cmd_flag_check_resp_crc	|
			nx_sdmmc_cmd_flag_wait_prev_data	|
			nx_sdmmc_cmd_flag_data_expected		|
			nx_sdmmc_cmd_flag_resp_expected
		);
	} else {
		send_sd_cmd(
			SD_CMD18,
			block_base,
			nx_sdmmc_cmd_flag_check_resp_crc	|
			nx_sdmmc_cmd_flag_wait_prev_data	|
			nx_sdmmc_cmd_flag_data_expected		|
			nx_sdmmc_cmd_flag_resp_expected
		);
	}
	
	// Receives data
	while (size > 0) {
		while (!(sdmmc->raw_int_stat & (1 << 5)));
		sdmmc->raw_int_stat = (1 << 5);
		len = (sdmmc->stat >> 17) & 0x1FFF;
		size -= len;
		while (len--)
			*p++ = sdmmc->data;
	}
	
	if (block_cnt > 1) {
		send_sd_cmd(
			SD_CMD12,
			0,
			nx_sdmmc_cmd_flag_check_resp_crc	|
			nx_sdmmc_cmd_flag_wait_prev_data	|
			nx_sdmmc_cmd_flag_resp_expected
		);
	}
	
	while (sdmmc->stat & (1 << 10));
}
