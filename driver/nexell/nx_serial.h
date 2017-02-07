/*
 * Copyright (C) 2017
 * Author: metro94 <flattiles@gmail.com>
 *
 * Version: v1.0
 * --- Update time: 02/07/2017
 * --- Description: First build; header of driver for Nexell SoC Serial
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

#ifndef __NX_SERIAL_H__
#define __NX_SERIAL_H__

#include <common.h>

struct nx_serial_regs {
	volatile uint32_t \
		l_con,		// 0x0
		con,		// 0x4
		f_con,		// 0x8
		m_con, 		// 0xC
		tr_stat,	// 0x10
		er_stat,	// 0x14
		f_stat,		// 0x18
		m_stat,		// 0x1C
		tx_buf,		// 0x20
		rx_buf,		// 0x24
		br_div,		// 0x28
		frac_val,	// 0x2C
		int_p,		// 0x30
		int_s,		// 0x34
		int_m;		// 0x38
};

int  nx_get_serial_br_div(struct nx_serial_regs * const);
int  nx_get_serial_frac_val(struct nx_serial_regs * const);
int  nx_get_serial_tx_fifo_count(struct nx_serial_regs * const);
int  nx_get_serial_rx_fifo_count(struct nx_serial_regs * const);
void nx_reset_serial_fifo(struct nx_serial_regs * const);
void nx_set_serial_parity_mode(struct nx_serial_regs * const, int);
void nx_set_serial_stop_bit(struct nx_serial_regs * const, int);
void nx_set_serial_data_len(struct nx_serial_regs * const, int);
void nx_set_serial_tx_int_type(struct nx_serial_regs * const, int);
void nx_set_serial_rx_int_type(struct nx_serial_regs * const, int);
void nx_set_serial_tx_mode(struct nx_serial_regs * const, int);
void nx_set_serial_rx_mode(struct nx_serial_regs * const, int);
void nx_set_serial_fifo(struct nx_serial_regs * const, int);
void nx_set_serial_br_div(struct nx_serial_regs * const, int);
void nx_set_serial_frac_val(struct nx_serial_regs * const, int);

void nx_set_tx_buf(struct nx_serial_regs * const, uint8_t);
uint8_t nx_get_rx_buf(struct nx_serial_regs * const);

#endif
