/*
 * Copyright (C) 2017
 * Author: metro94 <flattiles@gmail.com>
 *
 * Version: v1.0
 * --- Update time: 02/07/2017
 * --- Description: First build; code of driver for Nexell SoC SD/MMC
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

#include <nx_sdmmc.h>

inline void nx_set_sdmmc_power(struct nx_sdmmc_regs *sdmmc, int enb)
{
	sdmmc->power_enb = enb ? 1 : 0;
}

inline void nx_set_sdmmc_clk_div(struct nx_sdmmc_regs *sdmmc, int clk_src, int divisor)
{
	sdmmc->clk_div = (sdmmc->clk_div & ~(0xFF << (clk_src * 8))) | (((divisor + 1) / 2) << (clk_src * 8));
}

inline void nx_set_sdmmc_clk_src(struct nx_sdmmc_regs *sdmmc, int clk_src)
{
	sdmmc->clk_src = clk_src;
}

inline void nx_set_sdmmc_clk_enb(struct nx_sdmmc_regs *sdmmc, int clk_enb, int low_power)
{
	sdmmc->clk_enb = ((clk_enb ? 1 : 0) << 0) | ((low_power ? 1 : 0) << 16);
}

inline void nx_set_sdmmc_timeout(struct nx_sdmmc_regs *sdmmc, int data_timeout, int resp_timeout)
{
	sdmmc->timeout = (data_timeout << 8) | (resp_timeout << 0);
}

inline void nx_set_sdmmc_card_type(struct nx_sdmmc_regs *sdmmc, int bus_width)
{
	if (bus_width == 4)
		sdmmc->card_type = 1;
	else	// 1-bit bus default
		sdmmc->card_type = 0;
}

inline void nx_set_sdmmc_block_size(struct nx_sdmmc_regs *sdmmc, int block_size)
{
	sdmmc->block_size = block_size;
}

inline void nx_set_sdmmc_byte_count(struct nx_sdmmc_regs *sdmmc, int byte_count)
{
	sdmmc->byte_count = byte_count;
}

inline void nx_set_sdmmc_fifo_threshold(struct nx_sdmmc_regs *sdmmc, int tx_threshold, int rx_threshold)
{
	sdmmc->fifo_threshold = (tx_threshold << 0) | (rx_threshold << 16);
}

inline void nx_reset_sdmmc_all(struct nx_sdmmc_regs *sdmmc)
{
	sdmmc->ctrl =
		(1 << 2) |	// DMA Reset
		(1 << 1) |	// FIFO Reset
		(1 << 0);	// Controller Reset
		
	while (sdmmc->ctrl & ((1 << 2) | (1 << 1) | (1 << 0)));
}

inline void nx_reset_sdmmc_fifo(struct nx_sdmmc_regs *sdmmc)
{
	sdmmc->ctrl = (1 << 1);
		
	while (sdmmc->ctrl & (1 << 1));
}

inline void nx_reset_sdcard(struct nx_sdmmc_regs *sdmmc)
{
	sdmmc->rst = 0;
	sdmmc->rst = 1;
}
