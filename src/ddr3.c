/*
 * Copyright (C) 2017
 * Author: metro94 <flattiles@gmail.com>
 *
 * Version: v1.0
 * --- Update time: 02/07/2017
 * --- Description: First build; code for DDR3 SDRAM Initialization
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

#include <ddr3.h>

void send_ddr3_direct_cmd(enum DDR3_CMD_TYPE cmd, int chip, int bank, int addr)
{
	debug(DEBUG_LEVEL_INFO, "Direct CMD: cmd = %x, chip = %x, bank = %x, addr = %04x\n", cmd, chip, bank, addr);
	while (!(nx_drex->con_control & (1 << 8)) || (nx_drex->chip_status & (0xF << 0)));
	nx_drex->direct_cmd =
		(cmd  << 24) |
		(chip << 20) |
		(bank << 16) |
		(addr << 0);
}

void do_ddr3_read_leveling(void)
{
	debug(DEBUG_LEVEL_INFO, "DDR3 Read Leveling starts\n");
	
	send_ddr3_direct_cmd(DDR3_CMD_MRS, 0, 3, (1 << 2));
	
	nx_ddrphy->phy_con[1] = (nx_ddrphy->phy_con[1] & ~(0xFFFF)) | 0xFF00;
	nx_ddrphy->phy_con[2] |=  (1 << 25);
	nx_ddrphy->phy_con[3] |=  (1 << 19);
	while (!(nx_ddrphy->phy_con[3] & (1 << 26)));
	nx_ddrphy->phy_con[3] &= ~(1 << 19);
	
	/* 1.30 */
	send_ddr3_direct_cmd(DDR3_CMD_MRS, 0, 3, 0);
}

void do_ddr3_hw_write_leveling(void)
{
	debug(DEBUG_LEVEL_INFO, "DDR3 H/W Write Leveling starts\n");
	
	send_ddr3_direct_cmd(DDR3_CMD_PALL, 0, 0, 0);
	send_ddr3_direct_cmd(DDR3_CMD_MRS, 0, 1,
		(0x11 << 2) |
		(   1 << 7) |
		(   1 << 1)
	);
	
	nx_drex->wr_lvl_config[0] |=  (1 << 0);
	nx_drex->wr_lvl_config[1] |=  (1 << 0);
	nx_drex->wr_lvl_config[1] &= ~(1 << 0);
	
	nx_ddrphy->lp_ddr_con[4] |= ~(0x3 << 7);
	nx_ddrphy->phy_con[0] |=  (1 << 16);
	nx_ddrphy->phy_con[3] |=  (1 << 16);
	while (!(nx_ddrphy->phy_con[3] & (1 << 24)));
	nx_ddrphy->phy_con[3] &= ~(1 << 24);
	nx_ddrphy->phy_con[3] &= ~(1 << 16);
	nx_ddrphy->phy_con[0] &= ~(1 << 16);
	
	nx_drex->wr_lvl_config[0] &= ~(1 << 0);
	
	nx_ddrphy->lp_ddr_con[4] &= ~(0x3 << 7);
	
	send_ddr3_direct_cmd(DDR3_CMD_MRS, 0, 1, 
		(0x11 << 2) |
		(   1 << 1)
	);
	
	delay_us(10);
	
	nx_ddrphy->phy_con[3] |=  (   1 << 0);
	nx_ddrphy->phy_con[3] &= ~(0xFF << 0);
}

void do_ddr3_gate_leveling(void)
{
	debug(DEBUG_LEVEL_INFO, "DDR3 Gate Leveling starts\n");
	
	send_ddr3_direct_cmd(DDR3_CMD_PALL, 0, 0, 0);
	send_ddr3_direct_cmd(DDR3_CMD_MRS, 0, 3, (1 << 2));
	
	nx_ddrphy->phy_con[2] |=  (1 << 24);
	nx_ddrphy->phy_con[0] |=  (1 << 6) | (1 << 8);
	nx_ddrphy->phy_con[0] &= ~(0xF << 20);
	nx_ddrphy->phy_con[3] |=  (1 << 18);
	while (!(nx_ddrphy->phy_con[3] & (1 << 26)));
	nx_ddrphy->phy_con[3] &= ~(1 << 18);
	nx_ddrphy->lp_con[0] &= ~(0x1FF << 0);
	nx_ddrphy->r_odt_con[0] &= ~(1 << 16);
	
	send_ddr3_direct_cmd(DDR3_CMD_MRS, 0, 3, 0);
}

