/*
 * Copyright (C) 2017
 * Author: metro94 <flattiles@gmail.com>
 *
 * Version: v1.0
 * --- Update time: 02/07/2017
 * --- Description: First build; header for SD v2.0 or later version
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


#ifndef __SD_H__
#define __SD_H__

enum sd_command {
	SD_CMD0		= 0,
	SD_CMD2		= 2,
	SD_CMD3		= 3,
	SD_ACMD6	= 6,
	SD_CMD7		= 7,
	SD_CMD8		= 8,
	SD_CMD9		= 9,
	SD_CMD11	= 11,
	SD_CMD12	= 12,
	SD_CMD13	= 13,
	SD_CMD16	= 16,
	SD_CMD17	= 17,
	SD_CMD18	= 18,
	SD_CMD19	= 19,
	SD_ACMD41	= 41,
	SD_CMD42	= 42,
	SD_ACMD51	= 51,
	SD_CMD55	= 55
};

#endif
