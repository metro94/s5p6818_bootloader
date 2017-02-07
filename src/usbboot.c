/*
 * Copyright (C) 2017
 * Author: metro94 <flattiles@gmail.com>
 *
 * Version: v1.0
 * --- Update time: 02/07/2017
 * --- Description: First build; code for USB boot
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

#include <usbboot.h>

static struct usb_boot_info_table usb_boot_info;

void (*do_usb_boot(void))(void)
{
	void (*next_stage_addr)(void) = NULL;
	static int usb_boot_attempt_times __attribute__ ((unused)) = 0;
	
	debug("", "\n");
	debug(DEBUG_LEVEL_INFO, "Trying to boot from USB OTG %d times\n", ++usb_boot_attempt_times);
	
	if (!usb_boot_info.initialized) {
		init_usb_otg_phy_and_link();
		usb_boot_info.initialized = 1;
	}
	
	usb_boot_info.loading = 1;
	usb_boot_info.success = 0;
	usb_boot_info.nsih_received = 0;
	usb_boot_info.ep0_stat = USB_EP_STAT_INIT;
	usb_boot_info.cur_conf = 0;
	usb_boot_info.cur_if = 0;
	usb_boot_info.cur_settings = 0;
	
	while (usb_boot_info.loading)
		if (nx_usb_otg->core_global.int_stat & USB_INT_ALL) {
			handle_usb_int();
		}

	if (usb_boot_info.success) {
		reset_usb_otg_phy_and_link();
		next_stage_addr = (void (*)(void))(uint64_t)usb_boot_info.launch_addr;
		printf("Loading data successfully from USB OTG\n");
		printf("Load Address = %#010x, Load Size = %d\n", usb_boot_info.load_addr, usb_boot_info.load_size);
	} else {
		debug(DEBUG_LEVEL_WARN, "USB OTG boot failed.\n");
	}
	
	return next_stage_addr;
}

void init_usb_otg_phy_and_link(void)
{
	nx_do_iprst(nx_iprst_block, NX_IPRST_ID_USB_OTG);	// Releases OTG common reset
		
	nx_tieoff[12] &= ~(0x3 << 0);	// Programs scale mode to read mode
	nx_tieoff[14] |=  (0x3 << 8);	// Sets 16-bit word interface and enables word interface selection
	nx_tieoff[13] = 0xA3006C00;	// Selects VBUS as Digital USBVBUS
	nx_tieoff[13] = 0xA3006C80;	// Asserts POR of PHY
	delay_us(40);
	
	// Releases UTMI reset
	nx_tieoff[13] = 0xA3006C88;
	delay_us(1);
	
	// Releases AHB reset
	nx_tieoff[13] = 0xA3006C8C;
	delay_us(1);
	
	// USB core soft reset
	nx_usb_otg->core_global.rst_ctrl = (1 << 0);
	while (!(nx_usb_otg->core_global.rst_ctrl & (1 << 31)));
	
	nx_usb_otg->core_global.ahb_cfg = 
		(0 << 8) |	// Interrupt indicates that the periodic Tx FIFO is half empty
		(0 << 7) |	// Interrupt indicates that the non-periodic Tx FIFO is half empty
		(0 << 5) |	// Core operates in Slave Mode
		(0 << 1) |	// Burst Length is single
		(1 << 0);	// Unmasks the interrupt assertion
		
	nx_usb_otg->core_global.usb_cfg =
		(0 << 15) |	// PHY operates on 480 MHz Internal PLL Clock
		(1 << 14) |	// Non-periodic Tx FIFO Rewind enabled
		(5 << 10) |	// Turnaround time
		(0 <<  9) |	// HNP capability is not enabled
		(0 <<  8) |	// SRP capability is not enabled
		(0 <<  7) |	// ULPI DDR selection
		(0 <<  6) |	// High speed UTMI+
		(0 <<  4) |	// UTMI+
		(1 <<  3) |	// PHY uses 16-bit word interface
		(7 <<  0);	// HS/FS timeout calibration
		
	if ((nx_usb_otg->core_global.int_stat & (1 << 0)) == (0 << 0)) {	// Device Mode
		nx_usb_otg->device_mode.ctrl |=  (1 << 1);	// Generates soft disconnect
		delay_us(10);
		nx_usb_otg->device_mode.ctrl &= ~(1 << 1);	// Normal operation
		nx_usb_otg->device_mode.cfg = (1 << 18) | (usb_boot_info.speed << 0);
		nx_usb_otg->core_global.int_mask = USB_INT_ALL;
		
		debug(DEBUG_LEVEL_INFO, "USB OTG is ready\n");
	} else {
		debug(DEBUG_LEVEL_ERR, "Cannot initialize USB OTG\n");
		while (1);
	}
}

void reset_usb_otg_phy_and_link(void)
{
	nx_usb_otg->core_global.rst_ctrl = (1 << 0);
	while (!(nx_usb_otg->core_global.rst_ctrl & (1 << 31)));
	
	nx_tieoff[13] &= ~(1 << 3);
	nx_tieoff[13] &= ~(1 << 2);
	nx_tieoff[13] |= (1 << 8) | (1 << 7);
	
	nx_assert_iprst(nx_iprst_block, NX_IPRST_ID_USB_OTG);
}

void handle_usb_int(void)
{
	uint32_t int_stat;
	
	int_stat = nx_usb_otg->core_global.int_stat;
	
	if (int_stat & USB_INT_RESET) {
		reset_usb_connection();
	}
	
	if (int_stat & USB_INT_ENUM_DONE) {
		set_usb_connection();
	}
	
	if (int_stat & USB_INT_WAKEUP) {
	}
	
	if (int_stat & USB_INT_SUSPEND) {
	}
	
	if (int_stat & USB_INT_RX_FIFO_NOT_EMPTY) {
		nx_usb_otg->core_global.int_mask = USB_INT_ALL & ~USB_INT_RX_FIFO_NOT_EMPTY;
		receive_packet_via_usb();
		nx_usb_otg->core_global.int_mask = USB_INT_ALL;
	}
	
	if (int_stat & (USB_INT_IN_EP | USB_INT_OUT_EP)) {
		transfer_via_usb();
	}
	
	// Clear all interrupts
	nx_usb_otg->core_global.int_stat = int_stat;
}

void handle_usb_ep0_int(void)
{
	struct usb_request req;
	uint32_t *pData;
	static uint8_t buf_desc[32] __attribute__ ((aligned(4)));
	
	if (usb_boot_info.ep0_stat == USB_EP_STAT_INIT) {
		pData = (uint32_t *)&req;
		pData[0] = nx_usb_otg->ep_channel[USB_BOOT_CONTROL_EP].fifo;
		pData[1] = nx_usb_otg->ep_channel[USB_BOOT_CONTROL_EP].fifo;
		
		
		switch (req.bRequest) {
		case USB_REQUEST_GET_STATUS:
			usb_boot_info.ep0_stat = USB_EP_STAT_GET_STATUS;
			break;
		case USB_REQUEST_CLEAR_FEATURE:
			break;
		case USB_REQUEST_SET_FEATURE:
			break;
		case USB_REQUEST_SET_ADDRESS:
			nx_usb_otg->device_mode.cfg = (1 << 18) | ((req.wValue & 0xFF) << 4) | (usb_boot_info.speed << 0);
			usb_boot_info.ep0_stat = USB_EP_STAT_INIT;
			break;
		case USB_REQUEST_GET_DESCRIPTOR:
			usb_boot_info.remaining_size = req.wLength;
			switch (req.wValue >> 8) {
			case USB_DESCRIPTOR_TYPE_DEVICE:
				usb_boot_info.cur_desc = (uint32_t *)buf_desc;
				memcpy(buf_desc + 0, usb_boot_info.dev_desc, USB_DEVICE_DESCRIPTOR_SIZE);
				usb_boot_info.cur_fifo_size = usb_boot_info.dev_desc->bMaxPacketSize0;
				if (usb_boot_info.remaining_size > USB_DEVICE_DESCRIPTOR_SIZE)
					usb_boot_info.remaining_size = USB_DEVICE_DESCRIPTOR_SIZE;
				usb_boot_info.ep0_stat = USB_EP_STAT_GET_DESCRIPTOR;
				break;
			case USB_DESCRIPTOR_TYPE_CONFIGURATION:
				usb_boot_info.cur_desc = (uint32_t *)buf_desc;
				memcpy(
					buf_desc + 0,
					usb_boot_info.conf_desc,
					USB_CONFIGURATION_DESCRIPTOR_SIZE
				);
				memcpy(
					buf_desc + USB_CONFIGURATION_DESCRIPTOR_SIZE,
					usb_boot_info.if_desc,
					USB_INTERFACE_DESCRIPTOR_SIZE
				);
				memcpy(
					buf_desc + USB_CONFIGURATION_DESCRIPTOR_SIZE +
						USB_INTERFACE_DESCRIPTOR_SIZE,
					usb_boot_info.ep1_desc,
					USB_ENDPOINT_DESCRIPTOR_SIZE
				);
				memcpy(
					buf_desc + USB_CONFIGURATION_DESCRIPTOR_SIZE +
						USB_INTERFACE_DESCRIPTOR_SIZE +
						USB_ENDPOINT_DESCRIPTOR_SIZE,
					usb_boot_info.ep2_desc,
					USB_ENDPOINT_DESCRIPTOR_SIZE
				);
				usb_boot_info.cur_fifo_size = usb_boot_info.dev_desc->bMaxPacketSize0;
				if (usb_boot_info.remaining_size > USB_CONFIGURATION_DESCRIPTOR_SIZE +
					USB_INTERFACE_DESCRIPTOR_SIZE +
					USB_ENDPOINT_DESCRIPTOR_SIZE * 2)
					usb_boot_info.remaining_size =
						USB_CONFIGURATION_DESCRIPTOR_SIZE +
						USB_INTERFACE_DESCRIPTOR_SIZE +
						USB_ENDPOINT_DESCRIPTOR_SIZE * 2;
				usb_boot_info.ep0_stat = USB_EP_STAT_GET_DESCRIPTOR;
				break;
			default:
				// STALL Handshake
				nx_usb_otg->device_mode.in_ep[USB_BOOT_CONTROL_EP].ctrl |= (1 << 21);
				break;
			}
			break;
		case USB_REQUEST_SET_DESCRIPTOR:
			break;
		case USB_REQUEST_GET_CONFIGURATION:
			nx_usb_otg->device_mode.in_ep[USB_BOOT_CONTROL_EP].ctrl =
				(                  1 << 31) |	// Endpoint Enable
				(                  1 << 26) |	// Clear NAK
				(USB_BOOT_CONTROL_EP << 11) |	// Next Point
				(                  3 <<  0);	// Maximum Packet Size = 8 bytes
			nx_usb_otg->device_mode.in_ep[USB_BOOT_CONTROL_EP].transfer_size =
				(1 << 19) |	// Packet Count
				(1 <<  0);	// Transfer Size
			nx_usb_otg->ep_channel[USB_BOOT_CONTROL_EP].fifo = usb_boot_info.cur_conf;
			usb_boot_info.ep0_stat = USB_EP_STAT_INIT;
			break;
		case USB_REQUEST_SET_CONFIGURATION:
			usb_boot_info.cur_conf = req.wValue;
			usb_boot_info.ep0_stat = USB_EP_STAT_INIT;
			break;
		case USB_REQUEST_GET_INTERFACE:
			usb_boot_info.ep0_stat = USB_EP_STAT_GET_INTERFACE;
			break;
		case USB_REQUEST_SET_INTERFACE:
			usb_boot_info.cur_if = req.wValue;
			usb_boot_info.cur_settings = req.wValue;
			usb_boot_info.ep0_stat = USB_EP_STAT_INIT;
			break;
		case SYNCH_FRAME:
			usb_boot_info.ep0_stat = USB_EP_STAT_INIT;
			break;
		default:
			break;
		}
	}
	
	nx_usb_otg->device_mode.in_ep[USB_BOOT_CONTROL_EP].transfer_size =
		(1 << 19) |	// Packet Count
		(usb_boot_info.dev_desc->bMaxPacketSize0 << 0);	// Transfer Size
	nx_usb_otg->device_mode.in_ep[USB_BOOT_CONTROL_EP].ctrl =
		(                  1 << 26) |	// Clear NAK
		(USB_BOOT_CONTROL_EP << 11) |	// Next Point
		(                  0 <<  0);	// Maximum Packet Size = 64 bytes
}

void reset_usb_connection(void)
{
	int ep_index;
	
	// Sets NAK
	for (ep_index = 0; ep_index < 16; ++ep_index)
		nx_usb_otg->device_mode.out_ep[ep_index].ctrl |= (1 << 27);
	
	usb_boot_info.ep0_stat = USB_EP_STAT_INIT;
	nx_usb_otg->device_mode.all_ep_int_mask =
		(1 << (USB_BOOT_CONTROL_EP + 16)) |
		(1 << (USB_BOOT_OUT_EP + 16))     |
		(1 << (USB_BOOT_CONTROL_EP + 0))  |
		(1 << (USB_BOOT_IN_EP + 0));
	nx_usb_otg->device_mode.in_ep_int_mask =
		(1 << 4) |	// IN Token received with TxFIFO Empty
		(1 << 3) |	// Timeout Condition
		(1 << 2) |	// AHB Error
		(1 << 0);	// Transfer Completed
	nx_usb_otg->device_mode.out_ep_int_mask =
		(1 << 3) |	// SETUP Phase Done
		(1 << 2) |	// AHB Error
		(1 << 0);	// Transfer Completed
		
	nx_usb_otg->core_global.rx_fifo_size = USB_BOOT_FIFO_SIZE;
	nx_usb_otg->core_global.tx_non_periodic_fifo_size =
		(USB_BOOT_FIFO_SIZE << 16) |
		(USB_BOOT_FIFO_SIZE <<  0);

	// Enables Endpoint and Clears NAK
	for (ep_index = 0; ep_index < 16; ++ep_index)
		nx_usb_otg->device_mode.out_ep[ep_index].ctrl |= (1 << 31) | (1 << 26);
	
	// Clears Device Address
	nx_usb_otg->device_mode.cfg &= ~(0x7F << 4);
}

void set_usb_connection(void)
{
	switch ((nx_usb_otg->device_mode.stat >> 1) & 0x3) {
	case USB_ENUMERATED_SPEED_HIGH:
		debug(DEBUG_LEVEL_INFO, "Connected at High Speed\n");
		usb_boot_info.speed     = USB_ENUMERATED_SPEED_HIGH;
		usb_boot_info.dev_desc  = &usb_boot_hs_dev_desc;
		usb_boot_info.conf_desc = &usb_boot_hs_conf_desc;
		usb_boot_info.if_desc   = &usb_boot_hs_if_desc;
		usb_boot_info.ep1_desc  = &usb_boot_hs_ep1_desc;
		usb_boot_info.ep2_desc  = &usb_boot_hs_ep2_desc;
		break;
	case USB_ENUMERATED_SPEED_FULL:
		debug(DEBUG_LEVEL_INFO, "Connected at Full Speed\n");
		usb_boot_info.speed     = USB_ENUMERATED_SPEED_FULL;
		usb_boot_info.dev_desc  = &usb_boot_fs_dev_desc;
		usb_boot_info.conf_desc = &usb_boot_fs_conf_desc;
		usb_boot_info.if_desc   = &usb_boot_fs_if_desc;
		usb_boot_info.ep1_desc  = &usb_boot_fs_ep1_desc;
		usb_boot_info.ep2_desc  = &usb_boot_fs_ep2_desc;
		break;
	default:
		debug(DEBUG_LEVEL_WARN, "Cannot support current speed\n");
		return;
	}
	
	nx_usb_otg->device_mode.in_ep[USB_BOOT_CONTROL_EP].int_stat = 0x3F;
	nx_usb_otg->device_mode.out_ep[USB_BOOT_CONTROL_EP].int_stat = 0x1F;
	nx_usb_otg->device_mode.in_ep[USB_BOOT_IN_EP].int_stat = 0x3F;
	nx_usb_otg->device_mode.out_ep[USB_BOOT_OUT_EP].int_stat = 0x1F;
	
	nx_usb_otg->device_mode.in_ep[USB_BOOT_CONTROL_EP].ctrl =
		(                  1 << 26) |	// Clear NAK
		(USB_BOOT_CONTROL_EP << 11) |	// Next Point
		(                  0 <<  0);	// Maximum Packet Size = 64 bytes
	nx_usb_otg->device_mode.out_ep[USB_BOOT_CONTROL_EP].ctrl =
		(1 << 31) |	// Endpoint Enable
		(1 << 26) |	// Clear NAK
		(0 <<  0);	// Maximum Packet Size = 64 bytes
	
	debug(DEBUG_LEVEL_INFO, "VID = %04x, PID = %04x\n", usb_boot_info.dev_desc->idVendor, usb_boot_info.dev_desc->idProduct);
	
	nx_usb_otg->core_global.int_mask = USB_INT_ALL;
	
	
	nx_usb_otg->device_mode.in_ep[USB_BOOT_IN_EP].transfer_size =
		(1 << 19) |	// Packet Count
		(0 <<  0);	// Transfer Size
	nx_usb_otg->device_mode.out_ep[USB_BOOT_OUT_EP].transfer_size =
		(1 << 19) |	// Packet Count
		(usb_boot_info.ep2_desc->wMaxPacketSize << 0);	// Transfer Size
		
	nx_usb_otg->device_mode.in_ep[USB_BOOT_IN_EP].ctrl =
		(0 << 31) |	// Endpoint Disable
		(1 << 26) |	// Clear NAK
		(2 << 18) |	// Bulk
		(1 << 15) |	// USB Active Point
		(usb_boot_info.ep1_desc->wMaxPacketSize << 0);	// Maximum Packet Size = 512 bytes
	nx_usb_otg->device_mode.out_ep[USB_BOOT_OUT_EP].ctrl =
		(                  1 << 31) |	// Endpoint Enable
		(                  1 << 26) |	// Clear NAK
		(                  2 << 18) |	// Bulk
		(                  1 << 15) |	// USB Active Point
		(USB_BOOT_CONTROL_EP << 11) |	// Next Point
		(usb_boot_info.ep2_desc->wMaxPacketSize << 0);	// Maximum Packet Size = 512 bytes
}

void receive_packet_via_usb(void)
{
	uint32_t rx_stat_device;
	uint32_t fifo_count;
	
	rx_stat_device = nx_usb_otg->core_global.rx_stat_device;
	switch ((rx_stat_device >> 17) & 0xF) {
	case USB_RX_STAT_GLOBAL_OUT_NAK:
		break;
	case USB_RX_STAT_OUT_DATA_PACKET_RECEIVED:
		fifo_count = (rx_stat_device >> 4) & 0x7FF;
		if ((rx_stat_device & 0xF) == USB_BOOT_OUT_EP && fifo_count > 0) {
			transfer_via_usb_ep2(fifo_count);
			nx_usb_otg->core_global.int_mask = USB_INT_ALL;
		}
		break;
	case USB_RX_STAT_OUT_TRANSFER_COMPLETED:
		break;
	case USB_RX_STAT_SETUP_TRANSACTION_COMPLETED:
		break;
	case USB_RX_STAT_SETUP_DATA_PACKET_RECEIVED:
		handle_usb_ep0_int();
		break;
	default:
		break;
	}
}

void transfer_via_usb(void)
{
	uint32_t all_ep_int_stat;
	uint32_t epx_int_stat;
	
	all_ep_int_stat = nx_usb_otg->device_mode.all_ep_int_stat;
	
	if (all_ep_int_stat & (1 << USB_BOOT_CONTROL_EP)) {
		epx_int_stat = nx_usb_otg->device_mode.in_ep[USB_BOOT_CONTROL_EP].int_stat;
		if (epx_int_stat & (1 << 4)) {	// IN Token Received When TxFIFO is Empty
			while (((nx_usb_otg->core_global.tx_non_periodic_fifo_stat & 0xFFFF) >> 0) < usb_boot_info.dev_desc->bMaxPacketSize0);
			transfer_via_usb_ep0();
		}
		nx_usb_otg->device_mode.in_ep[USB_BOOT_CONTROL_EP].int_stat = epx_int_stat;
	}
	
	if (all_ep_int_stat & (1 << (USB_BOOT_CONTROL_EP + 16))) {
		epx_int_stat = nx_usb_otg->device_mode.out_ep[USB_BOOT_CONTROL_EP].int_stat;
		nx_usb_otg->device_mode.out_ep[USB_BOOT_CONTROL_EP].transfer_size =
			(1 << 29) |	// Multi Count
			(1 << 19) |	// Packet Count
			(8 <<  0);	// Transfer Size
		nx_usb_otg->device_mode.out_ep[USB_BOOT_CONTROL_EP].ctrl =
			(                  1 << 31) |	// Endpoint Enable
			(                  1 << 26) |	// Clear NAK
			(USB_BOOT_CONTROL_EP << 11) |	// Next Point
			(                  0 <<  0);	// Maximum Packet Size = 64 bytes
		nx_usb_otg->device_mode.out_ep[USB_BOOT_CONTROL_EP].int_stat = epx_int_stat;
	}
	
	if (all_ep_int_stat & (1 << USB_BOOT_IN_EP)) {
		epx_int_stat = nx_usb_otg->device_mode.in_ep[USB_BOOT_IN_EP].int_stat;
		if (epx_int_stat & (1 << 4)) {	// IN Token Received When TxFIFO is Empty
			transfer_via_usb_ep1();
		}
		nx_usb_otg->device_mode.in_ep[USB_BOOT_IN_EP].int_stat = epx_int_stat;
	}
	
	if (all_ep_int_stat & (1 << (USB_BOOT_OUT_EP + 16))) {
		epx_int_stat = nx_usb_otg->device_mode.out_ep[USB_BOOT_OUT_EP].int_stat;
		nx_usb_otg->device_mode.out_ep[USB_BOOT_OUT_EP].int_stat = epx_int_stat;
	}
}

void transfer_via_usb_ep0(void)
{
	switch (usb_boot_info.ep0_stat) {
	case USB_EP_STAT_INIT:
		nx_usb_otg->device_mode.in_ep[USB_BOOT_CONTROL_EP].transfer_size =
			(1 << 19) |	// Packet Count
			(0 <<  0);	// Transfer Size
		nx_usb_otg->device_mode.in_ep[USB_BOOT_CONTROL_EP].ctrl =
			(                  1 << 31) |	// Endpoint Enable
			(                  1 << 26) |	// Clear NAK
			(USB_BOOT_CONTROL_EP << 11) |	// Next Point
			(                  3 <<  0);	// Maximum Packet Size = 8 bytes
		break;
	case USB_EP_STAT_GET_STATUS:
		nx_usb_otg->device_mode.in_ep[USB_BOOT_CONTROL_EP].transfer_size =
			(1 << 19) |	// Packet Count
			(1 <<  0);	// Transfer Size
		nx_usb_otg->device_mode.in_ep[USB_BOOT_CONTROL_EP].ctrl =
			(                  1 << 31) |	// Endpoint Enable
			(                  1 << 26) |	// Clear NAK
			(USB_BOOT_CONTROL_EP << 11) |	// Next Point
			(                  3 <<  0);	// Maximum Packet Size = 8 bytes
		nx_usb_otg->ep_channel[USB_BOOT_CONTROL_EP].fifo = 0;
		usb_boot_info.ep0_stat = USB_EP_STAT_INIT;
		break;
	case USB_EP_STAT_GET_DESCRIPTOR:
		nx_usb_otg->device_mode.in_ep[USB_BOOT_CONTROL_EP].ctrl =
			(                  1 << 31) |	// Endpoint Enable
			(                  1 << 26) |	// Clear NAK
			(USB_BOOT_CONTROL_EP << 11) |	// Next Point
			(                  0 <<  0);	// Maximum Packet Size = 64 bytes
		if (usb_boot_info.cur_fifo_size < usb_boot_info.remaining_size) {
			nx_usb_otg->device_mode.in_ep[USB_BOOT_CONTROL_EP].transfer_size =
				(1 << 19) |	// Packet Count
				(usb_boot_info.cur_fifo_size << 0);	// Transfer Size
			write_fifo_via_usb_ep(USB_BOOT_CONTROL_EP, usb_boot_info.cur_desc, usb_boot_info.cur_fifo_size);
			usb_boot_info.cur_desc += usb_boot_info.cur_fifo_size / 4;
			usb_boot_info.remaining_size -= usb_boot_info.cur_fifo_size;
		} else {
			nx_usb_otg->device_mode.in_ep[USB_BOOT_CONTROL_EP].transfer_size =
				(1 << 19) |	// Packet Count
				(usb_boot_info.remaining_size << 0);	// Transfer Size
			write_fifo_via_usb_ep(USB_BOOT_CONTROL_EP, usb_boot_info.cur_desc, usb_boot_info.remaining_size);
			usb_boot_info.cur_desc += (usb_boot_info.remaining_size + 3) / 4;
			usb_boot_info.remaining_size = 0;
			usb_boot_info.ep0_stat = USB_EP_STAT_INIT;
		}
		break;
	case USB_EP_STAT_GET_CONFIGURATION:
		nx_usb_otg->device_mode.in_ep[USB_BOOT_CONTROL_EP].transfer_size =
			(1 << 19) |	// Packet Count
			(1 <<  0);	// Transfer Size
		nx_usb_otg->device_mode.in_ep[USB_BOOT_CONTROL_EP].ctrl =
			(                  1 << 31) |	// Endpoint Enable
			(                  1 << 26) |	// Clear NAK
			(USB_BOOT_CONTROL_EP << 11) |	// Next Point
			(                  3 <<  0);	// Maximum Packet Size = 8 bytes
		nx_usb_otg->ep_channel[USB_BOOT_CONTROL_EP].fifo = usb_boot_info.cur_conf;
		usb_boot_info.ep0_stat = USB_EP_STAT_INIT;
		break;
	case USB_EP_STAT_GET_INTERFACE:
		nx_usb_otg->device_mode.in_ep[USB_BOOT_CONTROL_EP].transfer_size =
			(1 << 19) |	// Packet Count
			(1 <<  0);	// Transfer Size
		nx_usb_otg->device_mode.in_ep[USB_BOOT_CONTROL_EP].ctrl =
			(                  1 << 31) |	// Endpoint Enable
			(                  1 << 26) |	// Clear NAK
			(USB_BOOT_CONTROL_EP << 11) |	// Next Point
			(                  3 <<  0);	// Maximum Packet Size = 8 bytes
		nx_usb_otg->ep_channel[USB_BOOT_CONTROL_EP].fifo = usb_boot_info.cur_if;
		usb_boot_info.ep0_stat = USB_EP_STAT_INIT;
		break;
	default:
		break;
	}
}

void transfer_via_usb_ep1(void)
{
	// Simply does nothing
}

void transfer_via_usb_ep2(uint32_t fifo_count)
{
	static uint32_t nsih[128];	// 512 bytes
	static uint32_t loaded_size = 0;
	
	if (!usb_boot_info.nsih_received) {
		read_fifo_via_usb_ep(USB_BOOT_OUT_EP, nsih, fifo_count);
		if ((fifo_count & 0x3) != 0x0) {
			nx_usb_otg->device_mode.out_ep[USB_BOOT_OUT_EP].ctrl |= (1 << 21);
			loaded_size = 0;
		} else {
			loaded_size += fifo_count;
		}
		
		if (loaded_size >= 512) {
			debug(DEBUG_LEVEL_INFO, "NSIH Received\n");
			if (nsih[127] == 0x4849534E) {	// ASCII Code of "NSIH" (Little-Endian)
				usb_boot_info.nsih_received = 1;
				usb_boot_info.load_size = nsih[17];
				usb_boot_info.load_addr = nsih[18];
				usb_boot_info.launch_addr = nsih[19];
			} else {
				usb_boot_info.loading = 0;
				usb_boot_info.success = 0;
				nx_usb_otg->device_mode.out_ep[USB_BOOT_OUT_EP].ctrl |= (1 << 21);
			}
			loaded_size = 0;
		}
	} else {
		read_fifo_via_usb_ep(USB_BOOT_OUT_EP, (uint32_t *)(uint64_t)(usb_boot_info.load_addr + loaded_size), fifo_count);
		loaded_size += fifo_count;
		if (loaded_size >= usb_boot_info.load_size) {
			usb_boot_info.loading = 0;
			usb_boot_info.success = 1;
		}
	}
	
	nx_usb_otg->device_mode.out_ep[USB_BOOT_OUT_EP].transfer_size =
		(1 << 19) |	// Packet Count
		(usb_boot_info.ep2_desc->wMaxPacketSize << 0);	// Transfer Size
		
	nx_usb_otg->device_mode.out_ep[USB_BOOT_OUT_EP].ctrl =
		(                  1 << 31) |	// Endpoint Enable
		(                  1 << 26) |	// Clear NAK
		(                  2 << 18) |	// Bulk
		(                  1 << 15) |	// USB Active Point
		(USB_BOOT_CONTROL_EP << 11) |	// Next Point
		(usb_boot_info.ep2_desc->wMaxPacketSize << 0);	// Maximum Packet Size = 512 bytes
}

void read_fifo_via_usb_ep(int ep_channel, uint32_t *buf, int32_t size)
{
	while (size > 0) {
		*buf++ = nx_usb_otg->ep_channel[ep_channel].fifo;
		size -= 4;
	};
}

void write_fifo_via_usb_ep(int ep_channel, uint32_t const *buf, int32_t size)
{
	while (size > 0) {
		nx_usb_otg->ep_channel[ep_channel].fifo = *buf++;
		size -= 4;
	};
}