void do_ddr3_zq_calibration(void)
{
	debug(DEBUG_LEVEL_INFO, "DDR3 ZQ Calibration starts\n");
	
	nx_ddrphy->zq_con[2] = 7;
	nx_ddrphy->drv_ds_con[0] = 0;
	nx_ddrphy->drv_ds_con[1] = 0;
	nx_ddrphy->zq_con[0] =
		( 1 << 27) |
		( 6 << 24) |
		( 2 << 21) |
		( 1 << 18) |
		(48 <<  4) |
		( 1 <<  2);
	nx_ddrphy->zq_con[0] |=  (1 <<  1);
	while (!(nx_ddrphy->zq_con[1] & (1 << 0)));
	nx_ddrphy->zq_con[0] &= ~(1 <<  1);
	nx_ddrphy->zq_con[0] &= ~(1 << 18);
}

void do_ddr3_write_latency_calibration(void)
{
	debug(DEBUG_LEVEL_INFO, "DDR3 Write Latency Calibration starts\n");
	
	nx_drex->wr_tra_config |=  (1 << 0);
	
	nx_ddrphy->phy_con[0] &= ~(1 << 14);
	nx_ddrphy->phy_con[0] |=  (1 << 14);
	nx_ddrphy->phy_con[3] |=  (1 << 20);
	nx_ddrphy->phy_con[3] |=  (1 << 21);
	while (!(nx_ddrphy->phy_con[3] & (1 << 27)));
	nx_ddrphy->phy_con[3] &= ~(1 << 21);
	
	nx_drex->wr_tra_config &= ~(1 << 0);
}

void do_ddr3_write_dq_calibration(void)
{
	debug(DEBUG_LEVEL_INFO, "DDR3 Write DQ Calibration starts\n");
	
	nx_drex->wr_tra_config |=  (1 << 0);
	
	nx_ddrphy->phy_con[1] = (nx_ddrphy->phy_con[1] & ~(0xFFFF)) | 0x0100;
	nx_ddrphy->phy_con[0] |=  (1 << 13);
	nx_ddrphy->phy_con[1] = (nx_ddrphy->phy_con[1] & ~(0xFFFF)) | 0xFF00;
	nx_ddrphy->phy_con[0] &= ~(1 << 13);
	nx_ddrphy->phy_con[2] |=  (1 << 26);
	nx_ddrphy->phy_con[2] |=  (1 << 27);
	while (!(nx_ddrphy->phy_con[3] & (1 << 26)));
	nx_ddrphy->phy_con[2] &= ~(1 << 27);
	
	nx_drex->wr_tra_config &= ~(1 << 0);
	
	nx_ddrphy->phy_con[2] |=  (1 << 24);
	nx_ddrphy->phy_con[0] |=  (1 << 8) | (1 << 6);
	nx_ddrphy->phy_con[1] |=  (0xF << 20) | (0 << 20);
	nx_ddrphy->offset_c_con[0] = 0;
	nx_ddrphy->phy_con[2] &= ~(1 << 24);
	nx_ddrphy->lp_con[0] = 0;
	nx_ddrphy->r_odt_con[0] &= ~(1 << 16);
}

