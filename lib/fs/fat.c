/*
 * Copyright (C) 2017
 * Author: metro94 <flattiles@gmail.com>
 *
 * Version: v1.0
 * --- Update time: 02/07/2017
 * --- Description: First build; header for FAT12/FAT16
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

#include <std/debug.h>

#include <fat.h>

static void (*__read_block_used_in_fat)(void *, unsigned int, unsigned int);
static unsigned int __buf_used_in_fat[FAT_BLOCK_SIZE / 4];
static struct partition_info_table partition_info;
static struct fat_info_table fat_info;

int get_first_partition_info(void)
{
	__read_block_used_in_fat(__buf_used_in_fat, 0, 1);
	
	// Checks if MBR is valid
	if ((__buf_used_in_fat[0x1FE / 4] >> 16) == 0x55AA) {
		debug(DEBUG_LEVEL_INFO, "Invalid MBR\n");
		return 0;
	}
	
	partition_info.part_type = (__buf_used_in_fat[0x1C2 / 4] >> 16) & 0xFF;
	partition_info.rel_sectors =
		((__buf_used_in_fat[0x1C6 / 4] & 0xFFFF0000) >> 16) |
		((__buf_used_in_fat[0x1C8 / 4] & 0x0000FFFF) << 16);
	partition_info.tot_sectors =
		((__buf_used_in_fat[0x1CA / 4] & 0xFFFF0000) >> 16) |
		((__buf_used_in_fat[0x1CC / 4] & 0x0000FFFF) << 16);
	
	// Only FAT12/16 are supported
	if (partition_info.part_type != 0x04 && partition_info.part_type != 0x06) {
		debug(DEBUG_LEVEL_WARN, "Cannot support partition type: %02x\n", partition_info.part_type);
		return 0;
	}
	
	debug(DEBUG_LEVEL_INFO, "First Partition Information:\n");
	debug(DEBUG_LEVEL_INFO, "Boot Indicator = %02x\n", (__buf_used_in_fat[0x1BE / 4] >> 16) & 0xFF);
	debug(DEBUG_LEVEL_INFO, "Starting Head = %u\n", (__buf_used_in_fat[0x1BE / 4] >> 24) & 0xFF);
	debug(DEBUG_LEVEL_INFO, "Starting Sector = %u\n", (__buf_used_in_fat[0x1C0 / 4] >> 0) & 0x3F);
	debug(DEBUG_LEVEL_INFO, "Starting Cylinder = %u\n", (__buf_used_in_fat[0x1C0 / 4] >> 6) & 0x3FF);
	debug(DEBUG_LEVEL_INFO, "System ID = %02x\n", (__buf_used_in_fat[0x1C2 / 4] >> 16) & 0xFF);
	debug(DEBUG_LEVEL_INFO, "Ending Head = %02x\n", (__buf_used_in_fat[0x1C3 / 4] >> 24) & 0xFF);
	debug(DEBUG_LEVEL_INFO, "Ending Sector = %u\n", (__buf_used_in_fat[0x1C4 / 4] >> 0) & 0x3F);
	debug(DEBUG_LEVEL_INFO, "Ending Cylinder = %u\n", (__buf_used_in_fat[0x1C4 / 4] >> 6) & 0x3FF);
	debug(DEBUG_LEVEL_INFO, "Relative Sectors = %u\n",
		((__buf_used_in_fat[0x1C6 / 4] & 0xFFFF0000) >> 16) |
		((__buf_used_in_fat[0x1C8 / 4] & 0x0000FFFF) << 16)
	);
	debug(DEBUG_LEVEL_INFO, "Total Sectors = %u\n",
		((__buf_used_in_fat[0x1CA / 4] & 0xFFFF0000) >> 16) |
		((__buf_used_in_fat[0x1CC / 4] & 0x0000FFFF) << 16)
	);
	
	__read_block_used_in_fat(__buf_used_in_fat, partition_info.rel_sectors, 1);
	
	fat_info.sector_size =
		((__buf_used_in_fat[0xB / 4] & 0xFF000000) >> 24) |
		((__buf_used_in_fat[0xC / 4] & 0x000000FF) <<  8);
	fat_info.sectors_per_cluster = (__buf_used_in_fat[0xD / 4] >> 8) & 0xFF;
	fat_info.rsvd_sectors = (__buf_used_in_fat[0xE / 4] >> 16) & 0xFFFF;
	fat_info.fat_table_cnt = (__buf_used_in_fat[0x10 / 4] >> 0) & 0xFF;
	fat_info.root_max_items = (__buf_used_in_fat[0x11 / 4] >> 8) & 0xFFFF;
	fat_info.tot_sectors =
		((__buf_used_in_fat[0x13 / 4] & 0xFF000000) >> 24) |
		((__buf_used_in_fat[0x14 / 4] & 0x000000FF) <<  8);
	if (fat_info.tot_sectors == 0)
		fat_info.tot_sectors = __buf_used_in_fat[0x20 / 4];
	fat_info.fat_table_sectors = (__buf_used_in_fat[0x16 / 4] >> 16) & 0xFFFF;
	fat_info.hidden_sectors = __buf_used_in_fat[0x1C / 4];
	
	// Checks if DBR is valid
	if ((__buf_used_in_fat[0x1FE / 4] >> 16) == 0x55AA) {
		debug(DEBUG_LEVEL_INFO, "Invalid DBR\n");
		return 0;
	}
	
	debug(DEBUG_LEVEL_INFO, "FAT Information:\n");
	debug(DEBUG_LEVEL_INFO, "Sector Size = %u\n", fat_info.sector_size);
	debug(DEBUG_LEVEL_INFO, "Sectors Per Cluster = %u\n", fat_info.sectors_per_cluster);
	debug(DEBUG_LEVEL_INFO, "Reserved Sectors = %u\n", fat_info.rsvd_sectors);
	debug(DEBUG_LEVEL_INFO, "FAT Table Count = %u\n", fat_info.fat_table_cnt);
	debug(DEBUG_LEVEL_INFO, "FAT Table Sectors = %u\n", fat_info.fat_table_sectors);
	debug(DEBUG_LEVEL_INFO, "Root Maximum Items = %u\n", fat_info.root_max_items);
	debug(DEBUG_LEVEL_INFO, "Hidden Sectors = %u\n", fat_info.hidden_sectors);
	debug(DEBUG_LEVEL_INFO, "Total Sectors = %u\n", fat_info.tot_sectors);
	
	fat_info.tot_clusters = (fat_info.tot_sectors -
		fat_info.rsvd_sectors -
		fat_info.fat_table_cnt * fat_info.fat_table_sectors) /
		fat_info.sectors_per_cluster;
	fat_info.fat_type = (fat_info.tot_clusters < 4085) ? 0 : 1;
	fat_info.fat_table_starting_sector = partition_info.rel_sectors +
		fat_info.rsvd_sectors;
	fat_info.root_starting_sector = partition_info.rel_sectors +
		fat_info.rsvd_sectors +
		fat_info.fat_table_cnt * fat_info.fat_table_sectors;
	fat_info.data_starting_sector = partition_info.rel_sectors +
		fat_info.rsvd_sectors +
		fat_info.fat_table_cnt * fat_info.fat_table_sectors +
		fat_info.root_max_items * 32 / 512;
		
	debug(DEBUG_LEVEL_INFO, "FAT Type = %s\n", fat_info.fat_type ? "FAT16" : "FAT12");
	debug(DEBUG_LEVEL_INFO, "Total Clusters = %d\n", fat_info.tot_clusters);
	debug(DEBUG_LEVEL_INFO, "FAT Table Starting Sector = %d\n", fat_info.fat_table_starting_sector);
	debug(DEBUG_LEVEL_INFO, "Root Starting Sector = %d\n", fat_info.root_starting_sector);
	debug(DEBUG_LEVEL_INFO, "Data Starting Sector = %d\n", fat_info.data_starting_sector);
	
	return 1;
}

void register_read_block_used_in_fat(void (*read_block)(void *, unsigned int, unsigned int))
{
	__read_block_used_in_fat = read_block;
}

const char * get_first_partition_volume_label(void)
{
	int str_index;
	unsigned int  item_num;
	unsigned char attr;
	
	static char volume_label[12];
	
	for (item_num = 0; item_num < fat_info.root_max_items; ++item_num) {
		// Loads FAT Table per sector
		if ((item_num & 0xF) == 0x0)
			__read_block_used_in_fat(__buf_used_in_fat, fat_info.root_starting_sector + (item_num >> 4), 1);
		
		// Checks if the item is volumn label
		attr = (__buf_used_in_fat[((item_num & 0xF) * 0x20 + 0xB) / 4] >> 24) & 0xFF;
		if (attr != 0x08)
			continue;
			
		// Gets volumn label
		for (str_index = 0; str_index < 11; ++str_index)
			volume_label[str_index] = (__buf_used_in_fat[((item_num & 0xF) * 0x20 + str_index) / 4] >>
				(8 * (str_index & 0x3))) & 0xFF;
		for (str_index = 10; str_index >= 0; --str_index)
			if (volume_label[str_index] == 0x20)
				volume_label[str_index] = 0x0;
			else
				break;
		break;
	}
	
	return volume_label;
}

unsigned int find_file_by_name(const char *raw_filename)
{
	int str_index;
	int str_equal;
	unsigned int  item_num;
	unsigned char attr;
	char converted_filename[12];
	
	if (convert_filename(converted_filename, raw_filename) == 0)
		return 0;
		
	for (item_num = 0; item_num < fat_info.root_max_items; ++item_num) {
		// Loads FAT Table per sector
		if ((item_num & 0xF) == 0x0)
			__read_block_used_in_fat(__buf_used_in_fat, fat_info.root_starting_sector + (item_num >> 4), 1);
		
		// Checks if the item is valid
		attr = (__buf_used_in_fat[((item_num & 0xF) * 0x20 + 0xB) / 4] >> 24) & 0xFF;
		if (attr == 0x08 || attr == 0x0F)
			continue;
			
		// Compare filename
		str_equal = 1;
		for (str_index = 0; str_index < 11; ++str_index) {
			if (compare_filename_char((__buf_used_in_fat[((item_num & 0xF) * 0x20 + str_index) / 4] >>
				(8 * (str_index & 0x3))) & 0xFF,
				converted_filename[str_index])) {
				str_equal = 0;
				break;
			}
		}
		if (str_equal)
			return (__buf_used_in_fat[((item_num & 0xF) * 0x20 + 0x1A) / 4] >> 16) & 0xFFFF;
	}
	
	return 0;
}

unsigned int fopen(const char *filename)
{
	return find_file_by_name(filename);
}

unsigned int fread(void *buf, unsigned int max_size, unsigned int cluster_id)
{
	unsigned int  read_size;
	unsigned char *buf_in_8;
	
	buf_in_8 = buf;
	read_size = 0;
	while (max_size > 0) {
		__read_block_used_in_fat(
			buf_in_8,
			fat_info.data_starting_sector +
			(cluster_id - 2) * fat_info.sectors_per_cluster,
			fat_info.sectors_per_cluster
		);
		buf_in_8 += fat_info.sectors_per_cluster * 512;
		read_size += fat_info.sectors_per_cluster * 512;
		// Checks max_size
		if (max_size > fat_info.sectors_per_cluster * 512)
			max_size -= fat_info.sectors_per_cluster * 512;
		else
			max_size = 0;
		// Checks cluster ending
		if (max_size > 0) {
			cluster_id = get_next_cluster_id(cluster_id);
			if (cluster_id == 0) {
				debug(DEBUG_LEVEL_WARN, "Not Used Cluster, skip\n");
				return 0;
			} else if ((fat_info.fat_type == 0 && cluster_id >= 0xFF0) ||
				(fat_info.fat_type == 1 && cluster_id >= 0xFFF0)) {
				max_size = 0;
			}
		}
	}
	
	return read_size;
}

unsigned int fclose(unsigned int file_id)
{
	(void)file_id;
	
	return 0;
}

int  convert_filename(char *dest, const char *src)
{
	int str_index;
	int str_len;
	int dot_pos;
	
	// Checks filename length
	for (str_index = 0; str_index < 12; ++str_index)
		if (src[str_index] == 0x0)
			break;
	
	if (src[str_index] == 0x0)
		str_len = str_index;
	else {
		debug(DEBUG_LEVEL_WARN, "Filename is too long\n");
		return 0;
	}
	
	for (str_index = 0; str_index < 11; ++str_index)
		dest[str_index] = 0x20;
	dest[str_index] = 0x0;
	
	// Checks filename validity
	for (str_index = str_len - 1; str_index > 0; --str_index)
		if (src[str_index] == '.')
			break;
	
	if (src[str_index] == '.') {	// With Extension Name
		dot_pos = str_index;
		if (dot_pos <= 8 && str_len - dot_pos - 1 <= 3) {
			for (str_index = 0; str_index < dot_pos; ++str_index)
				dest[str_index] = src[str_index];
			for (str_index = dot_pos + 1; str_index < str_len; ++str_index)
				dest[str_index - dot_pos - 1 + 8] = src[str_index];
		}
		else {
			debug(DEBUG_LEVEL_WARN, "Filename is invalid\n");
			return 0;
		}
	} else {			// Without Extension Name
		if (str_len <= 8) {
			for (str_index = 0; str_index < str_len; ++str_index)
				dest[str_index] = src[str_index];
		}
		else {
			debug(DEBUG_LEVEL_WARN, "Filename is invalid\n");
			return 0;
		}
	}
	
	return 1;
}

int  compare_filename_char(char x, char y)
{
	if ('a' <= x && x <= 'z')
		x = x - 'a' + 'A';
	if ('a' <= y && y <= 'z')
		y = y - 'a' + 'A';
	if (x == y)
		return 0;
	else if (x < y)
		return -1;
	else
		return 1;
}

unsigned int get_next_cluster_id(unsigned int cur_cluster_id) {
	unsigned int next_cluster_id_offset;
	unsigned int next_cluster_id;
	
	if (fat_info.fat_type == 0) {
		next_cluster_id_offset = cur_cluster_id * 3;
		__read_block_used_in_fat(
			__buf_used_in_fat,
			fat_info.fat_table_starting_sector + (next_cluster_id_offset >> 10),
			1
		);
		if ((next_cluster_id_offset & 0x3FF) < 0x3FE) {
			if ((next_cluster_id_offset & 0x7) < 0x6) {
				next_cluster_id = (__buf_used_in_fat[((next_cluster_id_offset >> 1) & 0x1FF) / 4] >>
					(4 * (next_cluster_id_offset & 0x7))) & 0xFFF;
			} else {
				next_cluster_id  = (__buf_used_in_fat[((next_cluster_id_offset >> 1) & 0x1FF) / 4] >>
					(4 * (next_cluster_id_offset & 0x7))) &
					((1 << (4 * (0x8 - (next_cluster_id_offset & 0x7)))) - 1);
				next_cluster_id |= ((__buf_used_in_fat[((next_cluster_id_offset >> 1) & 0x1FF) / 4 + 1] &
					((1 << (4 * ((next_cluster_id_offset & 0x7) - 0x5	))) - 1))) <<
					(4 * (0x8 - (next_cluster_id_offset & 0x7)));
			}
		} else {
			next_cluster_id  = (__buf_used_in_fat[0x1FF / 4] >>
				(4 * (next_cluster_id_offset & 0x7))) &
				((1 << (4 * (0x8 - (next_cluster_id_offset & 0x7)))) - 1);
			__read_block_used_in_fat(
				__buf_used_in_fat,
				fat_info.fat_table_starting_sector + (next_cluster_id_offset >> 10) + 1,
				1
			);
			next_cluster_id |= ((__buf_used_in_fat[0x0 / 4] &
				((1 << (4 * ((next_cluster_id_offset & 0x7) - 0x5))) - 1))) <<
				(4 * (0x8 - (next_cluster_id_offset & 0x7)));
		}
	} else {
		next_cluster_id_offset = cur_cluster_id * 4;
		__read_block_used_in_fat(
			__buf_used_in_fat,
			fat_info.fat_table_starting_sector + (next_cluster_id_offset >> 10),
			1
		);
		next_cluster_id = (__buf_used_in_fat[((next_cluster_id_offset >> 1) & 0x1FF) / 4] >>
			(4 * (next_cluster_id_offset & 0x7))) & 0xFFFF;
	}
	
	return next_cluster_id;
}
