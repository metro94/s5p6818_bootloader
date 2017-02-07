/*
 * Copyright (C) 2017
 * Author: metro94 <flattiles@gmail.com>
 *
 * Version: v1.0
 * --- Update time: 02/07/2017
 * --- Description: First build; code for boot sequence
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

#include <boot.h>

static const init_fn init_seq[] = {
	init_led,
	init_clock,
	init_serial,
	init_system_counter,
	disp_compile_info,
#ifdef DEBUG
	disp_clock_info,
#endif
	init_i2c,
	init_pmic,
	release_i2c,
	init_ddr3,
	set_drex_qos,
	init_bus,
#ifdef PI_MEM_TEST
	test_ddr3,
#endif
	wakeup_slave_cpu,
	NULL
};

void boot_master_cpu(uint32_t cpuid)
{
	int init_step;
	void (*go_next_stage)(void);
	
	(void)(cpuid);	// Not used at all
	
	for (init_step = 0; init_seq[init_step]; ++init_step)
		init_seq[init_step]();
	
	go_next_stage = do_sdfs_boot();
	
	if (!go_next_stage) {	// SDFS boot failed, trying USB boot
		printf("Entering USB boot mode\n");
		do {
			go_next_stage = do_usb_boot();
		} while (!go_next_stage);
	}
	
	set_led_on();
	printf("Going to %p. Good-bye.\n", go_next_stage);
	wait_serial_tx_done();
	go_next_stage();
	
	while (1);
}

void boot_slave_cpu(uint32_t cpuid)
{
	init_fn run_next_stage;
	
	debug(DEBUG_LEVEL_INFO, "CPU%d is ready\n", cpuid);
//	wait_serial_tx_done();
	nx_sysctrl->scratch[0] = cpuid;
	do {
		debug(DEBUG_LEVEL_INFO, "CPU%d enters wfi\n", cpuid);
//		wait_serial_tx_done();
		asm __volatile__("wfi");
		debug(DEBUG_LEVEL_INFO, "CPU%d wakes up\n", cpuid);
		if (ref64(PI_SLAVE_CPU_RELEASE_ADDR) != NULL) {
			run_next_stage = (init_fn)PI_SLAVE_CPU_RELEASE_ADDR;
			run_next_stage();
		}
	} while (1);
}

void disp_compile_info(void)
{
	printf("\n");
	printf("****************************************\n");
	printf("* Bootloader for S5P6818 - Version %d.%d *\n", (build_info >> 8) & 0xFF, (build_info >> 0) & 0xF);
	printf("* Compiled at %s, %-11s    *\n", __TIME__, __DATE__);
	printf("****************************************\n");
	printf("\n");
}

void wakeup_slave_cpu(void)
{
	uint32_t cpuid;
	
	debug("", "\n");
	debug(DEBUG_LEVEL_INFO, "Trying to wake up slave CPU\n");
	
	write64(PI_SLAVE_CPU_RELEASE_ADDR, NULL);
	for (cpuid = 1; cpuid < 8; ++cpuid) {
		wait_serial_tx_done();
		nx_sysctrl->cpu_power_on_req = (1 << cpuid);
		delay_us(100);
		if (nx_sysctrl->scratch[0] != cpuid) {
			debug(DEBUG_LEVEL_WARN, "Cannot wake up CPU%d\n", cpuid);
		}
	}
}
