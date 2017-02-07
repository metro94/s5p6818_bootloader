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

#ifndef __CLKSRC_H__
#define __CLKSRC_H__

#include <common.h>
#include <std/math.h>
#include <std/printf.h>

#include <nexell/nx_sysctrl.h>

int  get_pll_freq(int);
void set_pll_freq(int, int);

void update_pll_all(void);

void init_clock(void);
void disp_clock_info(void);

static inline int  get_pll_power(int pll_src) __attribute__((always_inline));
static inline int  get_pll_sscg(int pll_src) __attribute__((always_inline));
static inline int  get_pll_pdiv(int pll_src) __attribute__((always_inline));
static inline int  get_pll_mdiv(int pll_src) __attribute__((always_inline));
static inline int  get_pll_sdiv(int pll_src) __attribute__((always_inline));
static inline void set_pll_power(int pll_src, int power_on) __attribute__((always_inline));
static inline void set_pll_sscg(int pll_src, int sscg_on) __attribute__((always_inline));
static inline void set_pll_pdiv(int pll_src, int pdiv) __attribute__((always_inline));
static inline void set_pll_mdiv(int pll_src, int mdiv) __attribute__((always_inline));
static inline void set_pll_sdiv(int pll_src, int sdiv) __attribute__((always_inline));
static inline int  get_cpu_cluster_0_fclk_src(void) __attribute__((always_inline));
static inline int  get_cpu_cluster_0_fclk_div(void) __attribute__((always_inline));
static inline int  get_cpu_cluster_0_hclk_div(void) __attribute__((always_inline));
static inline int  get_cpu_cluster_1_fclk_src(void) __attribute__((always_inline));
static inline int  get_cpu_cluster_1_fclk_div(void) __attribute__((always_inline));
static inline int  get_cpu_cluster_1_hclk_div(void) __attribute__((always_inline));
static inline int  get_bclk_src(void) __attribute__((always_inline));
static inline int  get_bclk_div(void) __attribute__((always_inline));
static inline int  get_pclk_div(void) __attribute__((always_inline));
static inline int  get_mdclk_src(void) __attribute__((always_inline));
static inline int  get_mdclk_div(void) __attribute__((always_inline));
static inline int  get_mclk_div(void) __attribute__((always_inline));
static inline int  get_mbclk_div(void) __attribute__((always_inline));
static inline int  get_mpclk_div(void) __attribute__((always_inline));
static inline int  get_gr3d_bclk_src(void) __attribute__((always_inline));
static inline int  get_gr3d_bclk_div(void) __attribute__((always_inline));
static inline int  get_gr3d_pclk_div(void) __attribute__((always_inline));
static inline int  get_mpeg_bclk_src(void) __attribute__((always_inline));
static inline int  get_mpeg_bclk_div(void) __attribute__((always_inline));
static inline int  get_mpeg_pclk_div(void) __attribute__((always_inline));
static inline int  get_disp_bclk_src(void) __attribute__((always_inline));
static inline int  get_disp_bclk_div(void) __attribute__((always_inline));
static inline int  get_disp_pclk_div(void) __attribute__((always_inline));
static inline int  get_hdmi_pclk_src(void) __attribute__((always_inline));
static inline int  get_hdmi_pclk_div(void) __attribute__((always_inline));
static inline int  get_fast_bclk_src(void) __attribute__((always_inline));
static inline int  get_fast_bclk_div(void) __attribute__((always_inline));
static inline void set_cpu_cluster_0_fclk_src(int src) __attribute__((always_inline));
static inline void set_cpu_cluster_0_fclk_div(int div) __attribute__((always_inline));
static inline void set_cpu_cluster_0_hclk_div(int div) __attribute__((always_inline));
static inline void set_cpu_cluster_1_fclk_src(int src) __attribute__((always_inline));
static inline void set_cpu_cluster_1_fclk_div(int div) __attribute__((always_inline));
static inline void set_cpu_cluster_1_hclk_div(int div) __attribute__((always_inline));
static inline void set_bclk_src(int src) __attribute__((always_inline));
static inline void set_bclk_div(int div) __attribute__((always_inline));
static inline void set_pclk_div(int div) __attribute__((always_inline));
static inline void set_mdclk_src(int src) __attribute__((always_inline));
static inline void set_mdclk_div(int div) __attribute__((always_inline));
static inline void set_mclk_div(int div) __attribute__((always_inline));
static inline void set_mbclk_div(int div) __attribute__((always_inline));
static inline void set_mpclk_div(int div) __attribute__((always_inline));
static inline void set_gr3d_bclk_src(int src) __attribute__((always_inline));
static inline void set_gr3d_bclk_div(int div) __attribute__((always_inline));
static inline void set_gr3d_pclk_div(int div) __attribute__((always_inline));
static inline void set_mpeg_bclk_src(int src) __attribute__((always_inline));
static inline void set_mpeg_bclk_div(int div) __attribute__((always_inline));
static inline void set_mpeg_pclk_div(int div) __attribute__((always_inline));
static inline void set_disp_bclk_src(int src) __attribute__((always_inline));
static inline void set_disp_bclk_div(int div) __attribute__((always_inline));
static inline void set_disp_pclk_div(int div) __attribute__((always_inline));
static inline void set_hdmi_pclk_src(int src) __attribute__((always_inline));
static inline void set_hdmi_pclk_div(int div) __attribute__((always_inline));
static inline void set_fast_bclk_src(int src) __attribute__((always_inline));
static inline void set_fast_bclk_div(int div) __attribute__((always_inline));
static inline int  get_cpu_cluster_0_fclk_freq(void) __attribute__((always_inline));
static inline int  get_cpu_cluster_0_hclk_freq(void) __attribute__((always_inline));
static inline int  get_cpu_cluster_1_fclk_freq(void) __attribute__((always_inline));
static inline int  get_cpu_cluster_1_hclk_freq(void) __attribute__((always_inline));
static inline int  get_bclk_freq(void) __attribute__((always_inline));
static inline int  get_pclk_freq(void) __attribute__((always_inline));
static inline int  get_mdclk_freq(void) __attribute__((always_inline));
static inline int  get_mclk_freq(void) __attribute__((always_inline));
static inline int  get_mbclk_freq(void) __attribute__((always_inline));
static inline int  get_mpclk_freq(void) __attribute__((always_inline));
static inline int  get_gr3d_bclk_freq(void) __attribute__((always_inline));
static inline int  get_gr3d_pclk_freq(void) __attribute__((always_inline));
static inline int  get_mpeg_bclk_freq(void) __attribute__((always_inline));
static inline int  get_mpeg_pclk_freq(void) __attribute__((always_inline));
static inline int  get_disp_bclk_freq(void) __attribute__((always_inline));
static inline int  get_disp_pclk_freq(void) __attribute__((always_inline));
static inline int  get_hdmi_pclk_freq(void) __attribute__((always_inline));
static inline int  get_fast_bclk_freq(void) __attribute__((always_inline));
static inline void set_cpu_cluster_0_fclk_freq(int target_freq) __attribute__((always_inline));
static inline void set_cpu_cluster_0_hclk_freq(int target_freq) __attribute__((always_inline));
static inline void set_cpu_cluster_1_fclk_freq(int target_freq) __attribute__((always_inline));
static inline void set_cpu_cluster_1_hclk_freq(int target_freq) __attribute__((always_inline));
static inline void set_bclk_freq(int target_freq) __attribute__((always_inline));
static inline void set_pclk_freq(int target_freq) __attribute__((always_inline));
static inline void set_mdclk_freq(int target_freq) __attribute__((always_inline));
static inline void set_mclk_freq(int target_freq) __attribute__((always_inline));
static inline void set_mbclk_freq(int target_freq) __attribute__((always_inline));
static inline void set_mpclk_freq(int target_freq) __attribute__((always_inline));
static inline void set_gr3d_bclk_freq(int target_freq) __attribute__((always_inline));
static inline void set_gr3d_pclk_freq(int target_freq) __attribute__((always_inline));
static inline void set_mpeg_bclk_freq(int target_freq) __attribute__((always_inline));
static inline void set_mpeg_pclk_freq(int target_freq) __attribute__((always_inline));
static inline void set_disp_bclk_freq(int target_freq) __attribute__((always_inline));
static inline void set_disp_pclk_freq(int target_freq) __attribute__((always_inline));
static inline void set_hdmi_pclk_freq(int target_freq) __attribute__((always_inline));
static inline void set_fast_bclk_freq(int target_freq) __attribute__((always_inline));

