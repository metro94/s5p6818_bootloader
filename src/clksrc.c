/*
 * Copyright (C) 2017
 * Author: metro94 <flattiles@gmail.com>
 *
 * Version: v1.0
 * --- Update time: 02/07/2017
 * --- Description: First build; code for Clock Source Control
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

#include <clksrc.h>

int  get_pll_freq(int pll_src)
{
	return (int)((uint64_t)PI_OSC_FREQ	\
		/ get_pll_pdiv(pll_src)		\
		* get_pll_mdiv(pll_src)		\
		/ (1 << get_pll_sdiv(pll_src)));
}

void set_pll_freq(int pll_src, int target_freq)
{
	if (target_freq > 1000000000 /* 1GHz */) {
		set_pll_pdiv(pll_src, 3);
		set_pll_mdiv(pll_src, round((double)target_freq / (PI_OSC_FREQ / 3)));
		set_pll_sdiv(pll_src, 0);
	} else if (target_freq > 500000000 /* 500MHz */) {
		set_pll_pdiv(pll_src, 3);
		set_pll_mdiv(pll_src, round((double)target_freq / (PI_OSC_FREQ / 6)));
		set_pll_sdiv(pll_src, 1);
	} else if (target_freq > 250000000 /* 250MHz */) {
		set_pll_pdiv(pll_src, 3);
		set_pll_mdiv(pll_src, round((double)target_freq / (PI_OSC_FREQ / 12)));
		set_pll_sdiv(pll_src, 2);
	} else {
		set_pll_pdiv(pll_src, 3);
		set_pll_mdiv(pll_src, round((double)target_freq / (PI_OSC_FREQ / 24)));
		set_pll_sdiv(pll_src, 3);
	}
}

void update_pll_all(void)
{
	nx_sysctrl->clk_mode[0] |=  (0xF << 0);
	nx_sysctrl->clk_mode[0] &= ~(0xF << 0);
	
	nx_sysctrl->pwr_mode |= (1 << 15);
	while (nx_sysctrl->pwr_mode & (1 << 15));
}

void init_clock(void)
{
	set_pll_freq(0, PI_PLL_0_FREQ);
	set_pll_power(0, 1);
	set_pll_sscg(0, 0);

	set_pll_freq(1, PI_PLL_1_FREQ);
	set_pll_power(1, 1);
	set_pll_sscg(1, 0);

	set_pll_freq(2, PI_PLL_2_FREQ);
	set_pll_power(2, 1);
	set_pll_sscg(2, 0);

	set_pll_freq(3, PI_PLL_3_FREQ);
	set_pll_power(3, 0);
	set_pll_sscg(3, 0);
	
	set_cpu_cluster_0_fclk_src(0);
	set_cpu_cluster_0_fclk_freq(PI_CPU_CLUSTER_0_FCLK_FREQ);
	set_cpu_cluster_0_hclk_freq(PI_CPU_CLUSTER_0_HCLK_FREQ);

	set_cpu_cluster_1_fclk_src(0);
	set_cpu_cluster_1_fclk_freq(PI_CPU_CLUSTER_1_FCLK_FREQ);
	set_cpu_cluster_1_hclk_freq(PI_CPU_CLUSTER_1_HCLK_FREQ);

	set_bclk_src(2);
	set_bclk_freq(PI_BCLK_FREQ);
	set_pclk_freq(PI_PCLK_FREQ);

	set_mdclk_src(1);
	set_mdclk_freq(PI_MDCLK_FREQ);
	set_mclk_freq(PI_MCLK_FREQ);
	set_mbclk_freq(PI_MBCLK_FREQ);
	set_mpclk_freq(PI_MPCLK_FREQ);

	set_gr3d_bclk_src(2);
	set_gr3d_bclk_freq(PI_GR3D_BCLK_FREQ);
	set_gr3d_pclk_freq(PI_GR3D_PCLK_FREQ);

	set_mpeg_bclk_src(2);
	set_mpeg_bclk_freq(PI_MPEG_BCLK_FREQ);
	set_mpeg_pclk_freq(PI_MPEG_PCLK_FREQ);

	set_disp_bclk_src(2);
	set_disp_bclk_freq(PI_DISP_BCLK_FREQ);
	set_disp_pclk_freq(PI_DISP_PCLK_FREQ);

	set_hdmi_pclk_src(2);
	set_hdmi_pclk_freq(PI_HDMI_PCLK_FREQ);

	set_fast_bclk_src(2);
	set_fast_bclk_freq(PI_FAST_BCLK_FREQ);

	update_pll_all();
}

void disp_clock_info(void)
{
	printf("---------------------------\n");
	printf("|   Clock   |  Frequency  |\n");
	printf("| %-9s | %10d  |\n", "PLL0", get_pll_freq(0));
	printf("| %-9s | %10d  |\n", "PLL1", get_pll_freq(1));
	printf("| %-9s | %10d  |\n", "PLL2", get_pll_freq(2));
	printf("| %-9s | %10d  |\n", "PLL3", get_pll_freq(3));
	printf("| %-9s | %10d  |\n", "CPU0 FCLK", get_cpu_cluster_0_fclk_freq());
	printf("| %-9s | %10d  |\n", "CPU0 HCLK", get_cpu_cluster_0_hclk_freq());
	printf("| %-9s | %10d  |\n", "CPU1 FCLK", get_cpu_cluster_1_fclk_freq());
	printf("| %-9s | %10d  |\n", "CPU1 HCLK", get_cpu_cluster_1_hclk_freq());
	printf("| %-9s | %10d  |\n", "BCLK", get_bclk_freq());
	printf("| %-9s | %10d  |\n", "PCLK", get_pclk_freq());
	printf("| %-9s | %10d  |\n", "MDCLK", get_mdclk_freq());
	printf("| %-9s | %10d  |\n", "MCLK", get_mclk_freq());
	printf("| %-9s | %10d  |\n", "MBCLK", get_mbclk_freq());
	printf("| %-9s | %10d  |\n", "MPCLK", get_mpclk_freq());
	printf("| %-9s | %10d  |\n", "GR3D BCLK", get_gr3d_bclk_freq());
	printf("| %-9s | %10d  |\n", "GR3D PCLK", get_gr3d_pclk_freq());
	printf("| %-9s | %10d  |\n", "MPEG BCLK", get_mpeg_bclk_freq());
	printf("| %-9s | %10d  |\n", "MPEG PCLK", get_mpeg_pclk_freq());
	printf("| %-9s | %10d  |\n", "DISP BCLK", get_disp_bclk_freq());
	printf("| %-9s | %10d  |\n", "DISP PCLK", get_disp_pclk_freq());
	printf("| %-9s | %10d  |\n", "HDMI PCLK", get_hdmi_pclk_freq());
	printf("| %-9s | %10d  |\n", "FAST BCLK", get_fast_bclk_freq());
	printf("---------------------------\n");
}
