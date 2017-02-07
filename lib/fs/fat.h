/*
 * Copyright (C) 2017
 * Author: metro94 <flattiles@gmail.com>
 *
 * Version: v1.0
 * --- Update time: 02/07/2017
 * --- Description: First build; code for FAT12/FAT16
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

#ifndef __FAT_H__
#define __FAT_H__

#define FAT_BLOCK_SIZE		512

struct partition_info_table {
	unsigned char part_type;
	unsigned int  rel_sectors;
	unsigned int  tot_sectors;
};

struct fat_info_table {
	unsigned int  sector_size;
	unsigned int  sectors_per_cluster;
	unsigned int  rsvd_sectors;
	unsigned int  fat_table_cnt;
	unsigned int  fat_table_sectors;
	unsigned int  root_max_items;
	unsigned int  hidden_sectors;
	unsigned int  tot_sectors;
	// Extended Info
	unsigned int  fat_type;
	unsigned int  tot_clusters;
	unsigned int  fat_table_starting_sector;
	unsigned int  root_starting_sector;
	unsigned int  data_starting_sector;
};

int  get_first_partition_info(void);
const char * get_first_partition_volume_label(void);
unsigned int find_file_by_name(const char *);
unsigned int fopen(const char *);
unsigned int fread(void *, unsigned int, unsigned int);
unsigned int fclose(unsigned int);
int  convert_filename(char *, const char *);
int  compare_filename_char(char, char);
unsigned int get_next_cluster_id(unsigned int);
void register_read_block_used_in_fat(void (*read_block)(void *, unsigned int, unsigned int));

#endif