static inline int  get_pll_power(int pll_src)
{
	return (nx_sysctrl->pll_set[pll_src] & (1 << 29)) ? 0 : 1;
}

static inline int  get_pll_sscg(int pll_src)
{
	return (nx_sysctrl->pll_set[pll_src] & (1 << 30)) ? 1 : 0;
}

static inline int  get_pll_pdiv(int pll_src)
{
	return (nx_sysctrl->pll_set[pll_src] >> 18) & 0x3F;
}

static inline int  get_pll_mdiv(int pll_src)
{
	return (nx_sysctrl->pll_set[pll_src] >>  8) & 0x3FF;
}

static inline int  get_pll_sdiv(int pll_src)
{
	return (nx_sysctrl->pll_set[pll_src] >>  0) & 0xFF;
}

static inline void set_pll_power(int pll_src, int power_on)
{
	if (power_on)
		nx_sysctrl->pll_set[pll_src] &= ~(1 << 29);
	else
		nx_sysctrl->pll_set[pll_src] |=  (1 << 29);
}

static inline void set_pll_sscg(int pll_src, int sscg_on)
{
	if (sscg_on)
		nx_sysctrl->pll_set[pll_src] |=  (1 << 30);
	else
		nx_sysctrl->pll_set[pll_src] &= ~(1 << 30);
}

