/*
 * Copyright (C) 2017
 * Author: metro94 <flattiles@gmail.com>
 *
 * Version: v1.0
 * --- Update time: 02/07/2017
 * --- Description: First build; code of driver for Nexell SoC IP Reset
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

#include <nx_iprst.h>

inline void nx_do_iprst(nx_iprst_regs * const iprst_block, int iprst_id)
{
	iprst_block[iprst_id >> 5] &= ~(1 << (iprst_id & 0x1F));
	iprst_block[iprst_id >> 5] |=  (1 << (iprst_id & 0x1F));
}

inline void nx_assert_iprst(nx_iprst_regs * const iprst_block, int iprst_id)
{
	iprst_block[iprst_id >> 5] &= ~(1 << (iprst_id & 0x1F));
}

inline void nx_release_iprst(nx_iprst_regs * const iprst_block, int iprst_id)
{
	iprst_block[iprst_id >> 5] |=  (1 << (iprst_id & 0x1F));
}
