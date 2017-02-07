/*
 * Copyright (C) 2017
 * Author: metro94 <flattiles@gmail.com>
 *
 * Version: v1.0
 * --- Update time: 02/07/2017
 * --- Description: First build; header for USB
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


#ifndef __USB_H__
#define __USB_H__

#include <common.h>

enum USB_DESCRIPTOR_TYPE {
	USB_DESCRIPTOR_TYPE_DEVICE		= 0x1,
	USB_DESCRIPTOR_TYPE_CONFIGURATION	= 0x2,
	USB_DESCRIPTOR_TYPE_STRING		= 0x3,
	USB_DESCRIPTOR_TYPE_INTERFACE		= 0x4,
	USB_DESCRIPTOR_TYPE_ENDPOINT		= 0x5
};

enum USB_REQUEST_TYPE {
	USB_REQUEST_GET_STATUS		= 0,
	USB_REQUEST_CLEAR_FEATURE	= 1,
	USB_REQUEST_SET_FEATURE		= 3,
	USB_REQUEST_SET_ADDRESS		= 5,
	USB_REQUEST_GET_DESCRIPTOR	= 6,
	USB_REQUEST_SET_DESCRIPTOR	= 7,
	USB_REQUEST_GET_CONFIGURATION	= 8,
	USB_REQUEST_SET_CONFIGURATION	= 9,
	USB_REQUEST_GET_INTERFACE	= 10,
	USB_REQUEST_SET_INTERFACE	= 11,
	SYNCH_FRAME			= 12
};

struct usb_request {
	uint8_t  bmRequestType;
	uint8_t  bRequest;
	uint16_t wValue;
	uint16_t wIndex;
	uint16_t wLength;
};

struct usb_device_descriptor {
	uint8_t  bLength;
	uint8_t  bDescriptorType;
	uint16_t bcdUSB;
	uint8_t  bDeviceClass;
	uint8_t  bDeviceSubClass;
	uint8_t  bDeviceProtocol;
	uint8_t  bMaxPacketSize0;
	uint16_t idVendor;
	uint16_t idProduct;
	uint16_t bcdDevice;
	uint8_t  iManufacturer;
	uint8_t  iProduct;
	uint8_t  iSerialNumber;
	uint8_t  bNumConfigurations;
} __attribute__ ((packed, aligned(4)));

#define USB_DEVICE_DESCRIPTOR_SIZE		18

struct usb_configuration_descriptor {
	uint8_t  bLength;
	uint8_t  bDescriptorType;
	uint16_t wTotalLength;
	uint8_t  bNumInterface;
	uint8_t  bConfigurationValue;
	uint8_t  iConfiguration;
	uint8_t  bmAttributes;
	uint8_t  MaxPower;
} __attribute__ ((packed, aligned(4)));

#define USB_CONFIGURATION_DESCRIPTOR_SIZE	9

struct usb_string_descriptor {
	uint8_t  bLength;
	uint8_t  bDescriptorType;
	uint16_t wData[1];
} __attribute__ ((packed, aligned(4)));

#define USB_STRING_DESCRIPTOR_SIZE		4

struct usb_interface_descriptor {
	uint8_t  bLength;
	uint8_t  bDescriptorType;
	uint8_t  bInterfaceNumber;
	uint8_t  bAlternateSetting;
	uint8_t  bNumEndpoints;
	uint8_t  bInterfaceClass;
	uint8_t  bInterfaceSubClass;
	uint8_t  bInterfaceProtocol;
	uint8_t  iInterface;
} __attribute__ ((packed, aligned(4)));

#define USB_INTERFACE_DESCRIPTOR_SIZE		9

struct usb_endpoint_descriptor {
	uint8_t  bLength;
	uint8_t  bDescriptorType;
	uint8_t  bEndpointAddress;
	uint8_t  bmAttributes;
	uint16_t wMaxPacketSize;
	uint8_t  bInterval;
} __attribute__ ((packed, aligned(4)));

#define USB_ENDPOINT_DESCRIPTOR_SIZE		7

#endif