static inline void set_pll_pdiv(int pll_src, int pdiv)
{
	nx_sysctrl->pll_set[pll_src] = (nx_sysctrl->pll_set[pll_src]	\
					& ~(0x3F << 18))		\
					| (pdiv << 18);
}

static inline void set_pll_mdiv(int pll_src, int mdiv)
{
	nx_sysctrl->pll_set[pll_src] = (nx_sysctrl->pll_set[pll_src]	\
					& ~(0x3FF << 8))		\
					| (mdiv << 8);
}

static inline void set_pll_sdiv(int pll_src, int sdiv)
{
	nx_sysctrl->pll_set[pll_src] = (nx_sysctrl->pll_set[pll_src]	\
					& ~(0xFF << 0))			\
					| (sdiv << 0);
}

static inline int  get_cpu_cluster_0_fclk_src(void)
{
	return (nx_sysctrl->clk_div[0] >> 0) & 0x7;
}

static inline int  get_cpu_cluster_0_fclk_div(void)
{
	return ((nx_sysctrl->clk_div[0] >> 3) & 0x3F) + 1;
}

static inline int  get_cpu_cluster_0_hclk_div(void)
{
	return ((nx_sysctrl->clk_div[0] >> 9) & 0x3F) + 1;
}

static inline int  get_cpu_cluster_1_fclk_src(void)
{
	return (nx_sysctrl->clk_div[7] >> 0) & 0x7;
}

static inline int  get_cpu_cluster_1_fclk_div(void)
{
	return ((nx_sysctrl->clk_div[7] >> 3) & 0x3F) + 1;
}

static inline int  get_cpu_cluster_1_hclk_div(void)
{
	return ((nx_sysctrl->clk_div[7] >> 9) & 0x3F) + 1;
}

static inline int  get_bclk_src(void)
{
	return (nx_sysctrl->clk_div[1] >> 0) & 0x7;
}

static inline int  get_bclk_div(void)
{
	return ((nx_sysctrl->clk_div[1] >> 3) & 0x3F) + 1;
}

static inline int  get_pclk_div(void)
{
	return ((nx_sysctrl->clk_div[1] >> 9) & 0x3F) + 1;
}

static inline int  get_mdclk_src(void)
{
	return (nx_sysctrl->clk_div[2] >> 0) & 0x7;
}

static inline int  get_mdclk_div(void)
{
	return ((nx_sysctrl->clk_div[2] >> 3) & 0x3F) + 1;
}

static inline int  get_mclk_div(void)
{
	return ((nx_sysctrl->clk_div[2] >> 9) & 0x3F) + 1;
}

static inline int  get_mbclk_div(void)
{
	return ((nx_sysctrl->clk_div[2] >> 15) & 0x3F) + 1;
}

static inline int  get_mpclk_div(void)
{
	return ((nx_sysctrl->clk_div[8] >> 9) & 0x3F) + 1;
}

static inline int  get_gr3d_bclk_src(void)
{
	return (nx_sysctrl->clk_div[3] >> 0) & 0x7;
}

static inline int  get_gr3d_bclk_div(void)
{
	return ((nx_sysctrl->clk_div[3] >> 3) & 0x3F) + 1;
}

static inline int  get_gr3d_pclk_div(void)
{
	return ((nx_sysctrl->clk_div[3] >> 9) & 0x3F) + 1;
}

static inline int  get_mpeg_bclk_src(void)
{
	return (nx_sysctrl->clk_div[4] >> 0) & 0x7;
}

