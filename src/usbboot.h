/*
 * Copyright (C) 2017
 * Author: metro94 <flattiles@gmail.com>
 *
 * Version: v1.0
 * --- Update time: 02/07/2017
 * --- Description: First build; header for USB boot
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

#ifndef __USBBOOT_H__
#define __USBBOOT_H__

#include <common.h>
#include <usb.h>
#include <std/debug.h>
#include <std/printf.h>
#include <std/string.h>

#include <nexell/nx_tieoff.h>
#include <nexell/nx_iprst.h>
#include <nexell/nx_usb_otg.h>
#include <timer.h>

enum USB_INT_TYPE {
	USB_INT_WAKEUP			= (1 << 31),
	USB_INT_OUT_EP			= (1 << 19),
	USB_INT_IN_EP			= (1 << 18),
	USB_INT_ENUM_DONE		= (1 << 13),
	USB_INT_RESET			= (1 << 12),
	USB_INT_SUSPEND			= (1 << 11),
	USB_INT_RX_FIFO_NOT_EMPTY	= (1 <<  4),
	USB_INT_ALL			=
		USB_INT_WAKEUP | USB_INT_OUT_EP | USB_INT_IN_EP | USB_INT_ENUM_DONE |
		USB_INT_RESET | USB_INT_SUSPEND | USB_INT_RX_FIFO_NOT_EMPTY
};

enum USB_EP_STAT {
	USB_EP_STAT_INIT = 0,
	USB_EP_STAT_GET_STATUS,
	USB_EP_STAT_GET_DESCRIPTOR,
	USB_EP_STAT_GET_CONFIGURATION,
	USB_EP_STAT_GET_INTERFACE
};

enum USB_ENUMERATED_SPEED {
	USB_ENUMERATED_SPEED_HIGH	= 0,
	USB_ENUMERATED_SPEED_FULL	= 1,
	USB_ENUMERATED_SPEED_LOW	= 2
};

enum USB_RX_STAT {
	USB_RX_STAT_GLOBAL_OUT_NAK		= 1,
	USB_RX_STAT_OUT_DATA_PACKET_RECEIVED	= 2,
	USB_RX_STAT_OUT_TRANSFER_COMPLETED	= 3,
	USB_RX_STAT_SETUP_TRANSACTION_COMPLETED	= 4,
	USB_RX_STAT_SETUP_DATA_PACKET_RECEIVED	= 6
};

struct usb_boot_info_table {
	int initialized;
	int loading;
	int success;
	int nsih_received;
	enum USB_EP_STAT ep0_stat;
	enum USB_ENUMERATED_SPEED speed;
	struct usb_device_descriptor const *dev_desc;
	struct usb_configuration_descriptor const *conf_desc;
	struct usb_interface_descriptor const *if_desc;
	struct usb_endpoint_descriptor const *ep1_desc;
	struct usb_endpoint_descriptor const *ep2_desc;
	uint32_t const *cur_desc;
	uint32_t cur_conf;
	uint32_t cur_if;
	uint32_t cur_settings;
	uint32_t cur_fifo_size;
	uint32_t remaining_size;
	uint32_t load_addr;
	uint32_t load_size;
	uint32_t launch_addr;
};

static struct usb_device_descriptor const usb_boot_fs_dev_desc = {
	.bLength		= USB_DEVICE_DESCRIPTOR_SIZE,
	.bDescriptorType	= USB_DESCRIPTOR_TYPE_DEVICE,
	.bcdUSB			= 0x0110,
	.bDeviceClass		= 0xFF,
	.bDeviceSubClass	= 0xFF,
	.bDeviceProtocol	= 0xFF,
	.bMaxPacketSize0	= 64,
	.idVendor		= 0x04E8,
	.idProduct		= 0x1234,
	.bcdDevice		= 0x0000,
	.iManufacturer		= 0,
	.iProduct		= 0,
	.iSerialNumber		= 0,
	.bNumConfigurations	= 1
};

static struct usb_device_descriptor const usb_boot_hs_dev_desc = {
	.bLength		= USB_DEVICE_DESCRIPTOR_SIZE,
	.bDescriptorType	= USB_DESCRIPTOR_TYPE_DEVICE,
	.bcdUSB			= 0x0200,
	.bDeviceClass		= 0xFF,
	.bDeviceSubClass	= 0xFF,
	.bDeviceProtocol	= 0xFF,
	.bMaxPacketSize0	= 64,
	.idVendor		= 0x04E8,
	.idProduct		= 0x1234,
	.bcdDevice		= 0x0000,
	.iManufacturer		= 0,
	.iProduct		= 0,
	.iSerialNumber		= 0,
	.bNumConfigurations	= 1
};

static struct usb_configuration_descriptor const usb_boot_fs_conf_desc = {
	.bLength		= USB_CONFIGURATION_DESCRIPTOR_SIZE,
	.bDescriptorType	= USB_DESCRIPTOR_TYPE_CONFIGURATION,
	.wTotalLength		= 32,
	.bNumInterface		= 1,
	.bConfigurationValue	= 1,
	.iConfiguration		= 0,
	.bmAttributes		= 0xC0,
	.MaxPower		= 25
};

static struct usb_configuration_descriptor const usb_boot_hs_conf_desc = {
	.bLength		= USB_CONFIGURATION_DESCRIPTOR_SIZE,
	.bDescriptorType	= USB_DESCRIPTOR_TYPE_CONFIGURATION,
	.wTotalLength		= 32,
	.bNumInterface		= 1,
	.bConfigurationValue	= 1,
	.iConfiguration		= 0,
	.bmAttributes		= 0xC0,
	.MaxPower		= 25
};

static struct usb_interface_descriptor const usb_boot_fs_if_desc = {
	.bLength		= USB_INTERFACE_DESCRIPTOR_SIZE,
	.bDescriptorType	= USB_DESCRIPTOR_TYPE_INTERFACE,
	.bInterfaceNumber	= 0,
	.bAlternateSetting	= 0,
	.bNumEndpoints		= 2,
	.bInterfaceClass	= 0xFF,
	.bInterfaceSubClass	= 0xFF,
	.bInterfaceProtocol	= 0xFF,
	.iInterface		= 0
};

static struct usb_interface_descriptor const usb_boot_hs_if_desc = {
	.bLength		= USB_INTERFACE_DESCRIPTOR_SIZE,
	.bDescriptorType	= USB_DESCRIPTOR_TYPE_INTERFACE,
	.bInterfaceNumber	= 0,
	.bAlternateSetting	= 0,
	.bNumEndpoints		= 2,
	.bInterfaceClass	= 0xFF,
	.bInterfaceSubClass	= 0xFF,
	.bInterfaceProtocol	= 0xFF,
	.iInterface		= 0
};

static struct usb_endpoint_descriptor const usb_boot_fs_ep1_desc = {
	.bLength		= USB_ENDPOINT_DESCRIPTOR_SIZE,
	.bDescriptorType	= USB_DESCRIPTOR_TYPE_ENDPOINT,
	.bEndpointAddress	= 0x81,
	.bmAttributes		= 0x02,
	.wMaxPacketSize		= 64,
	.bInterval		= 0
};

static struct usb_endpoint_descriptor const usb_boot_hs_ep1_desc = {
	.bLength		= USB_ENDPOINT_DESCRIPTOR_SIZE,
	.bDescriptorType	= USB_DESCRIPTOR_TYPE_ENDPOINT,
	.bEndpointAddress	= 0x81,
	.bmAttributes		= 0x02,
	.wMaxPacketSize		= 512,
	.bInterval		= 0
};

static struct usb_endpoint_descriptor const usb_boot_fs_ep2_desc = {
	.bLength		= USB_ENDPOINT_DESCRIPTOR_SIZE,
	.bDescriptorType	= USB_DESCRIPTOR_TYPE_ENDPOINT,
	.bEndpointAddress	= 0x02,
	.bmAttributes		= 0x02,
	.wMaxPacketSize		= 64,
	.bInterval		= 0
};

static struct usb_endpoint_descriptor const usb_boot_hs_ep2_desc = {
	.bLength		= USB_ENDPOINT_DESCRIPTOR_SIZE,
	.bDescriptorType	= USB_DESCRIPTOR_TYPE_ENDPOINT,
	.bEndpointAddress	= 0x02,
	.bmAttributes		= 0x02,
	.wMaxPacketSize		= 512,
	.bInterval		= 0
};

#define USB_BOOT_CONTROL_EP		0
#define USB_BOOT_IN_EP			1
#define USB_BOOT_OUT_EP			2

#define USB_BOOT_FIFO_SIZE		512

void (*do_usb_boot(void))(void);
void init_usb_otg_phy_and_link(void);
void reset_usb_otg_phy_and_link(void);
void handle_usb_int(void);
void handle_usb_ep0_int(void);
void reset_usb_connection(void);
void set_usb_connection(void);
void receive_packet_via_usb(void);
void transfer_via_usb(void);
void transfer_via_usb_ep0(void);
void transfer_via_usb_ep1(void);
void transfer_via_usb_ep2(uint32_t);
void read_fifo_via_usb_ep(int, uint32_t *, int32_t);
void write_fifo_via_usb_ep(int, uint32_t const *, int32_t);

#endif
