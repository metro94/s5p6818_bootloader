/*
 * Copyright (C) 2017
 * Author: metro94 <flattiles@gmail.com>
 *
 * Version: v1.0
 * --- Update time: 02/07/2017
 * --- Description: First build; code for SD boot with File System
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

#include <sdfsboot.h>

void (*do_sdfs_boot(void))(void)
{
	uint32_t str_index;
	uint32_t fid;
	char *str;
	char *eof;
#ifdef PI_BOOT_VOLUME_LABEL
	const char *volume_label;
#endif
	char raw_filename[13];
	
	void (*next_stage_addr)(void) = NULL;
	char *filename;
	uint32_t load_addr;
	uint32_t launch_addr;
	
	init_sdcard_detect();
	if (!is_sdcard_detected()) {
		debug(DEBUG_LEVEL_WARN, "SD Card not detected, skip SDFS boot\n");
		return next_stage_addr;
	}
	
	if (!init_sdcard()) {
		debug(DEBUG_LEVEL_WARN, "Cannot initialize SDMMC, skip SDFS boot\n");
		return next_stage_addr;
	}
	
	register_read_block_used_in_fat(read_sd_block);
	
	if (!get_first_partition_info())
		return next_stage_addr;
	
#ifdef PI_BOOT_VOLUME_LABEL
	volume_label = get_first_partition_volume_label();
	if (strncmp(volume_label, PI_BOOT_VOLUME_LABEL, 11) != 0) {
		printf("Warning: Expected volume label is \"%s\", but found \"%s\"\n", PI_BOOT_VOLUME_LABEL, volume_label);
		return next_stage_addr;
	}
#endif

	filename = NULL;
	load_addr = NULL;
	launch_addr = NULL;
	fid = fopen(PI_BOOTLOADER_CONF_FILENAME);
	if (fid == 0) {
		printf("Warning: Cannot open configuration file \"%s\"; use default settings\n", PI_BOOTLOADER_CONF_FILENAME);
		filename = PI_BOOTLOADER_DEFAULT_FILENAME;
		load_addr = PI_BOOTLOADER_DEFAULT_LOAD_ADDR;
		launch_addr = PI_BOOTLOADER_DEFAULT_LAUNCH_ADDR;
	} else {
		for (str_index = 0; str_index < 13; ++str_index)
			raw_filename[str_index] = 0x0;
		str = (void *)(uint64_t)ddr3_conf.addr_base;
		eof = str + fread(str, ~0U, fid);
		while (str < eof) {
			if (strncmp(str, "filename=", 9) == 0) {
				str += 9;
				str_index = 0;
				while (*str != '\n' && *str != '\r' && *str != 0x0 && str_index < 12 && str < eof)
					raw_filename[str_index++] = *str++;
				filename = raw_filename;
			}
			else if (strncmp(str, "load_addr=", 10) == 0) {
				str += 10;
				while (1) {
					if ('0' <= *str && *str <= '9')
						load_addr = (load_addr << 4) | (*str - '0');
					else if ('A' <= *str && *str <= 'F')
						load_addr = (load_addr << 4) | (*str - 'A' + 10);
					else if ('a' <= *str && *str <= 'f')
						load_addr = (load_addr << 4) | (*str - 'a' + 10);
					else if (*str == 'X' || *str == 'x')
						;	// Does nothing
					else
						break;
					++str;
				}
			}
			else if (strncmp(str, "launch_addr=", 12) == 0) {
				str += 12;
				while (1) {
					if ('0' <= *str && *str <= '9')
						launch_addr = (launch_addr << 4) | (*str - '0');
					else if ('A' <= *str && *str <= 'F')
						launch_addr = (launch_addr << 4) | (*str - 'A' + 10);
					else if ('a' <= *str && *str <= 'f')
						launch_addr = (launch_addr << 4) | (*str - 'a' + 10);
					else if (*str == 'X' || *str == 'x')
						;	// Does nothing
					else
						break;
					++str;
				}
			}
			while (*str != '\n' && *str != '\r' && str < eof)
				++str;
			while ((*str == '\n' || *str == '\r') && str < eof)
				++str;
		}
		
		if (!filename) {
			filename = PI_BOOTLOADER_DEFAULT_FILENAME;
			printf("Warning: filename not set; use default settings \"%s\"\n", filename);
		}
		
		if (!load_addr) {
			load_addr = PI_BOOTLOADER_DEFAULT_LOAD_ADDR;
			printf("Warning: load_addr not set; use default settings \"%08x\"\n", load_addr);
		}
		
		if (!launch_addr) {
			launch_addr = load_addr;
			printf("Warning: launch_addr not set; use load_addr \"%08x\"\n", load_addr);
		}
	}
	
	fid = fopen(filename);
	if (fid == 0) {
		printf("Warning: Cannot find boot binary code \"%s\", skip SD Boot\n", filename);
		return next_stage_addr;
	}
	
	fread((void *)(uint64_t)load_addr, ~0U, fid);
	fclose(fid);
	
	next_stage_addr = (void (*)(void))(uint64_t)launch_addr;
	
	reset_sdmmc();
	
	return next_stage_addr;
}
