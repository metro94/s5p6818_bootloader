/*
 * Copyright (C) 2017
 * Author: metro94 <flattiles@gmail.com>
 *
 * Version: v1.0
 * --- Update time: 02/07/2017
 * --- Description: First build; code of driver for Nexell SoC Serial
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

#include <nx_serial.h>

inline int  nx_get_serial_br_div(struct nx_serial_regs * const nx_serial)
{
	return nx_serial->br_div + 1;
}

inline int  nx_get_serial_frac_val(struct nx_serial_regs * const nx_serial)
{
	return nx_serial->frac_val;
}

inline int  nx_get_serial_tx_fifo_count(struct nx_serial_regs * const nx_serial)
{
	return (nx_serial->f_stat >> 16) & 0x1FF;
}

inline int  nx_get_serial_rx_fifo_count(struct nx_serial_regs * const nx_serial)
{
	return (nx_serial->f_stat >>  0) & 0x1FF;
}

inline void nx_reset_serial_fifo(struct nx_serial_regs * const nx_serial)
{
	nx_serial->f_con |= (1 << 2) | (1 << 1);
	while (nx_serial->f_con & ((1 << 2) | (1 << 1)));
}

inline void nx_set_serial_parity_mode(struct nx_serial_regs * const nx_serial, int parity_mode)
{
	nx_serial->l_con = (nx_serial->l_con		\
				& ~(0x7 << 3))		\
				| (parity_mode << 3);
}

inline void nx_set_serial_stop_bit(struct nx_serial_regs * const nx_serial, int stop_bit)
{
	if (stop_bit == 0)
		nx_serial->l_con &= ~(1 << 2);
	else
		nx_serial->l_con |=  (1 << 2);
}

inline void nx_set_serial_data_len(struct nx_serial_regs * const nx_serial, int data_len)
{
	nx_serial->l_con = (nx_serial->l_con		\
				& ~(0x3 << 0))		\
				| (data_len << 0);
}

inline void nx_set_serial_tx_int_type(struct nx_serial_regs * const nx_serial, int int_type)
{
	if (int_type == 0)
		nx_serial->con &= ~(1 << 9);
	else
		nx_serial->con |=  (1 << 9);
}

inline void nx_set_serial_rx_int_type(struct nx_serial_regs * const nx_serial, int int_type)
{
	if (int_type == 0)
		nx_serial->con &= ~(1 << 8);
	else
		nx_serial->con |=  (1 << 8);
}

inline void nx_set_serial_tx_mode(struct nx_serial_regs * const nx_serial, int mode)
{
	nx_serial->con = (nx_serial->con	\
				& ~(0x3 << 2))	\
				| (mode << 2);
}

inline void nx_set_serial_rx_mode(struct nx_serial_regs * const nx_serial, int mode)
{
	nx_serial->con = (nx_serial->con	\
				& ~(0x3 << 0))	\
				| (mode << 0);
}

inline void nx_set_serial_fifo(struct nx_serial_regs * const nx_serial, int fifo_enb)
{
	if (fifo_enb == 0)
		nx_serial->f_con &= ~(1 << 0);
	else
		nx_serial->f_con |=  (1 << 0);
}

inline void nx_set_serial_br_div(struct nx_serial_regs * const nx_serial, int br_div)
{
	nx_serial->br_div = br_div - 1;
}

inline void nx_set_serial_frac_val(struct nx_serial_regs * const nx_serial, int frac_val)
{
	nx_serial->frac_val = frac_val;
}

inline void nx_set_tx_buf(struct nx_serial_regs * const nx_serial, uint8_t data)
{
	nx_serial->tx_buf = data;
}

inline uint8_t nx_get_rx_buf(struct nx_serial_regs * const nx_serial)
{
	return (uint8_t)nx_serial->rx_buf;
}
