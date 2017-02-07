/*
 * Copyright (C) 2017
 * Author: metro94 <flattiles@gmail.com>
 *
 * Version: v1.0
 * --- Update time: 02/07/2017
 * --- Description: First build; code for Serial operation
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

#include <serial.h>

void init_serial(void)
{
	init_nx_serial(PI_DEBUG_UART_PORT);
	register_putchar_used_in_printf(putchar_serial);

	debug(DEBUG_LEVEL_INFO, "Debug UART is ready\n");
}

void init_nx_serial(int port_num)
{
	int divisor;
	
	// Resets serial IP
	nx_do_iprst(nx_iprst_block, nx_serial_extended_port[port_num].iprst_id);
	
	// Sets serial clock
	nx_set_clkgen_src(nx_clkgen_table[nx_serial_extended_port[port_num].clkgen_id].clkgen, 0, PI_DEBUG_UART_CLKSRC);
	set_clkgen_freq(nx_clkgen_table[nx_serial_extended_port[port_num].clkgen_id], PI_DEBUG_UART_CLKGEN_FREQ);
	set_clkgen_state(nx_clkgen_table[nx_serial_extended_port[port_num].clkgen_id], 1);
	
	// Sets serial
	nx_set_serial_tx_int_type(nx_serial_port[port_num], 1);
	nx_set_serial_rx_int_type(nx_serial_port[port_num], 1);
	nx_set_serial_parity_mode(nx_serial_port[port_num], 0);
	nx_set_serial_stop_bit(nx_serial_port[port_num], 0);
	nx_set_serial_data_len(nx_serial_port[port_num], 3);
	nx_set_serial_tx_mode(nx_serial_port[port_num], 1);
	nx_set_serial_rx_mode(nx_serial_port[port_num], 1);
	divisor = round((double)get_clkgen_freq(nx_clkgen_table[nx_serial_extended_port[port_num].clkgen_id]) / PI_DEBUG_UART_BAUDRATE);
	nx_set_serial_br_div(nx_serial_port[port_num], divisor / 16);
	nx_set_serial_frac_val(nx_serial_port[port_num], divisor % 16);
	nx_reset_serial_fifo(nx_serial_port[port_num]);
	nx_set_serial_fifo(nx_serial_port[port_num], 1);
	
	// Sets pinctrl
	nx_set_pinctrl(nx_serial_extended_port[port_num].pinctrl_conf);
}

inline int get_serial_tx_fifo_count(void)
{
	return nx_get_serial_tx_fifo_count(nx_serial_port[PI_DEBUG_UART_PORT]);
}

inline int get_serial_rx_fifo_count(void)
{
	return nx_get_serial_rx_fifo_count(nx_serial_port[PI_DEBUG_UART_PORT]);
}

void wait_serial_tx_done(void)
{
	while (get_serial_tx_fifo_count() > 0);
}

inline int getchar_serial(void)
{
	while (nx_get_serial_rx_fifo_count(nx_serial_port[PI_DEBUG_UART_PORT]) == 0);
	return nx_get_rx_buf(nx_serial_port[PI_DEBUG_UART_PORT]);
}

inline int putchar_serial(int data)
{
	while (nx_get_serial_tx_fifo_count(nx_serial_port[PI_DEBUG_UART_PORT]) >= 0x100);
	nx_set_tx_buf(nx_serial_port[PI_DEBUG_UART_PORT], (uint8_t)data);
	return (uint8_t)data;
}