static inline int  get_mpeg_bclk_div(void)
{
	return ((nx_sysctrl->clk_div[4] >> 3) & 0x3F) + 1;
}

static inline int  get_mpeg_pclk_div(void)
{
	return ((nx_sysctrl->clk_div[4] >> 9) & 0x3F) + 1;
}

static inline int  get_disp_bclk_src(void)
{
	return (nx_sysctrl->clk_div[5] >> 0) & 0x7;
}

static inline int  get_disp_bclk_div(void)
{
	return ((nx_sysctrl->clk_div[5] >> 3) & 0x3F) + 1;
}

static inline int  get_disp_pclk_div(void)
{
	return ((nx_sysctrl->clk_div[5] >> 9) & 0x3F) + 1;
}

static inline int  get_hdmi_pclk_src(void)
{
	return (nx_sysctrl->clk_div[6] >> 0) & 0x7;
}

static inline int  get_hdmi_pclk_div(void)
{
	return ((nx_sysctrl->clk_div[6] >> 3) & 0x3F) + 1;
}

static inline int  get_fast_bclk_src(void)
{
	return (nx_sysctrl->clk_div[8] >> 0) & 0x7;
}

static inline int  get_fast_bclk_div(void)
{
	return ((nx_sysctrl->clk_div[8] >> 3) & 0x3F) + 1;
}

static inline void set_cpu_cluster_0_fclk_src(int src)
{
	nx_sysctrl->clk_div[0] = (nx_sysctrl->clk_div[0]	\
					& ~(0x7 << 0))		\
					| (src << 0);
}

static inline void set_cpu_cluster_0_fclk_div(int div)
{
	nx_sysctrl->clk_div[0] = (nx_sysctrl->clk_div[0]	\
					& ~(0x3F << 3))		\
					| ((div - 1) << 3);
}

static inline void set_cpu_cluster_0_hclk_div(int div)
{
	nx_sysctrl->clk_div[0] = (nx_sysctrl->clk_div[0]	\
					& ~(0x3F << 9))		\
					| ((div - 1) << 9);
}

static inline void set_cpu_cluster_1_fclk_src(int src)
{
	nx_sysctrl->clk_div[7] = (nx_sysctrl->clk_div[7]	\
					& ~(0x7 << 0))		\
					| (src << 0);
}

static inline void set_cpu_cluster_1_fclk_div(int div)
{
	nx_sysctrl->clk_div[7] = (nx_sysctrl->clk_div[7]	\
					& ~(0x3F << 3))		\
					| ((div - 1) << 3);
}

static inline void set_cpu_cluster_1_hclk_div(int div)
{
	nx_sysctrl->clk_div[7] = (nx_sysctrl->clk_div[7]	\
					& ~(0x3F << 9))		\
					| ((div - 1) << 9);
}

static inline void set_bclk_src(int src)
{
	nx_sysctrl->clk_div[1] = (nx_sysctrl->clk_div[1]	\
					& ~(0x7 << 0))		\
					| (src << 0);
}

static inline void set_bclk_div(int div)
{
	nx_sysctrl->clk_div[1] = (nx_sysctrl->clk_div[1]	\
					& ~(0x3F << 3))		\
					| ((div - 1) << 3);
}

static inline void set_pclk_div(int div)
{
	nx_sysctrl->clk_div[1] = (nx_sysctrl->clk_div[1]	\
					& ~(0x3F << 9))		\
					| ((div - 1) << 9);
}

static inline void set_mdclk_src(int src)
{
	nx_sysctrl->clk_div[2] = (nx_sysctrl->clk_div[2]	\
					& ~(0x7 << 0))		\
					| (src << 0);
}

static inline void set_mdclk_div(int div)
{
	nx_sysctrl->clk_div[2] = (nx_sysctrl->clk_div[2]	\
					& ~(0x3F << 3))		\
					| ((div - 1) << 3);
}

static inline void set_mclk_div(int div)
{
	nx_sysctrl->clk_div[2] = (nx_sysctrl->clk_div[2]	\
					& ~(0x3F << 9))		\
					| ((div - 1) << 9);
}

static inline void set_mbclk_div(int div)
{
	nx_sysctrl->clk_div[2] = (nx_sysctrl->clk_div[2]	\
					& ~(0x3F << 15))	\
					| ((div - 1) << 15);
}