void init_ddr3(void)
{
	debug("", "\n");
	debug(DEBUG_LEVEL_INFO, "Trying to initialize DDR3\n");

	/* 1.1 */
	// Does IP Reset	
	nx_do_iprst(nx_iprst_block, NX_IPRST_ID_DREX_APB);
	nx_do_iprst(nx_iprst_block, NX_IPRST_ID_DREX_AXI);
	nx_do_iprst(nx_iprst_block, NX_IPRST_ID_DREX_CORE);
	
	delay_us(200);
	
	/* 1.2 */
	/* 2.1 */
	nx_ddrphy->phy_con[0] = (nx_ddrphy->phy_con[0] & ~((0x7 << 17) | (0x3 << 11))) | (( 7 << 17) | (1 << 11));
	/* 2.2 */
	nx_ddrphy->lp_ddr_con[3] = (nx_ddrphy->lp_ddr_con[3] & ~0x1FFF) | 0x105E;
	nx_ddrphy->lp_ddr_con[4] = (nx_ddrphy->lp_ddr_con[4] & ~0x1FFF) | 0x107F;
	nx_ddrphy->phy_con[4] = (nx_ddrphy->phy_con[4] &
		~((0x1F << 16) |
		  (0x1F <<  8) |
		  (0x1F <<  0))) |
		((  (ddr3_conf.cwl + ddr3_conf.al) << 16) |
		(                      ddr3_conf.bl <<  8) |
		((ddr3_conf.cl + ddr3_conf.al + 1) <<  0));
	/* ZQ Calibration */
	/* 2.3 */
	do_ddr3_zq_calibration();

	/* 1.3 */
	/* 2.4 */
	nx_drex->con_control = 0x0FFF1000;

	nx_drex->con_control |=  (1 << 28);

	/* 1.4 */
	/* 2.5 */
	while (!(nx_drex->phy_status & (1 << 3)));

	/* 1.5 */
	nx_drex->con_control = (1 << 28);

	/* 1.6 */
	/* 2.6 */
	nx_ddrphy->lp_con[0] = 0x1ff;

	/* 2.7 */

	/* 2.8 */
	/* 1.7 */
	nx_drex->phy_control[0] |=  (1 << 3);

	/* 1.8 */
	nx_drex->phy_control[0] &= ~(1 << 3);

	/* 1.9 */
	nx_tzasc->mem_base_config[0] =
		(  (ddr3_conf.addr_base & 0xff000000) >> 8) |
		(((1 << 11) - (ddr3_conf.size >> 24)) << 0);

	/* 1.10 */
	nx_tzasc->mem_config[0] =
		(           ddr3_conf.bank_lsb << 20) |
		(      ddr3_conf.rank_inter_en << 19) |
		(         ddr3_conf.bit_sel_en << 18) |
		(            ddr3_conf.bit_sel << 16) |
		(                             2 << 12) |
		(          (ddr3_conf.col - 7) <<  8) |
		(         (ddr3_conf.row - 12) <<  4) |
		((ddr3_conf.bank == 8 ? 3 : 2) <<  0);

	/* 1.11 */
	nx_drex->prech_config_0 =
		(0xF << 28) |
		(  0 << 16);
	nx_drex->prech_config_1 = 0;
	nx_drex->pwr_dn_config = 0xFF;

	/* 1.12 */
	nx_drex->timing_pzq = ddr3_conf.t_pzq;
	nx_drex->timing_aref =
		(ddr3_conf.t_refi << 16) |
		(ddr3_conf.t_refi <<  0);
	nx_drex->timing_row =
		(ddr3_conf.t_rfc << 24) |
		(ddr3_conf.t_rrd << 20) |
		(ddr3_conf.t_rp  << 16) |
		(ddr3_conf.t_rcd << 12) |
		(ddr3_conf.t_rc  <<  6) |
		(ddr3_conf.t_ras <<  0);
	nx_drex->timing_data_0 = \
		(                   ddr3_conf.t_wtr << 28) |
		(                   ddr3_conf.t_wr  << 24) |
		(                   ddr3_conf.t_rtp << 20) |
		(                                  0 << 17) |
		(                                  1 << 14) |
		(                                  1 << 12) |
		(   (ddr3_conf.cwl + ddr3_conf.al) <<  8) |
		(                                  0 <<  4) |
		((ddr3_conf.cl + ddr3_conf.al + 1) <<  0);
	nx_drex->timing_power_0 = \
		(ddr3_conf.t_faw << 26) |
		(ddr3_conf.t_xsr << 16) |
		(ddr3_conf.t_xp  <<  8) |
		(ddr3_conf.t_cke <<  4) |
		(ddr3_conf.t_mrd <<  0);
	nx_drex->wr_lvl_config[0] |= (1 << 5);
	nx_drex->mem_control =
		(3 << 20) |
		(0 << 16) |
		(2 << 12) |
		(6 <<  8) |
		(0 <<  6);
	nx_drex->phy_control[0] |=  (1 << 3);
	nx_drex->phy_control[0] &= ~(1 << 3);

	/* 1.13 */
	/* TODO */

	/* 1.14 */
	delay_us(500);

	/* 1.15 */
	delay_us(0);

	/* 1.16 */
	send_ddr3_direct_cmd(DDR3_CMD_NOP, 0, 0, 0);

	/* 1.17 */
	delay_us(10);

	/* 1.18 */
	send_ddr3_direct_cmd(DDR3_CMD_MRS, 0, 2, ((ddr3_conf.cwl - 5) << 3));

	/* 1.19 */
	send_ddr3_direct_cmd(DDR3_CMD_MRS, 0, 3, 0);

	/* 1.20 */
	send_ddr3_direct_cmd(DDR3_CMD_MRS, 0, 1,
		(0x11 << 2) |
		(((ddr3_conf.al == 0) ? 0 : (ddr3_conf.al == ddr3_conf.cl - 1) ? 1 : 2) << 3) |
		(   1 << 1)
	);

	/* 1.21 */
	send_ddr3_direct_cmd(DDR3_CMD_MRS, 0, 0, 
		(1 <<  8) |
		(1 << 12) |
		((ddr3_conf.wr < 10 ? ddr3_conf.wr - 4 : ddr3_conf.wr / 2) << 9) |
		(((((ddr3_conf.cl - 4) & 0x7) << 2) | (((ddr3_conf.cl - 4) & 0x8) >> 3)) << 2)
	);
	delay_us(10);

	/* 1.22 */
	send_ddr3_direct_cmd(DDR3_CMD_MRS, 0, 0, 
		(1 << 12) |
		((ddr3_conf.wr < 10 ? ddr3_conf.wr - 4 : ddr3_conf.wr / 2) << 9) |
		(((((ddr3_conf.cl - 4) & 0x7) << 2) | (((ddr3_conf.cl - 4) & 0x8) >> 3)) << 2)
	);

	/* 1.23 */
	send_ddr3_direct_cmd(DDR3_CMD_ZQINIT, 0, 0, 0);

	/* 1.24 */

	/* 1.25 */
	/* 2.9 */
	nx_ddrphy->offset_d_con[0] &= ~(1 << 28);
	nx_ddrphy->phy_con[0] |= (1 <<  6);
	nx_ddrphy->phy_con[0] |= (1 << 14);
	nx_ddrphy->phy_con[2] |= (1 <<  6);
	nx_ddrphy->phy_con[0] |= (1 << 13);
	nx_ddrphy->phy_con[1] = (nx_ddrphy->phy_con[1] & ~(0xF << 16)) | (4 << 16);
	nx_ddrphy->lp_ddr_con[3] = (nx_ddrphy->lp_ddr_con[3] & ~0x1FFF) | 0x105E;
	nx_ddrphy->lp_ddr_con[4] = (nx_ddrphy->lp_ddr_con[4] & ~0x1FFF) | 0x107F;
	nx_ddrphy->phy_con[2] = (nx_ddrphy->phy_con[2] & ~(0x3F << 16)) | (1 << 16);
	nx_ddrphy->mdll_con[0] |=  (1 << 5);
	while ((nx_ddrphy->mdll_con[1] & 0x7) != 0x7);
	nx_ddrphy->mdll_con[0] &= ~(1 << 5);
	nx_ddrphy->mdll_con[0] = (nx_ddrphy->mdll_con[0] & ~(0x1FF << 7)) | ((nx_ddrphy->mdll_con[1] & 0x1FF0) >> 1);

	/* 1.26 */
	/* H/W Write Leveling */
	if (ddr3_conf.write_leveling)
		do_ddr3_hw_write_leveling();
	/* CA Calibration */

	/* 1.27 */
	/* Gate Leveling */
	if (ddr3_conf.gate_leveling)
		do_ddr3_gate_leveling();

	/* 1.28 */

	/* 1.29 */
	/* Read Leveling */

	/* 1.30 */
	if (ddr3_conf.read_leveling)
		do_ddr3_read_leveling();

	/* 1.31 */
	/* Write Latency Calibration */
	if (ddr3_conf.write_latency_calibration)
		do_ddr3_write_latency_calibration();
	/* Write DQ Calibration */

	/* 1.32 */
	if (ddr3_conf.write_dq_calibration)
		do_ddr3_write_dq_calibration();

	/* 2.10 */
	nx_ddrphy->offset_d_con[0] |=  (1 << 24);
	nx_ddrphy->offset_d_con[0] &= ~(1 << 24);
	nx_ddrphy->phy_con[0] &= ~((1 << 14) | (1 << 13));
	nx_ddrphy->mdll_con[0] |= (1 << 5);
	nx_ddrphy->phy_con[2] |= (1 << 12);
	/* 2.11 */

	/* 1.33 */
	nx_drex->phy_control[0] |=  (1 << 3);

	/* 1.34 */
	nx_drex->phy_control[0] &= ~(1 << 3);

	/* 1.35 */
	nx_ddrphy->phy_con[0] &= ~(1 << 6);

	/* 1.36 */
	send_ddr3_direct_cmd(DDR3_CMD_PALL, 0, 0, 0);

	/* 1.37 */
	nx_drex->phy_control[0] = \
		(1 << 31) |
		(1 << 30) |
		(1 << 29) |
		(0 <<  4);

	/* 1.38 */
	nx_drex->con_control = \
		(0xFFF << 16) |
		(    1 << 12) |
		(    1 <<  6) |
		(    1 <<  5);

	/* 1.39 */
	nx_drex->cg_control = \
		(1 << 3) |
		(1 << 2) |
		(1 << 1) |
		(1 << 0);

	debug(DEBUG_LEVEL_INFO, "DDR3 has been initialized\n");
	debug(DEBUG_LEVEL_INFO, "DDR3 base addr = %#010x, size = %#010x\n", ddr3_conf.addr_base, ddr3_conf.size);
}

