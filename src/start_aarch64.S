/*
 * Copyright (C) 2017
 * Author: metro94 <flattiles@gmail.com>
 *
 * Version: v1.0
 * --- Update time: 02/07/2017
 * --- Description: First build; assemble code for S5P6818 starting up in AArch64 mode
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

#include <s5p6818.h>

	// Global functions declare
	.global boot_master_cpu
	.global boot_slave_cpu

	// Global constants declare
	.global vectors

	.align 9

	.global _start
_start:
	b	reset

	.global build_info
build_info:
	.word	(0x68180000 + (MAJOR_VERSION << 8) + (MINOR_VERSION << 0))

reset:
	msr	DAIFSet, #7		// Disables IRQ & FIQ & Asynchronous Abort Exceptions
					// [2]: Asynchronous Abort
					// [1]: IRQ
					// [0]: FIQ

	mrs	x1, MPIDR_EL1
	and	x0, x1, #0x3		// Gets Affinity Level 0
	lsr	x1, x1, #8
	and	x1, x1, #0xF		// Gets Affinity Level 1
	orr	x0, x0, x1
	mov	x29, x0			// Saves CPUID to x29

	// Sets vectors
	ldr	x0, =vectors
	ldr	x1, =0x14000000		// instruction: b .
	str	x1, [x0, #0x000]
	str	x1, [x0, #0x080]
	str	x1, [x0, #0x100]
	str	x1, [x0, #0x180]
	str	x1, [x0, #0x200]
	str	x1, [x0, #0x280]
	str	x1, [x0, #0x300]
	str	x1, [x0, #0x380]
	str	x1, [x0, #0x400]
	str	x1, [x0, #0x480]
	str	x1, [x0, #0x500]
	str	x1, [x0, #0x580]
	str	x1, [x0, #0x600]
	str	x1, [x0, #0x680]
	str	x1, [x0, #0x700]
	str	x1, [x0, #0x780]
	msr	VBAR_EL3, x0

	ands	x0, x29, #3
	bne	prepare_cpu		// if (CPUID != 0 && CPUID != 4) skip clear_bss & set_l2cache
	cmp	x29, xzr
	bne	set_l2cache		// if (CPUID != 0) skip clear_bss

	// Clears BSS Section
	ldr	x1, =__bss_start__
	ldr	x2, =__bss_end__

	cmp	x1, x2
	bhs	set_l2cache
clear_bss:
	str	xzr, [x1], #8
	cmp	x1, x2
	bls	clear_bss		// if x1 <= x2 goto clear_bss

	// Sets L2 cache
set_l2cache:
	mrs	x0, S3_1_C11_C0_2	// L2CTLR_EL1
	orr	x0, x0, #(1 << 22)	// [22] Core RAMs are implemented with ECC.
	orr	x0, x0, #(1 << 21)	// [21] L2 cache is implemented with ECC.
	orr	x0, x0, #(1 << 5)	// [5]  2-cycle input delay from L2 data RAMs.
	orr	x0, x0, #(1 << 0)	// [0]  3-cycle output delay from L2 data RAMs.
	msr	S3_1_C11_C0_2, x0

	mrs	x0, S3_1_C15_C0_0	// L2ACTLR_EL1
	bic	x0, x0, #(1 << 14)	// [14] Disables UniqueClean evictions with data. This is the reset value for ACE.
	bic	x0, x0, #(1 << 3)	// [3]  Enables clean/evict to be pushed out to external. This is the reset value for ACE.
	msr	S3_1_C15_C0_0, x0

	mrs	x0, ACTLR_EL3
	orr	x0, x0, #(1 << 6)	// [6]  L2ACTLR_EL1 is write accessible from EL2.
	orr	x0, x0, #(1 << 5)	// [5]  L2ECTLR_EL1 is write accessible from EL2.
	orr	x0, x0, #(1 << 4)	// [4]  L2CTLR_EL1 is write accessible from EL2.
	orr	x0, x0, #(1 << 1)	// [1]  CPUECTLR_EL1 is write accessible from EL2.
	orr	x0, x0, #(1 << 0)	// [0]  CPUACTLR_EL1 is write accessible from EL2.
	msr	ACTLR_EL3, x0

	// Sets registers of each CPU
prepare_cpu:
	mrs	x0, SCR_EL3
	orr	x0, x0, #(1 << 10)	// [10] The next lower level is AArch64.
	bic	x0, x0, #(1 << 8)	// [8]  The HVC instruction is UNDEFINED at all exception levels.
	bic	x0, x0, #(1 << 7)	// [7]  The SMC instruction is enabled at EL1, EL2, and EL3. This is the reset value.
	orr	x0, x0, #(1 << 5)	// [5]  RES1
	orr	x0, x0, #(1 << 4)	// [4]	RES1
	orr	x0, x0, #(1 << 2)	// [2]  Physical FIQ while executing at all exception levels are taken in EL3.
	bic	x0, x0, #(1 << 0)	// [0]	EL0 and EL1 are in Secure state, memory accesses from those exception levels can access Secure memory.
	msr	SCR_EL3, x0

	mrs	x0, CPTR_EL3
	bic	x0, x0, #(1 << 31)	// [31] Does not cause access to the CPACR_EL1 or CPTR_EL2 to be trapped.
	bic	x0, x0, #(1 << 10)	// [10] Does not cause any instruction to be trapped. This is the reset value if the Advanced SIMD and Floating-point Extension is implemented.
	msr	CPTR_EL3, x0

	mrs	x0, S3_1_C15_C2_1	// CPUECTLR_EL1
	orr	x0, x0, #(1 << 6)	// [6]  Enables data coherency with other cores in the cluster.
	msr	S3_1_C15_C2_1, x0
	isb

	mrs	x0, CPACR_EL1
	orr	x0, x0, #(3 << 20)	// [21:20] No instructions in EL0 or EL1 that uses registers associated with Advanced SIMD and Floating-point execution are trapped.
	msr	CPACR_EL1, x0

	mrs	x0, HCR_EL2
	orr	x0, x0, #(1 << 31)	// [31] EL1 is AArch64. EL0 is determined by the register width described in the current processing state when executing at EL0.
	bic	x0, x0, #(1 << 27)	// [27] Does not traps general exceptions.
	orr	x0, x0, #(1 << 4)	// [4]  Physical IRQ while executing at EL2 or lower are taken in EL2 unless routed by SCTLR_EL3.IRQ bit to EL3. Virtual IRQ interrupt is enabled.
	msr	HCR_EL2, x0

	mrs	x0, CPTR_EL2
	bic	x0, x0, #(1 << 31)	// [31] Access to CPACR is not trapped.
	bic	x0, x0, #(1 << 10)	// [10] Instructions are not trapped. This is the reset value if Advanced SIMD and Floating-point are implemented.
	msr	CPTR_EL2, x0

	// TODO: make out if not skip codes below

	mrs	x0, SCTLR_EL3
	bic	x0, x0, #(1 << 12)	// [12] Instruction caches disabled.
	msr	SCTLR_EL3, x0
	ic	ialluis			// Invalidate all instruction caches in Inner Shareable domain to Point of Unification.
	isb	sy

	mrs	x0, SCTLR_EL3
	orr	x0, x0, #(1 << 12)	// [12] Instruction caches enabled.
	msr	SCTLR_EL3, x0

	mrs	x0, SCTLR_EL2
	bic	x0, x0, #(1 << 25)	// [25] Little endian.
	bic	x0, x0, #(1 << 19)	// [19] Regions with write permissions are not forced XN.
	bic	x0, x0, #(1 << 12)	// [12] Instruction caches disabled.
	bic 	x0, x0, #(1 << 3)	// [3]  Disables stack alignment check.
	bic	x0, x0, #(1 << 2)	// [2]  Disables data and unified caches.
	bic	x0, x0, #(1 << 1)	// [1]  Disables alignment fault checking.
	bic	x0, x0, #(1 << 0)	// [0]  Disables EL2 MMU.
	msr	SCTLR_EL2, x0

	// Makes stack for each CPU
	// CPU0: -0x1000
	// CPU1: -0xE00
	// CPU2: -0xC00
	// CPU3: -0xA00
	// CPU4: -0x800
	// CPU5: -0x400
	// CPU6: -0x200
	// CPU7: -0x000
make_stack:
	ldr	x0, =INTERNAL_SRAM_BASE
	add	x0, x0, #INTERNAL_SRAM_SIZE
	ldr	x1, =(CPU_NUMBERS - 1)
	sub	x1, x1, x29
	ldr	x2, =STACK_SIZE
	mul	x1, x1, x2
	sub	x0, x0, x1

	mov	sp, x0
	msr	SP_EL2, x0
	
	cmp	x29, xzr
	bne	start_slave_cpu

start_master_cpu:
	mov	x0, x29
	b	boot_master_cpu
	b	.

start_slave_cpu:
	mov	x0, x29
	b	boot_slave_cpu
	b	.