static inline void set_mpclk_div(int div)
{
	nx_sysctrl->clk_div[8] = (nx_sysctrl->clk_div[8]	\
					& ~(0x3F << 9))		\
					| ((div - 1) << 9);
}

static inline void set_gr3d_bclk_src(int src)
{
	nx_sysctrl->clk_div[3] = (nx_sysctrl->clk_div[3]	\
					& ~(0x7 << 0))		\
					| (src << 0);
}

static inline void set_gr3d_bclk_div(int div)
{
	nx_sysctrl->clk_div[3] = (nx_sysctrl->clk_div[3]	\
					& ~(0x3F << 3))		\
					| ((div - 1) << 3);
}

static inline void set_gr3d_pclk_div(int div)
{
	nx_sysctrl->clk_div[3] = (nx_sysctrl->clk_div[3]	\
					& ~(0x3F << 9))		\
					| ((div - 1) << 9);
}

static inline void set_mpeg_bclk_src(int src)
{
	nx_sysctrl->clk_div[4] = (nx_sysctrl->clk_div[4]	\
					& ~(0x7 << 0))		\
					| (src << 0);
}

static inline void set_mpeg_bclk_div(int div)
{
	nx_sysctrl->clk_div[4] = (nx_sysctrl->clk_div[4]	\
					& ~(0x3F << 3))		\
					| ((div - 1) << 3);
}

static inline void set_mpeg_pclk_div(int div)
{
	nx_sysctrl->clk_div[4] = (nx_sysctrl->clk_div[4]	\
					& ~(0x3F << 9))		\
					| ((div - 1) << 9);
}

static inline void set_disp_bclk_src(int src)
{
	nx_sysctrl->clk_div[5] = (nx_sysctrl->clk_div[5]	\
					& ~(0x7 << 0))		\
					| (src << 0);
}

static inline void set_disp_bclk_div(int div)
{
	nx_sysctrl->clk_div[5] = (nx_sysctrl->clk_div[5]	\
					& ~(0x3F << 3))		\
					| ((div - 1) << 3);
}

static inline void set_disp_pclk_div(int div)
{
	nx_sysctrl->clk_div[5] = (nx_sysctrl->clk_div[5]	\
					& ~(0x3F << 9))		\
					| ((div - 1) << 9);
}

static inline void set_hdmi_pclk_src(int src)
{
	nx_sysctrl->clk_div[6] = (nx_sysctrl->clk_div[6]	\
					& ~(0x7 << 0))		\
					| (src << 0);
}

static inline void set_hdmi_pclk_div(int div)
{
	nx_sysctrl->clk_div[6] = (nx_sysctrl->clk_div[6]	\
					& ~(0x3F << 3))		\
					| ((div - 1) << 3);
}

static inline void set_fast_bclk_src(int src)
{
	nx_sysctrl->clk_div[8] = (nx_sysctrl->clk_div[8]	\
					& ~(0x7 << 0))		\
					| (src << 0);
}

static inline void set_fast_bclk_div(int div)
{
	nx_sysctrl->clk_div[8] = (nx_sysctrl->clk_div[8]	\
					& ~(0x3F << 3))		\
					| ((div - 1) << 3);
}

static inline int  get_cpu_cluster_0_fclk_freq(void)
{
	return get_pll_freq(get_cpu_cluster_0_fclk_src()) / get_cpu_cluster_0_fclk_div();
}

static inline int  get_cpu_cluster_0_hclk_freq(void)
{
	return get_cpu_cluster_0_fclk_freq() / get_cpu_cluster_0_hclk_div();
}

static inline int  get_cpu_cluster_1_fclk_freq(void)
{
	return get_pll_freq(get_cpu_cluster_1_fclk_src()) / get_cpu_cluster_1_fclk_div();
}

static inline int  get_cpu_cluster_1_hclk_freq(void)
{
	return get_cpu_cluster_1_fclk_freq() / get_cpu_cluster_1_hclk_div();
}

static inline int  get_bclk_freq(void)
{
	return get_pll_freq(get_bclk_src()) / get_bclk_div();
}

static inline int  get_pclk_freq(void)
{
	return get_bclk_freq() / get_pclk_div();
}

static inline int  get_mdclk_freq(void)
{
	return get_pll_freq(get_mdclk_src()) / get_mdclk_div();
}

static inline int  get_mclk_freq(void)
{
	return get_mdclk_freq() / get_mclk_div();
}

static inline int  get_mbclk_freq(void)
{
	return get_mclk_freq() / get_mbclk_div();
}

