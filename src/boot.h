/*
 * Copyright (C) 2017
 * Author: metro94 <flattiles@gmail.com>
 *
 * Version: v1.0
 * --- Update time: 02/07/2017
 * --- Description: First build; header for boot sequence
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

#ifndef __BOOT_H__
#define __BOOT_H__

#include <common.h>
#include <io.h>
#include <std/printf.h>
#include <std/debug.h>

#include <led.h>
#include <clksrc.h>
#include <serial.h>
#include <timer.h>
#include <i2c.h>
#include <pmic.h>
#include <ddr3.h>
#include <drex.h>
#include <bus.h>
#include <sdfsboot.h>
#include <usbboot.h>

extern uint32_t build_info;

typedef void (*init_fn)(void);

void boot_master_cpu(uint32_t) __attribute__ ((noreturn));
void boot_slave_cpu (uint32_t) __attribute__ ((noreturn));

void disp_compile_info(void);
void wakeup_slave_cpu(void);

#endif