static uint64_t const mem_test_seq[] = {
	0x0000000000000000ULL,
	0xAAAAAAAAAAAAAAAAULL,
	0x5555555555555555ULL,
	0xCCCCCCCCCCCCCCCCULL,
	0x6666666666666666ULL,
	0x4444444444444444ULL,
	0x9999999999999999ULL,
	0xF0F0F0F0F0F0F0F0ULL,
	0x7878787878787878ULL,
	0x3C3C3C3C3C3C3C3CULL,
	0x1E1E1E1E1E1E1E1EULL,
	0x0F0F0F0F0F0F0F0FULL,
	0x8787878787878787ULL,
	0xC3C3C3C3C3C3C3C3ULL,
	0xE1E1E1E1E1E1E1E1ULL,
	0xFFFFFFFFFFFFFFFFULL,
};

void test_ddr3(void)
{
	uint64_t cur_addr;
	uint32_t cur_seq;
	
	printf("\n");
	printf("Memory Test Starts\n");
	printf("\n");
	
	for (cur_addr = PI_MEM_TEST_START_ADDR, cur_seq = 0; cur_addr < PI_MEM_TEST_END_ADDR; cur_addr += 8, cur_seq = (cur_seq + 1) & 0xF) {
		ref64(cur_addr) = mem_test_seq[cur_seq];
		if (!(cur_addr & 0xFFFF))
			printf("\rWriting data at %#010llx", cur_addr);
	}
	
	printf("\rNow checking data at %#010llx\n", PI_MEM_TEST_START_ADDR);
	
	for (cur_addr = PI_MEM_TEST_START_ADDR, cur_seq = 0; cur_addr < PI_MEM_TEST_END_ADDR; cur_addr += 8, cur_seq = (cur_seq + 1) & 0xF) {
		if (ref64(cur_addr) != mem_test_seq[cur_seq]) {
			printf("\nData check is failed at %#010llx\n", cur_addr);
			return;
		}
		if (!(cur_addr & 0xFFFF))
			printf("\rReading data at %#010llx", cur_addr);
	}
	
	printf("\rData check is OK at %#010llx\n", PI_MEM_TEST_START_ADDR);
}