static inline int  get_mpclk_freq(void)
{
	return get_mbclk_freq() / get_mpclk_div();
}

static inline int  get_gr3d_bclk_freq(void)
{
	return get_pll_freq(get_gr3d_bclk_src()) / get_gr3d_bclk_div();
}

static inline int  get_gr3d_pclk_freq(void)
{
	return get_gr3d_bclk_freq() / get_gr3d_pclk_div();
}

static inline int  get_mpeg_bclk_freq(void)
{
	return get_pll_freq(get_mpeg_bclk_src()) / get_mpeg_bclk_div();
}

static inline int  get_mpeg_pclk_freq(void)
{
	return get_mpeg_bclk_freq() / get_mpeg_pclk_div();
}

static inline int  get_disp_bclk_freq(void)
{
	return get_pll_freq(get_disp_bclk_src()) / get_disp_bclk_div();
}

static inline int  get_disp_pclk_freq(void)
{
	return get_disp_bclk_freq() / get_disp_pclk_div();
}

static inline int  get_hdmi_pclk_freq(void)
{
	return get_pll_freq(get_hdmi_pclk_src()) / get_hdmi_pclk_div();
}

static inline int  get_fast_bclk_freq(void)
{
	return get_pll_freq(get_fast_bclk_src()) / get_fast_bclk_div();
}

static inline void set_cpu_cluster_0_fclk_freq(int target_freq)
{
	set_cpu_cluster_0_fclk_div(round((double)get_pll_freq(get_cpu_cluster_0_fclk_src()) / target_freq));
}

static inline void set_cpu_cluster_0_hclk_freq(int target_freq)
{
	set_cpu_cluster_0_hclk_div(round((double)get_cpu_cluster_0_fclk_freq() / target_freq));
}

static inline void set_cpu_cluster_1_fclk_freq(int target_freq)
{
	set_cpu_cluster_1_fclk_div(round((double)get_pll_freq(get_cpu_cluster_1_fclk_src()) / target_freq));
}

static inline void set_cpu_cluster_1_hclk_freq(int target_freq)
{
	set_cpu_cluster_1_hclk_div(round((double)get_cpu_cluster_1_fclk_freq() / target_freq));
}

static inline void set_bclk_freq(int target_freq)
{
	set_bclk_div(round((double)get_pll_freq(get_bclk_src()) / target_freq));
}

static inline void set_pclk_freq(int target_freq)
{
	set_pclk_div(round((double)get_bclk_freq() / target_freq));
}

static inline void set_mdclk_freq(int target_freq)
{
	set_mdclk_div(round((double)get_pll_freq(get_mdclk_src()) / target_freq));
}

static inline void set_mclk_freq(int target_freq)
{
	set_mclk_div(round((double)get_mdclk_freq() / target_freq));
}

static inline void set_mbclk_freq(int target_freq)
{
	set_mbclk_div(round((double)get_mclk_freq() / target_freq));
}

static inline void set_mpclk_freq(int target_freq)
{
	set_mpclk_div(round((double)get_mbclk_freq() / target_freq));
}

static inline void set_gr3d_bclk_freq(int target_freq)
{
	set_gr3d_bclk_div(round((double)get_pll_freq(get_gr3d_bclk_src()) / target_freq));
}

static inline void set_gr3d_pclk_freq(int target_freq)
{
	set_gr3d_pclk_div(round((double)get_gr3d_bclk_freq() / target_freq));
}

static inline void set_mpeg_bclk_freq(int target_freq)
{
	set_mpeg_bclk_div(round((double)get_pll_freq(get_mpeg_bclk_src()) / target_freq));
}

static inline void set_mpeg_pclk_freq(int target_freq)
{
	set_mpeg_pclk_div(round((double)get_mpeg_bclk_freq() / target_freq));
}

static inline void set_disp_bclk_freq(int target_freq)
{
	set_disp_bclk_div(round((double)get_pll_freq(get_disp_bclk_src()) / target_freq));
}

static inline void set_disp_pclk_freq(int target_freq)
{
	set_disp_pclk_div(round((double)get_disp_bclk_freq() / target_freq));
}

static inline void set_hdmi_pclk_freq(int target_freq)
{
	set_hdmi_pclk_div(round((double)get_pll_freq(get_hdmi_pclk_src()) / target_freq));
}

static inline void set_fast_bclk_freq(int target_freq)
{
	set_fast_bclk_div(round((double)get_pll_freq(get_fast_bclk_src()) / target_freq));
}

#endif
