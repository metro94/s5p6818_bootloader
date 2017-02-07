/*
 * Copyright (C) 2017
 * Author: metro94 <flattiles@gmail.com>
 *
 * Version: v1.0
 * --- Update time: 02/07/2017
 * --- Description: First build; header of driver for Nexell SoC USB OTG
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

#ifndef __NX_USB_OTG_H__
#define __NX_USB_OTG_H__

#include <common.h>

struct nx_usb_otg_regs {
	struct {
		volatile uint32_t \
			otg_ctrl_stat,			// 0x0
			otg_int,			// 0x4
			ahb_cfg,			// 0x8
			usb_cfg,			// 0xC
			rst_ctrl,			// 0x10
			int_stat,			// 0x14
			int_mask,			// 0x18
			rx_stat_host,			// 0x1C
			rx_stat_device,			// 0x20
			rx_fifo_size,			// 0x24
			tx_non_periodic_fifo_size,	// 0x28
			tx_non_periodic_fifo_stat,	// 0x2C
			__rsvd0[(0x100 - 0x30) / 4],	// 0x30 ~ 0xFC
			tx_periodic_fifo_size[16],	// 0x100 ~ 0x13C
			__rsvd1[(0x400 - 0x140) / 4];	// 0x140 ~ 0x3FC
	} core_global;				// 0x0 ~ 0x3FC
	
	struct {
		volatile uint32_t \
			cfg,				// 0x0
			frame_interval,			// 0x4
			frame_number,			// 0x8
			__rsvd0,			// 0xC
			tx_fifo_status,			// 0x10
			all_int_stat,			// 0x14
			all_int_mask,			// 0x18
			__rsvd1[(0x40 - 0x1C) / 4],	// 0x1C ~ 0x3C
			port_ctrl_stat,			// 0x40
			__rsvd2[(0x100 - 0x44) / 4];	// 0x44 ~ 0xFC
		
		struct {
			volatile uint32_t \
				chars,				// 0x0
				split,				// 0x4
				int_stat,			// 0x8
				int_mask,			// 0xC
				transfer_size,			// 0x10
				dma_addr,			// 0x14
				__rsvd[(0x20 - 0x18) / 4];	// 0x18 ~ 0x1C
		} channel[16];				// 0x100 ~ 0x2FC
		
		volatile uint32_t \
			__rsvd3[(0x400 - 0x300) / 4];	// 0x300 ~ 0x3FC
	} host_mode;				// 0x400 ~ 0x7FC
	
	struct {
		volatile uint32_t \
			cfg,				// 0x0
			ctrl,				// 0x4
			stat,				// 0x8
			__rsvd0,			// 0xC
			in_ep_int_mask,			// 0x10
			out_ep_int_mask,		// 0x14
			all_ep_int_stat,		// 0x18
			all_ep_int_mask,		// 0x1C
			in_token_seq_1,			// 0x20
			in_token_seq_2,			// 0x24
			vbus_discharge_time,		// 0x28
			vbus_pulse_time,		// 0x2C
			in_token_seq_3,			// 0x30
			in_token_seq_4,			// 0x34
			__rsvd1[(0x100 - 0x38) / 4];	// 0x38 ~ 0xFC
			
		struct {
			volatile uint32_t \
				ctrl,				// 0x0
				__rsvd0,			// 0x4
				int_stat,			// 0x8
				__rsvd1,			// 0xC
				transfer_size,			// 0x10
				dma_addr,			// 0x14
				__rsvd2[(0x20 - 0x18) / 4];	// 0x18 ~ 0x1C
		} in_ep[16];				// 0x100 ~ 0x2FC
			
		struct {
			volatile uint32_t \
				ctrl,				// 0x0
				__rsvd0,			// 0x4
				int_stat,			// 0x8
				__rsvd1,			// 0xC
				transfer_size,			// 0x10
				dma_addr,			// 0x14
				__rsvd2[(0x20 - 0x18) / 4];	// 0x18 ~ 0x1C
		} out_ep[16];				// 0x300 ~ 0x4FC
		
		volatile uint32_t \
			__rsvd3[(0x600 - 0x500) / 4];	// 0x500 ~ 0x5FC
	} device_mode;				// 0x800 ~ 0xDFC
	
	struct {
		volatile uint32_t \
			ctrl,				// 0x0
			__rsvd[(0x200 - 0x4) / 4];	// 0x4 ~ 0x1FC
	} power_and_clock_gating;		// 0xE00 ~ 0xFFC
	
	struct {
		volatile uint32_t \
			fifo,				// 0x0
			__rsvd[(0x1000 - 0x4) / 4];	// 0x4 ~ 0xFFC
	} ep_channel[16];			// 0x1000 ~ 0x10FFC
};

#endif
