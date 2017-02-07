/*
 * Copyright (C) 2017
 * Author: metro94 <flattiles@gmail.com>
 *
 * Version: v1.0
 * --- Update time: 02/07/2017
 * --- Description: First build; header for PMIC on board
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

#ifndef __PMIC_H__
#define __PMIC_H__

#include <common.h>
#include <std/debug.h>
#include <std/math.h>
#include <std/printf.h>

#include <x-powers/axp228.h>

#include <i2c.h>

void init_pmic(void);
uint8_t get_pmic_register(uint8_t);
void set_pmic_register(uint8_t, uint8_t);

void dump_pmic(void);

#endif
