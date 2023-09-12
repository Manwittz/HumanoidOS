/* $OpenBSD: armreg.h,v 1.29 2023/06/10 19:30:48 kettenis Exp $ */
/*-
 * Copyright (c) 2013, 2014 Andrew Turner
 * Copyright (c) 2015 The FreeBSD Foundation
 * All rights reserved.
 *
 * This software was developed by Andrew Turner under
 * sponsorship from the FreeBSD Foundation.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD: head/sys/arm64/include/armreg.h 309248 2016-11-28 14:24:07Z andrew $
 */

#ifndef _MACHINE_ARMREG_H_
#define	_MACHINE_ARMREG_H_

#define	INSN_SIZE		4

#define	READ_SPECIALREG(reg)						\
({	uint64_t val;							\
	__asm volatile("mrs	%0, " __STRING(reg) : "=&r" (val));	\
	val;								\
})
#define	WRITE_SPECIALREG(reg, val)					\
	__asm volatile("msr	" __STRING(reg) ", %0" : : "r"((uint64_t)val))

/* CCSIDR_EL1 - Current Cache Size ID Register */
#define	CCSIDR_SETS_MASK	0x0fffe000
#define	CCSIDR_SETS_SHIFT	13
#define	CCSIDR_SETS(reg)	\
    ((((reg) & CCSIDR_SETS_MASK) >> CCSIDR_SETS_SHIFT) + 1)
#define	CCSIDR_WAYS_MASK	0x00001ff8
#define	CCSIDR_WAYS_SHIFT	3
#define	CCSIDR_WAYS(reg)	\
    ((((reg) & CCSIDR_WAYS_MASK) >> CCSIDR_WAYS_SHIFT) + 1)
#define	CCSIDR_LINE_MASK	0x00000007
#define	CCSIDR_LINE_SIZE(reg)	(1 << (((reg) & CCSIDR_LINE_MASK) + 4))

/* CLIDR_EL1 - Cache Level ID Register */
#define	CLIDR_CTYPE_MASK	0x7
#define	CLIDR_CTYPE_INSN	0x1
#define	CLIDR_CTYPE_DATA	0x2
#define	CLIDR_CTYPE_UNIFIED	0x4

/* CNTHCTL_EL2 - Counter-timer Hypervisor Control Register */
#define	CNTHCTL_EVNTI_MASK	(0xf << 4) /* Bit to trigger event stream */
#define	CNTHCTL_EVNTDIR		(1 << 3) /* Control transition trigger bit */
#define	CNTHCTL_EVNTEN		(1 << 2) /* Enable event stream */
#define	CNTHCTL_EL1PCEN		(1 << 1) /* Allow EL0/1 physical timer access */
#define	CNTHCTL_EL1PCTEN	(1 << 0) /*Allow EL0/1 physical counter access*/

/* CNTKCTL_EL1 - Counter-timer Kernel Control Register */
#define	CNTKCTL_EL0VCTEN	(1 << 1) /* Allow EL0 virtual counter access */

/* CNTV_CTL_EL0 */
#define	CNTV_CTL_ENABLE		(1 << 0)
#define	CNTV_CTL_IMASK		(1 << 1)
#define	CNTV_CTL_ISTATUS	(1 << 2)

/* CPACR_EL1 */
#define	CPACR_FPEN_MASK		(0x3 << 20)
#define	 CPACR_FPEN_TRAP_ALL1	(0x0 << 20) /* Traps from EL0 and EL1 */
#define	 CPACR_FPEN_TRAP_EL0	(0x1 << 20) /* Traps from EL0 */
#define	 CPACR_FPEN_TRAP_ALL2	(0x2 << 20) /* Traps from EL0 and EL1 */
#define	 CPACR_FPEN_TRAP_NONE	(0x3 << 20) /* No traps */
#define	CPACR_TTA		(0x1 << 28)

/* CSSELR_EL1 - Cache Size Selection Register */
#define	CSSELR_IND		(1 << 0)
#define	CSSELR_LEVEL_SHIFT	1

/* CTR_EL0 - Cache Type Register */
#define	CTR_DLINE_SHIFT		16
#define	CTR_DLINE_MASK		(0xf << CTR_DLINE_SHIFT)
#define	CTR_DLINE_SIZE(reg)	(((reg) & CTR_DLINE_MASK) >> CTR_DLINE_SHIFT)
#define	CTR_IL1P_SHIFT		14
#define	CTR_IL1P_MASK		(0x3 << CTR_IL1P_SHIFT)
#define	CTR_IL1P_AIVIVT		(0x1 << CTR_IL1P_SHIFT)
#define	CTR_IL1P_VIPT		(0x2 << CTR_IL1P_SHIFT)
#define	CTR_IL1P_PIPT		(0x3 << CTR_IL1P_SHIFT)
#define	CTR_ILINE_SHIFT		0
#define	CTR_ILINE_MASK		(0xf << CTR_ILINE_SHIFT)
#define	CTR_ILINE_SIZE(reg)	(((reg) & CTR_ILINE_MASK) >> CTR_ILINE_SHIFT)

/* MPIDR_EL1 - Multiprocessor Affinity Register */
#define MPIDR_AFF3		(0xFFULL << 32)
#define MPIDR_AFF2		(0xFFULL << 16)
#define MPIDR_AFF1		(0xFFULL << 8)
#define MPIDR_AFF0		(0xFFULL << 0)
#define MPIDR_AFF		(MPIDR_AFF3|MPIDR_AFF2|MPIDR_AFF1|MPIDR_AFF0)

/* DCZID_EL0 - Data Cache Zero ID register */
#define DCZID_DZP		(1 << 4) /* DC ZVA prohibited if non-0 */
#define DCZID_BS_SHIFT		0
#define DCZID_BS_MASK		(0xf << DCZID_BS_SHIFT)
#define	DCZID_BS_SIZE(reg)	(((reg) & DCZID_BS_MASK) >> DCZID_BS_SHIFT)

/* ESR_ELx */
#define	ESR_ELx_ISS_MASK	0x00ffffff
#define	 ISS_INSN_FnV		(0x01 << 10)
#define	 ISS_INSN_EA		(0x01 << 9)
#define	 ISS_INSN_S1PTW		(0x01 << 7)
#define	 ISS_INSN_IFSC_MASK	(0x1f << 0)
#define	 ISS_DATA_ISV		(0x01 << 24)
#define	 ISS_DATA_SAS_MASK	(0x03 << 22)
#define	 ISS_DATA_SSE		(0x01 << 21)
#define	 ISS_DATA_SRT_MASK	(0x1f << 16)
#define	 ISS_DATA_SF		(0x01 << 15)
#define	 ISS_DATA_AR		(0x01 << 14)
#define	 ISS_DATA_FnV		(0x01 << 10)
#define	 ISS_DATA_EA		(0x01 << 9)
#define	 ISS_DATA_CM		(0x01 << 8)
#define	 ISS_INSN_S1PTW		(0x01 << 7)
#define	 ISS_DATA_WnR		(0x01 << 6)
#define	 ISS_DATA_DFSC_MASK	(0x3f << 0)
#define	 ISS_DATA_DFSC_ASF_L0	(0x00 << 0)
#define	 ISS_DATA_DFSC_ASF_L1	(0x01 << 0)
#define	 ISS_DATA_DFSC_ASF_L2	(0x02 << 0)
#define	 ISS_DATA_DFSC_ASF_L3	(0x03 << 0)
#define	 ISS_DATA_DFSC_TF_L0	(0x04 << 0)
#define	 ISS_DATA_DFSC_TF_L1	(0x05 << 0)
#define	 ISS_DATA_DFSC_TF_L2	(0x06 << 0)
#define	 ISS_DATA_DFSC_TF_L3	(0x07 << 0)
#define	 ISS_DATA_DFSC_AFF_L1	(0x09 << 0)
#define	 ISS_DATA_DFSC_AFF_L2	(0x0a << 0)
#define	 ISS_DATA_DFSC_AFF_L3	(0x0b << 0)
#define	 ISS_DATA_DFSC_PF_L1	(0x0d << 0)
#define	 ISS_DATA_DFSC_PF_L2	(0x0e << 0)
#define	 ISS_DATA_DFSC_PF_L3	(0x0f << 0)
#define	 ISS_DATA_DFSC_EXT	(0x10 << 0)
#define	 ISS_DATA_DFSC_EXT_L0	(0x14 << 0)
#define	 ISS_DATA_DFSC_EXT_L1	(0x15 << 0)
#define	 ISS_DATA_DFSC_EXT_L2	(0x16 << 0)
#define	 ISS_DATA_DFSC_EXT_L3	(0x17 << 0)
#define	 ISS_DATA_DFSC_ECC	(0x18 << 0)
#define	 ISS_DATA_DFSC_ECC_L0	(0x1c << 0)
#define	 ISS_DATA_DFSC_ECC_L1	(0x1d << 0)
#define	 ISS_DATA_DFSC_ECC_L2	(0x1e << 0)
#define	 ISS_DATA_DFSC_ECC_L3	(0x1f << 0)
#define	 ISS_DATA_DFSC_ALIGN	(0x21 << 0)
#define	 ISS_DATA_DFSC_TLB_CONFLICT (0x30 << 0)
#define	ESR_ELx_IL		(0x01 << 25)
#define	ESR_ELx_EC_SHIFT	26
#define	ESR_ELx_EC_MASK		(0x3f << 26)
#define	ESR_ELx_EXCEPTION(esr)	(((esr) & ESR_ELx_EC_MASK) >> ESR_ELx_EC_SHIFT)
#define	 EXCP_UNKNOWN		0x00	/* Unkwn exception */
#define	 EXCP_FP_SIMD		0x07	/* FP/SIMD trap */
#define	 EXCP_BRANCH_TGT	0x0d	/* Branch target exception */
#define	 EXCP_ILL_STATE		0x0e	/* Illegal execution state */
#define	 EXCP_SVC		0x15	/* SVC trap */
#define	 EXCP_MSR		0x18	/* MSR/MRS trap */
#define	 EXCP_FPAC		0x1c	/* Faulting PAC trap */
#define	 EXCP_INSN_ABORT_L	0x20	/* Instruction abort, from lower EL */
#define	 EXCP_INSN_ABORT	0x21	/* Instruction abort, from same EL */ 
#define	 EXCP_PC_ALIGN		0x22	/* PC alignment fault */
#define	 EXCP_DATA_ABORT_L	0x24	/* Data abort, from lower EL */
#define	 EXCP_DATA_ABORT	0x25	/* Data abort, from same EL */ 
#define	 EXCP_SP_ALIGN		0x26	/* SP alignment fault */
#define	 EXCP_TRAP_FP		0x2c	/* Trapped FP exception */
#define	 EXCP_SERROR		0x2f	/* SError interrupt */
#define	 EXCP_SOFTSTP_EL0	0x32	/* Software Step, from lower EL */
#define	 EXCP_SOFTSTP_EL1	0x33	/* Software Step, from same EL */
#define	 EXCP_WATCHPT_EL1	0x35	/* Watchpoint, from same EL */
#define	 EXCP_BRK		0x3c	/* Breakpoint */

/* ICC_CTLR_EL1 */
#define	ICC_CTLR_EL1_EOIMODE		(1U << 1)
#define	ICC_CTLR_EL1_PRIBITS_SHIFT	8
#define	ICC_CTLR_EL1_PRIBITS_MASK	(0x7UL << 8)
#define	ICC_CTLR_EL1_PRIBITS(reg)	\
    (((reg) & ICC_CTLR_EL1_PRIBITS_MASK) >> ICC_CTLR_EL1_PRIBITS_SHIFT)

/* ICC_IAR1_EL1 */
#define	ICC_IAR1_EL1_SPUR	(0x03ff)

/* ICC_IGRPEN0_EL1 */
#define	ICC_IGRPEN0_EL1_EN	(1U << 0)

/* ICC_PMR_EL1 */
#define	ICC_PMR_EL1_PRIO_MASK	(0xFFUL)

/* ICC_SGI1R_EL1 */
#define	ICC_SGI1R_EL1_TL_MASK		0xffffUL
#define	ICC_SGI1R_EL1_AFF1_SHIFT	16
#define	ICC_SGI1R_EL1_SGIID_SHIFT	24
#define	ICC_SGI1R_EL1_AFF2_SHIFT	32
#define	ICC_SGI1R_EL1_AFF3_SHIFT	48
#define	ICC_SGI1R_EL1_SGIID_MASK	0xfUL
#define	ICC_SGI1R_EL1_IRM		(0x1UL << 40)

/* ICC_SRE_EL1 */
#define	ICC_SRE_EL1_SRE		(1U << 0)

/* ICC_SRE_EL2 */
#define	ICC_SRE_EL2_SRE		(1U << 0)
#define	ICC_SRE_EL2_EN		(1U << 3)

/* ID_AA64DFR0_EL1 */
#define	ID_AA64DFR0_MASK		0x00000000f0f0ffffUL
#define	ID_AA64DFR0_DEBUG_VER_SHIFT	0
#define	ID_AA64DFR0_DEBUG_VER_MASK	(0xf << ID_AA64DFR0_DEBUG_VER_SHIFT)
#define	ID_AA64DFR0_DEBUG_VER(x)	((x) & ID_AA64DFR0_DEBUG_VER_MASK)
#define	 ID_AA64DFR0_DEBUG_VER_8	(0x6 << ID_AA64DFR0_DEBUG_VER_SHIFT)
#define	 ID_AA64DFR0_DEBUG_VER_8_VHE	(0x7 << ID_AA64DFR0_DEBUG_VER_SHIFT)
#define	ID_AA64DFR0_TRACE_VER_SHIFT	4
#define	ID_AA64DFR0_TRACE_VER_MASK	(0xf << ID_AA64DFR0_TRACE_VER_SHIFT)
#define	ID_AA64DFR0_TRACE_VER(x)	((x) & ID_AA64DFR0_TRACE_VER_MASK)
#define	 ID_AA64DFR0_TRACE_VER_NONE	(0x0 << ID_AA64DFR0_TRACE_VER_SHIFT)
#define	 ID_AA64DFR0_TRACE_VER_IMPL	(0x1 << ID_AA64DFR0_TRACE_VER_SHIFT)
#define	ID_AA64DFR0_PMU_VER_SHIFT	8
#define	ID_AA64DFR0_PMU_VER_MASK	(0xf << ID_AA64DFR0_PMU_VER_SHIFT)
#define	ID_AA64DFR0_PMU_VER(x)		((x) & ID_AA64DFR0_PMU_VER_MASK)
#define	 ID_AA64DFR0_PMU_VER_NONE	(0x0 << ID_AA64DFR0_PMU_VER_SHIFT)
#define	 ID_AA64DFR0_PMU_VER_3		(0x1 << ID_AA64DFR0_PMU_VER_SHIFT)
#define	 ID_AA64DFR0_PMU_VER_3_1	(0x4 << ID_AA64DFR0_PMU_VER_SHIFT)
#define	 ID_AA64DFR0_PMU_VER_IMPL	(0xf << ID_AA64DFR0_PMU_VER_SHIFT)
#define	ID_AA64DFR0_BRPS_SHIFT		12
#define	ID_AA64DFR0_BRPS_MASK		(0xf << ID_AA64DFR0_BRPS_SHIFT)
#define	ID_AA64DFR0_BRPS(x)		\
    ((((x) >> ID_AA64DFR0_BRPS_SHIFT) & 0xf) + 1)
#define	ID_AA64DFR0_WRPS_SHIFT		20
#define	ID_AA64DFR0_WRPS_MASK		(0xf << ID_AA64DFR0_WRPS_SHIFT)
#define	ID_AA64DFR0_WRPS(x)		\
    ((((x) >> ID_AA64DFR0_WRPS_SHIFT) & 0xf) + 1)
#define	ID_AA64DFR0_CTX_CMPS_SHIFT	28
#define	ID_AA64DFR0_CTX_CMPS_MASK	(0xf << ID_AA64DFR0_CTX_CMPS_SHIFT)
#define	ID_AA64DFR0_CTX_CMPS(x)		\
    ((((x) >> ID_AA64DFR0_CTX_CMPS_SHIFT) & 0xf) + 1)

/* ID_AA64ISAR0_EL1 */
#define	ID_AA64ISAR0_MASK		0xfffffffff0fffff0ULL
#define	ID_AA64ISAR0_AES_SHIFT		4
#define	ID_AA64ISAR0_AES_MASK		(0xf << ID_AA64ISAR0_AES_SHIFT)
#define	ID_AA64ISAR0_AES(x)		((x) & ID_AA64ISAR0_AES_MASK)
#define	 ID_AA64ISAR0_AES_NONE		(0x0 << ID_AA64ISAR0_AES_SHIFT)
#define	 ID_AA64ISAR0_AES_BASE		(0x1 << ID_AA64ISAR0_AES_SHIFT)
#define	 ID_AA64ISAR0_AES_PMULL		(0x2 << ID_AA64ISAR0_AES_SHIFT)
#define	ID_AA64ISAR0_SHA1_SHIFT		8
#define	ID_AA64ISAR0_SHA1_MASK		(0xf << ID_AA64ISAR0_SHA1_SHIFT)
#define	ID_AA64ISAR0_SHA1(x)		((x) & ID_AA64ISAR0_SHA1_MASK)
#define	 ID_AA64ISAR0_SHA1_NONE		(0x0 << ID_AA64ISAR0_SHA1_SHIFT)
#define	 ID_AA64ISAR0_SHA1_BASE		(0x1 << ID_AA64ISAR0_SHA1_SHIFT)
#define	ID_AA64ISAR0_SHA2_SHIFT		12
#define	ID_AA64ISAR0_SHA2_MASK		(0xf << ID_AA64ISAR0_SHA2_SHIFT)
#define	ID_AA64ISAR0_SHA2(x)		((x) & ID_AA64ISAR0_SHA2_MASK)
#define	 ID_AA64ISAR0_SHA2_NONE		(0x0 << ID_AA64ISAR0_SHA2_SHIFT)
#define	 ID_AA64ISAR0_SHA2_BASE		(0x1 << ID_AA64ISAR0_SHA2_SHIFT)
#define	 ID_AA64ISAR0_SHA2_512		(0x2 << ID_AA64ISAR0_SHA2_SHIFT)
#define	ID_AA64ISAR0_CRC32_SHIFT	16
#define	ID_AA64ISAR0_CRC32_MASK		(0xf << ID_AA64ISAR0_CRC32_SHIFT)
#define	ID_AA64ISAR0_CRC32(x)		((x) & ID_AA64ISAR0_CRC32_MASK)
#define	 ID_AA64ISAR0_CRC32_NONE	(0x0 << ID_AA64ISAR0_CRC32_SHIFT)
#define	 ID_AA64ISAR0_CRC32_BASE	(0x1 << ID_AA64ISAR0_CRC32_SHIFT)
#define	ID_AA64ISAR0_ATOMIC_SHIFT	20
#define	ID_AA64ISAR0_ATOMIC_MASK	(0xf << ID_AA64ISAR0_ATOMIC_SHIFT)
#define	ID_AA64ISAR0_ATOMIC(x)		((x) & ID_AA64ISAR0_ATOMIC_MASK)
#define	 ID_AA64ISAR0_ATOMIC_NONE	(0x0 << ID_AA64ISAR0_ATOMIC_SHIFT)
#define	 ID_AA64ISAR0_ATOMIC_IMPL	(0x2 << ID_AA64ISAR0_ATOMIC_SHIFT)
#define	ID_AA64ISAR0_RDM_SHIFT		28
#define	ID_AA64ISAR0_RDM_MASK		(0xf << ID_AA64ISAR0_RDM_SHIFT)
#define	ID_AA64ISAR0_RDM(x)		((x) & ID_AA64ISAR0_RDM_MASK)
#define	 ID_AA64ISAR0_RDM_NONE		(0x0 << ID_AA64ISAR0_RDM_SHIFT)
#define	 ID_AA64ISAR0_RDM_IMPL		(0x1 << ID_AA64ISAR0_RDM_SHIFT)
#define	ID_AA64ISAR0_SHA3_SHIFT		32
#define	ID_AA64ISAR0_SHA3_MASK		(0xfULL << ID_AA64ISAR0_SHA3_SHIFT)
#define	ID_AA64ISAR0_SHA3(x)		((x) & ID_AA64ISAR0_SHA3_MASK)
#define	 ID_AA64ISAR0_SHA3_NONE		(0x0ULL << ID_AA64ISAR0_SHA3_SHIFT)
#define	 ID_AA64ISAR0_SHA3_IMPL		(0x1ULL << ID_AA64ISAR0_SHA3_SHIFT)
#define	ID_AA64ISAR0_SM3_SHIFT		36
#define	ID_AA64ISAR0_SM3_MASK		(0xfULL << ID_AA64ISAR0_SM3_SHIFT)
#define	ID_AA64ISAR0_SM3(x)		((x) & ID_AA64ISAR0_SM3_MASK)
#define	 ID_AA64ISAR0_SM3_NONE		(0x0ULL << ID_AA64ISAR0_SM3_SHIFT)
#define	 ID_AA64ISAR0_SM3_IMPL		(0x1ULL << ID_AA64ISAR0_SM3_SHIFT)
#define	ID_AA64ISAR0_SM4_SHIFT		40
#define	ID_AA64ISAR0_SM4_MASK		(0xfULL << ID_AA64ISAR0_SM4_SHIFT)
#define	ID_AA64ISAR0_SM4(x)		((x) & ID_AA64ISAR0_SM4_MASK)
#define	 ID_AA64ISAR0_SM4_NONE		(0x0ULL << ID_AA64ISAR0_SM4_SHIFT)
#define	 ID_AA64ISAR0_SM4_IMPL		(0x1ULL << ID_AA64ISAR0_SM4_SHIFT)
#define	ID_AA64ISAR0_DP_SHIFT		44
#define	ID_AA64ISAR0_DP_MASK		(0xfULL << ID_AA64ISAR0_DP_SHIFT)
#define	ID_AA64ISAR0_DP(x)		((x) & ID_AA64ISAR0_DP_MASK)
#define	 ID_AA64ISAR0_DP_NONE		(0x0ULL << ID_AA64ISAR0_DP_SHIFT)
#define	 ID_AA64ISAR0_DP_IMPL		(0x1ULL << ID_AA64ISAR0_DP_SHIFT)
#define	ID_AA64ISAR0_FHM_SHIFT		48
#define	ID_AA64ISAR0_FHM_MASK		(0xfULL << ID_AA64ISAR0_FHM_SHIFT)
#define	ID_AA64ISAR0_FHM(x)		((x) & ID_AA64ISAR0_FHM_MASK)
#define	 ID_AA64ISAR0_FHM_NONE		(0x0ULL << ID_AA64ISAR0_FHM_SHIFT)
#define	 ID_AA64ISAR0_FHM_IMPL		(0x1ULL << ID_AA64ISAR0_FHM_SHIFT)
#define	ID_AA64ISAR0_TS_SHIFT		52
#define	ID_AA64ISAR0_TS_MASK		(0xfULL << ID_AA64ISAR0_TS_SHIFT)
#define	ID_AA64ISAR0_TS(x)		((x) & ID_AA64ISAR0_TS_MASK)
#define	 ID_AA64ISAR0_TS_NONE		(0x0ULL << ID_AA64ISAR0_TS_SHIFT)
#define	 ID_AA64ISAR0_TS_BASE		(0x1ULL << ID_AA64ISAR0_TS_SHIFT)
#define	 ID_AA64ISAR0_TS_AXFLAG		(0x2ULL << ID_AA64ISAR0_TS_SHIFT)
#define	ID_AA64ISAR0_TLB_SHIFT		56
#define	ID_AA64ISAR0_TLB_MASK		(0xfULL << ID_AA64ISAR0_TLB_SHIFT)
#define	ID_AA64ISAR0_TLB(x)		((x) & ID_AA64ISAR0_TLB_MASK)
#define	 ID_AA64ISAR0_TLB_NONE		(0x0ULL << ID_AA64ISAR0_TLB_SHIFT)
#define	 ID_AA64ISAR0_TLB_IOS		(0x1ULL << ID_AA64ISAR0_TLB_SHIFT)
#define	 ID_AA64ISAR0_TLB_IRANGE	(0x2ULL << ID_AA64ISAR0_TLB_SHIFT)
#define	ID_AA64ISAR0_RNDR_SHIFT		60
#define	ID_AA64ISAR0_RNDR_MASK		(0xfULL << ID_AA64ISAR0_RNDR_SHIFT)
#define	ID_AA64ISAR0_RNDR(x)		((x) & ID_AA64ISAR0_RNDR_MASK)
#define	 ID_AA64ISAR0_RNDR_NONE		(0x0ULL << ID_AA64ISAR0_RNDR_SHIFT)
#define	 ID_AA64ISAR0_RNDR_IMPL		(0x1ULL << ID_AA64ISAR0_RNDR_SHIFT)

/* ID_AA64ISAR1_EL1 */
#define	ID_AA64ISAR1_MASK		0x00000fffffffffffULL
#define	ID_AA64ISAR1_DPB_SHIFT		0
#define	ID_AA64ISAR1_DPB_MASK		(0xf << ID_AA64ISAR1_DPB_SHIFT)
#define	ID_AA64ISAR1_DPB(x)		((x) & ID_AA64ISAR1_DPB_MASK)
#define	 ID_AA64ISAR1_DPB_NONE		(0x0 << ID_AA64ISAR1_DPB_SHIFT)
#define	 ID_AA64ISAR1_DPB_IMPL		(0x1 << ID_AA64ISAR1_DPB_SHIFT)
#define	ID_AA64ISAR1_APA_SHIFT		4
#define	ID_AA64ISAR1_APA_MASK		(0xf << ID_AA64ISAR1_APA_SHIFT)
#define	ID_AA64ISAR1_APA(x)		((x) & ID_AA64ISAR1_APA_MASK)
#define	 ID_AA64ISAR1_APA_NONE		(0x0 << ID_AA64ISAR1_APA_SHIFT)
#define	 ID_AA64ISAR1_APA_BASE		(0x1 << ID_AA64ISAR1_APA_SHIFT)
#define	 ID_AA64ISAR1_APA_PAC		(0x2 << ID_AA64ISAR1_APA_SHIFT)
#define	ID_AA64ISAR1_API_SHIFT		8
#define	ID_AA64ISAR1_API_MASK		(0xf << ID_AA64ISAR1_API_SHIFT)
#define	ID_AA64ISAR1_API(x)		((x) & ID_AA64ISAR1_API_MASK)
#define	 ID_AA64ISAR1_API_NONE		(0x0 << ID_AA64ISAR1_API_SHIFT)
#define	 ID_AA64ISAR1_API_BASE		(0x1 << ID_AA64ISAR1_API_SHIFT)
#define	 ID_AA64ISAR1_API_PAC		(0x2 << ID_AA64ISAR1_API_SHIFT)
#define	ID_AA64ISAR1_JSCVT_SHIFT	12
#define	ID_AA64ISAR1_JSCVT_MASK		(0xf << ID_AA64ISAR1_JSCVT_SHIFT)
#define	ID_AA64ISAR1_JSCVT(x)		((x) & ID_AA64ISAR1_JSCVT_MASK)
#define	 ID_AA64ISAR1_JSCVT_NONE	(0x0 << ID_AA64ISAR1_JSCVT_SHIFT)
#define	 ID_AA64ISAR1_JSCVT_IMPL	(0x1 << ID_AA64ISAR1_JSCVT_SHIFT)
#define	ID_AA64ISAR1_FCMA_SHIFT		16
#define	ID_AA64ISAR1_FCMA_MASK		(0xf << ID_AA64ISAR1_FCMA_SHIFT)
#define	ID_AA64ISAR1_FCMA(x)		((x) & ID_AA64ISAR1_FCMA_MASK)
#define	 ID_AA64ISAR1_FCMA_NONE		(0x0 << ID_AA64ISAR1_FCMA_SHIFT)
#define	 ID_AA64ISAR1_FCMA_IMPL		(0x1 << ID_AA64ISAR1_FCMA_SHIFT)
#define	ID_AA64ISAR1_LRCPC_SHIFT	20
#define	ID_AA64ISAR1_LRCPC_MASK		(0xf << ID_AA64ISAR1_LRCPC_SHIFT)
#define	ID_AA64ISAR1_LRCPC(x)		((x) & ID_AA64ISAR1_LRCPC_MASK)
#define	 ID_AA64ISAR1_LRCPC_NONE	(0x0 << ID_AA64ISAR1_LRCPC_SHIFT)
#define	 ID_AA64ISAR1_LRCPC_BASE	(0x1 << ID_AA64ISAR1_LRCPC_SHIFT)
#define	 ID_AA64ISAR1_LRCPC_LDAPUR	(0x2 << ID_AA64ISAR1_LRCPC_SHIFT)
#define	ID_AA64ISAR1_GPA_SHIFT		24
#define	ID_AA64ISAR1_GPA_MASK		(0xf << ID_AA64ISAR1_GPA_SHIFT)
#define	ID_AA64ISAR1_GPA(x)		((x) & ID_AA64ISAR1_GPA_MASK)
#define	 ID_AA64ISAR1_GPA_NONE		(0x0 << ID_AA64ISAR1_GPA_SHIFT)
#define	 ID_AA64ISAR1_GPA_IMPL		(0x1 << ID_AA64ISAR1_GPA_SHIFT)
#define	ID_AA64ISAR1_GPI_SHIFT		28
#define	ID_AA64ISAR1_GPI_MASK		(0xf << ID_AA64ISAR1_GPI_SHIFT)
#define	ID_AA64ISAR1_GPI(x)		((x) & ID_AA64ISAR1_GPI_MASK)
#define	 ID_AA64ISAR1_GPI_NONE		(0x0 << ID_AA64ISAR1_GPI_SHIFT)
#define	 ID_AA64ISAR1_GPI_IMPL		(0x1 << ID_AA64ISAR1_GPI_SHIFT)
#define	ID_AA64ISAR1_FRINTTS_SHIFT	32
#define	ID_AA64ISAR1_FRINTTS_MASK	(0xfULL << ID_AA64ISAR1_FRINTTS_SHIFT)
#define	ID_AA64ISAR1_FRINTTS(x)		((x) & ID_AA64ISAR1_FRINTTS_MASK)
#define	 ID_AA64ISAR1_FRINTTS_NONE	(0x0ULL << ID_AA64ISAR1_FRINTTS_SHIFT)
#define	 ID_AA64ISAR1_FRINTTS_IMPL	(0x1ULL << ID_AA64ISAR1_FRINTTS_SHIFT)
#define	ID_AA64ISAR1_SB_SHIFT		36
#define	ID_AA64ISAR1_SB_MASK		(0xfULL << ID_AA64ISAR1_SB_SHIFT)
#define	ID_AA64ISAR1_SB(x)		((x) & ID_AA64ISAR1_SB_MASK)
#define	 ID_AA64ISAR1_SB_NONE		(0x0ULL << ID_AA64ISAR1_SB_SHIFT)
#define	 ID_AA64ISAR1_SB_IMPL		(0x1ULL << ID_AA64ISAR1_SB_SHIFT)
#define	ID_AA64ISAR1_SPECRES_SHIFT	40
#define	ID_AA64ISAR1_SPECRES_MASK	(0xfULL << ID_AA64ISAR1_SPECRES_SHIFT)
#define	ID_AA64ISAR1_SPECRES(x)		((x) & ID_AA64ISAR1_SPECRES_MASK)
#define	 ID_AA64ISAR1_SPECRES_NONE	(0x0ULL << ID_AA64ISAR1_SPECRES_SHIFT)
#define	 ID_AA64ISAR1_SPECRES_IMPL	(0x1ULL << ID_AA64ISAR1_SPECRES_SHIFT)

/* ID_AA64ISAR2_EL1 */
#define	ID_AA64ISAR2_MASK		0x00000000f0000000ULL
#define	ID_AA64ISAR2_CLRBHB_SHIFT	28
#define	ID_AA64ISAR2_CLRBHB_MASK	(0xfULL << ID_AA64ISAR2_CLRBHB_SHIFT)
#define	ID_AA64ISAR2_CLRBHB(x)		((x) & ID_AA64ISAR2_CLRBHB_MASK)
#define	 ID_AA64ISAR2_CLRBHB_NONE	(0x0ULL << ID_AA64ISAR2_CLRBHB_SHIFT)
#define	 ID_AA64ISAR2_CLRBHB_IMPL	(0x1ULL << ID_AA64ISAR2_CLRBHB_SHIFT)

/* ID_AA64MMFR0_EL1 */
#define	ID_AA64MMFR0_MASK		0x00000000ffffffffULL
#define	ID_AA64MMFR0_PA_RANGE_SHIFT	0
#define	ID_AA64MMFR0_PA_RANGE_MASK	(0xf << ID_AA64MMFR0_PA_RANGE_SHIFT)
#define	ID_AA64MMFR0_PA_RANGE(x)	((x) & ID_AA64MMFR0_PA_RANGE_MASK)
#define	 ID_AA64MMFR0_PA_RANGE_4G	(0x0 << ID_AA64MMFR0_PA_RANGE_SHIFT)
#define	 ID_AA64MMFR0_PA_RANGE_64G	(0x1 << ID_AA64MMFR0_PA_RANGE_SHIFT)
#define	 ID_AA64MMFR0_PA_RANGE_1T	(0x2 << ID_AA64MMFR0_PA_RANGE_SHIFT)
#define	 ID_AA64MMFR0_PA_RANGE_4T	(0x3 << ID_AA64MMFR0_PA_RANGE_SHIFT)
#define	 ID_AA64MMFR0_PA_RANGE_16T	(0x4 << ID_AA64MMFR0_PA_RANGE_SHIFT)
#define	 ID_AA64MMFR0_PA_RANGE_256T	(0x5 << ID_AA64MMFR0_PA_RANGE_SHIFT)
#define	ID_AA64MMFR0_ASID_BITS_SHIFT	4
#define	ID_AA64MMFR0_ASID_BITS_MASK	(0xf << ID_AA64MMFR0_ASID_BITS_SHIFT)
#define	ID_AA64MMFR0_ASID_BITS(x)	((x) & ID_AA64MMFR0_ASID_BITS_MASK)
#define	 ID_AA64MMFR0_ASID_BITS_8	(0x0 << ID_AA64MMFR0_ASID_BITS_SHIFT)
#define	 ID_AA64MMFR0_ASID_BITS_16	(0x2 << ID_AA64MMFR0_ASID_BITS_SHIFT)
#define	ID_AA64MMFR0_BIGEND_SHIFT	8
#define	ID_AA64MMFR0_BIGEND_MASK	(0xf << ID_AA64MMFR0_BIGEND_SHIFT)
#define	ID_AA64MMFR0_BIGEND(x)		((x) & ID_AA64MMFR0_BIGEND_MASK)
#define	 ID_AA64MMFR0_BIGEND_FIXED	(0x0 << ID_AA64MMFR0_BIGEND_SHIFT)
#define	 ID_AA64MMFR0_BIGEND_MIXED	(0x1 << ID_AA64MMFR0_BIGEND_SHIFT)
#define	ID_AA64MMFR0_S_NS_MEM_SHIFT	12
#define	ID_AA64MMFR0_S_NS_MEM_MASK	(0xf << ID_AA64MMFR0_S_NS_MEM_SHIFT)
#define	ID_AA64MMFR0_S_NS_MEM(x)	((x) & ID_AA64MMFR0_S_NS_MEM_MASK)
#define	 ID_AA64MMFR0_S_NS_MEM_NONE	(0x0 << ID_AA64MMFR0_S_NS_MEM_SHIFT)
#define	 ID_AA64MMFR0_S_NS_MEM_DISTINCT	(0x1 << ID_AA64MMFR0_S_NS_MEM_SHIFT)
#define	ID_AA64MMFR0_BIGEND_EL0_SHIFT	16
#define	ID_AA64MMFR0_BIGEND_EL0_MASK	(0xf << ID_AA64MMFR0_BIGEND_EL0_SHIFT)
#define	ID_AA64MMFR0_BIGEND_EL0(x)	((x) & ID_AA64MMFR0_BIGEND_EL0_MASK)
#define	 ID_AA64MMFR0_BIGEND_EL0_FIXED	(0x0 << ID_AA64MMFR0_BIGEND_EL0_SHIFT)
#define	 ID_AA64MMFR0_BIGEND_EL0_MIXED	(0x1 << ID_AA64MMFR0_BIGEND_EL0_SHIFT)
#define	ID_AA64MMFR0_TGRAN16_SHIFT	20
#define	ID_AA64MMFR0_TGRAN16_MASK	(0xf << ID_AA64MMFR0_TGRAN16_SHIFT)
#define	ID_AA64MMFR0_TGRAN16(x)		((x) & ID_AA64MMFR0_TGRAN16_MASK)
#define	 ID_AA64MMFR0_TGRAN16_NONE	(0x0 << ID_AA64MMFR0_TGRAN16_SHIFT)
#define	 ID_AA64MMFR0_TGRAN16_IMPL	(0x1 << ID_AA64MMFR0_TGRAN16_SHIFT)
#define	ID_AA64MMFR0_TGRAN64_SHIFT	24
#define	ID_AA64MMFR0_TGRAN64_MASK	(0xf << ID_AA64MMFR0_TGRAN64_SHIFT)
#define	ID_AA64MMFR0_TGRAN64(x)		((x) & ID_AA64MMFR0_TGRAN64_MASK)
#define	 ID_AA64MMFR0_TGRAN64_IMPL	(0x0 << ID_AA64MMFR0_TGRAN64_SHIFT)
#define	 ID_AA64MMFR0_TGRAN64_NONE	(0xf << ID_AA64MMFR0_TGRAN64_SHIFT)
#define	ID_AA64MMFR0_TGRAN4_SHIFT	28
#define	ID_AA64MMFR0_TGRAN4_MASK	(0xf << ID_AA64MMFR0_TGRAN4_SHIFT)
#define	ID_AA64MMFR0_TGRAN4(x)		((x) & ID_AA64MMFR0_TGRAN4_MASK)
#define	 ID_AA64MMFR0_TGRAN4_IMPL	(0x0 << ID_AA64MMFR0_TGRAN4_SHIFT)
#define	 ID_AA64MMFR0_TGRAN4_NONE	(0xf << ID_AA64MMFR0_TGRAN4_SHIFT)

/* ID_AA64MMFR1_EL1 */
#define	ID_AA64MMFR1_MASK		0xf0000000ffffffffULL
#define	ID_AA64MMFR1_HAFDBS_SHIFT	0
#define	ID_AA64MMFR1_HAFDBS_MASK	(0xf << ID_AA64MMFR1_HAFDBS_SHIFT)
#define	ID_AA64MMFR1_HAFDBS(x)		((x) & ID_AA64MMFR1_HAFDBS_MASK)
#define	 ID_AA64MMFR1_HAFDBS_NONE	(0x0 << ID_AA64MMFR1_HAFDBS_SHIFT)
#define	 ID_AA64MMFR1_HAFDBS_AF		(0x1 << ID_AA64MMFR1_HAFDBS_SHIFT)
#define	 ID_AA64MMFR1_HAFDBS_AF_DBS	(0x2 << ID_AA64MMFR1_HAFDBS_SHIFT)
#define	ID_AA64MMFR1_VMIDBITS_SHIFT	4
#define	ID_AA64MMFR1_VMIDBITS_MASK	(0xf << ID_AA64MMFR1_VMIDBITS_SHIFT)
#define	ID_AA64MMFR1_VMIDBITS(x)	((x) & ID_AA64MMFR1_VMIDBITS_MASK)
#define	 ID_AA64MMFR1_VMIDBITS_8	(0x0 << ID_AA64MMFR1_VMIDBITS_SHIFT)
#define	 ID_AA64MMFR1_VMIDBITS_16	(0x2 << ID_AA64MMFR1_VMIDBITS_SHIFT)
#define	ID_AA64MMFR1_VH_SHIFT		8
#define	ID_AA64MMFR1_VH_MASK		(0xf << ID_AA64MMFR1_VH_SHIFT)
#define	ID_AA64MMFR1_VH(x)		((x) & ID_AA64MMFR1_VH_MASK)
#define	 ID_AA64MMFR1_VH_NONE		(0x0 << ID_AA64MMFR1_VH_SHIFT)
#define	 ID_AA64MMFR1_VH_IMPL		(0x1 << ID_AA64MMFR1_VH_SHIFT)
#define	ID_AA64MMFR1_HPDS_SHIFT		12
#define	ID_AA64MMFR1_HPDS_MASK		(0xf << ID_AA64MMFR1_HPDS_SHIFT)
#define	ID_AA64MMFR1_HPDS(x)		((x) & ID_AA64MMFR1_HPDS_MASK)
#define	 ID_AA64MMFR1_HPDS_NONE		(0x0 << ID_AA64MMFR1_HPDS_SHIFT)
#define	 ID_AA64MMFR1_HPDS_IMPL		(0x1 << ID_AA64MMFR1_HPDS_SHIFT)
#define	ID_AA64MMFR1_LO_SHIFT		16
#define	ID_AA64MMFR1_LO_MASK		(0xf << ID_AA64MMFR1_LO_SHIFT)
#define	ID_AA64MMFR1_LO(x)		((x) & ID_AA64MMFR1_LO_MASK)
#define	 ID_AA64MMFR1_LO_NONE		(0x0 << ID_AA64MMFR1_LO_SHIFT)
#define	 ID_AA64MMFR1_LO_IMPL		(0x1 << ID_AA64MMFR1_LO_SHIFT)
#define	ID_AA64MMFR1_PAN_SHIFT		20
#define	ID_AA64MMFR1_PAN_MASK		(0xf << ID_AA64MMFR1_PAN_SHIFT)
#define	ID_AA64MMFR1_PAN(x)		((x) & ID_AA64MMFR1_PAN_MASK)
#define	 ID_AA64MMFR1_PAN_NONE		(0x0 << ID_AA64MMFR1_PAN_SHIFT)
#define	 ID_AA64MMFR1_PAN_IMPL		(0x1 << ID_AA64MMFR1_PAN_SHIFT)
#define	 ID_AA64MMFR1_PAN_ATS1E1	(0x2 << ID_AA64MMFR1_PAN_SHIFT)
#define	 ID_AA64MMFR1_PAN_EPAN		(0x3 << ID_AA64MMFR1_PAN_SHIFT)
#define	ID_AA64MMFR1_SPECSEI_SHIFT	24
#define	ID_AA64MMFR1_SPECSEI_MASK	(0xf << ID_AA64MMFR1_SPECSEI_SHIFT)
#define	ID_AA64MMFR1_SPECSEI(x)		((x) & ID_AA64MMFR1_SPECSEI_MASK)
#define	 ID_AA64MMFR1_SPECSEI_NONE	(0x0 << ID_AA64MMFR1_SPECSEI_SHIFT)
#define	 ID_AA64MMFR1_SPECSEI_IMPL	(0x1 << ID_AA64MMFR1_SPECSEI_SHIFT)
#define	ID_AA64MMFR1_XNX_SHIFT		28
#define	ID_AA64MMFR1_XNX_MASK		(0xf << ID_AA64MMFR1_XNX_SHIFT)
#define	ID_AA64MMFR1_XNX(x)		((x) & ID_AA64MMFR1_XNX_MASK)
#define	 ID_AA64MMFR1_XNX_NONE		(0x0 << ID_AA64MMFR1_XNX_SHIFT)
#define	 ID_AA64MMFR1_XNX_IMPL		(0x1 << ID_AA64MMFR1_XNX_SHIFT)
#define	ID_AA64MMFR1_ECBHB_SHIFT	60
#define	ID_AA64MMFR1_ECBHB_MASK		(0xfULL << ID_AA64MMFR1_ECBHB_SHIFT)
#define	ID_AA64MMFR1_ECBHB(x)		((x) & ID_AA64MMFR1_ECBHB_MASK)
#define	 ID_AA64MMFR1_ECBHB_NONE	(0x0ULL << ID_AA64MMFR1_ECBHB_SHIFT)
#define	 ID_AA64MMFR1_ECBHB_IMPL	(0x1ULL << ID_AA64MMFR1_ECBHB_SHIFT)

/* ID_AA64PFR0_EL1 */
#define	ID_AA64PFR0_MASK		0xff0fffffffffffffULL
#define	ID_AA64PFR0_EL0_SHIFT		0
#define	ID_AA64PFR0_EL0_MASK		(0xf << ID_AA64PFR0_EL0_SHIFT)
#define	ID_AA64PFR0_EL0(x)		((x) & ID_AA64PFR0_EL0_MASK)
#define	 ID_AA64PFR0_EL0_64		(1 << ID_AA64PFR0_EL0_SHIFT)
#define	 ID_AA64PFR0_EL0_64_32		(2 << ID_AA64PFR0_EL0_SHIFT)
#define	ID_AA64PFR0_EL1_SHIFT		4
#define	ID_AA64PFR0_EL1_MASK		(0xf << ID_AA64PFR0_EL1_SHIFT)
#define	ID_AA64PFR0_EL1(x)		((x) & ID_AA64PFR0_EL1_MASK)
#define	 ID_AA64PFR0_EL1_64		(1 << ID_AA64PFR0_EL1_SHIFT)
#define	 ID_AA64PFR0_EL1_64_32		(2 << ID_AA64PFR0_EL1_SHIFT)
#define	ID_AA64PFR0_EL2_SHIFT		8
#define	ID_AA64PFR0_EL2_MASK		(0xf << ID_AA64PFR0_EL2_SHIFT)
#define	ID_AA64PFR0_EL2(x)		((x) & ID_AA64PFR0_EL2_MASK)
#define	 ID_AA64PFR0_EL2_NONE		(0 << ID_AA64PFR0_EL2_SHIFT)
#define	 ID_AA64PFR0_EL2_64		(1 << ID_AA64PFR0_EL2_SHIFT)
#define	 ID_AA64PFR0_EL2_64_32		(2 << ID_AA64PFR0_EL2_SHIFT)
#define	ID_AA64PFR0_EL3_SHIFT		12
#define	ID_AA64PFR0_EL3_MASK		(0xf << ID_AA64PFR0_EL3_SHIFT)
#define	ID_AA64PFR0_EL3(x)		((x) & ID_AA64PFR0_EL3_MASK)
#define	 ID_AA64PFR0_EL3_NONE		(0 << ID_AA64PFR0_EL3_SHIFT)
#define	 ID_AA64PFR0_EL3_64		(1 << ID_AA64PFR0_EL3_SHIFT)
#define	 ID_AA64PFR0_EL3_64_32		(2 << ID_AA64PFR0_EL3_SHIFT)
#define	ID_AA64PFR0_FP_SHIFT		16
#define	ID_AA64PFR0_FP_MASK		(0xf << ID_AA64PFR0_FP_SHIFT)
#define	ID_AA64PFR0_FP(x)		((x) & ID_AA64PFR0_FP_MASK)
#define	 ID_AA64PFR0_FP_IMPL		(0x0 << ID_AA64PFR0_FP_SHIFT)
#define	 ID_AA64PFR0_FP_NONE		(0xf << ID_AA64PFR0_FP_SHIFT)
#define	ID_AA64PFR0_ADV_SIMD_SHIFT	20
#define	ID_AA64PFR0_ADV_SIMD_MASK	(0xf << ID_AA64PFR0_ADV_SIMD_SHIFT)
#define	ID_AA64PFR0_ADV_SIMD(x)		((x) & ID_AA64PFR0_ADV_SIMD_MASK)
#define	 ID_AA64PFR0_ADV_SIMD_IMPL	(0x0 << ID_AA64PFR0_ADV_SIMD_SHIFT)
#define	 ID_AA64PFR0_ADV_SIMD_NONE	(0xf << ID_AA64PFR0_ADV_SIMD_SHIFT)
#define	ID_AA64PFR0_GIC_BITS		0x4 /* Number of bits in GIC field */
#define	ID_AA64PFR0_GIC_SHIFT		24
#define	ID_AA64PFR0_GIC_MASK		(0xf << ID_AA64PFR0_GIC_SHIFT)
#define	ID_AA64PFR0_GIC(x)		((x) & ID_AA64PFR0_GIC_MASK)
#define	 ID_AA64PFR0_GIC_CPUIF_NONE	(0x0 << ID_AA64PFR0_GIC_SHIFT)
#define	 ID_AA64PFR0_GIC_CPUIF_EN	(0x1 << ID_AA64PFR0_GIC_SHIFT)
#define	ID_AA64PFR0_RAS_SHIFT		28
#define	ID_AA64PFR0_RAS_MASK		(0xfULL << ID_AA64PFR0_RAS_SHIFT)
#define	ID_AA64PFR0_RAS(x)		((x) & ID_AA64PFR0_RAS_MASK)
#define	 ID_AA64PFR0_RAS_NONE		(0x0ULL << ID_AA64PFR0_RAS_SHIFT)
#define	 ID_AA64PFR0_RAS_IMPL		(0x1ULL << ID_AA64PFR0_RAS_SHIFT)
#define	 ID_AA64PFR0_RAS_IMPL_V1P1	(0x2ULL << ID_AA64PFR0_RAS_SHIFT)
#define	ID_AA64PFR0_SVE_SHIFT		32
#define	ID_AA64PFR0_SVE_MASK		(0xfULL << ID_AA64PFR0_SVE_SHIFT)
#define	ID_AA64PFR0_SVE(x)		((x) & ID_AA64PFR0_SVE_MASK)
#define	 ID_AA64PFR0_SVE_NONE		(0x0ULL << ID_AA64PFR0_SVE_SHIFT)
#define	 ID_AA64PFR0_SVE_IMPL		(0x1ULL << ID_AA64PFR0_SVE_SHIFT)
#define	ID_AA64PFR0_SEL2_SHIFT		36
#define	ID_AA64PFR0_SEL2_MASK		(0xfULL << ID_AA64PFR0_SEL2_SHIFT)
#define	ID_AA64PFR0_SEL2(x)		((x) & ID_AA64PFR0_SEL2_MASK)
#define	 ID_AA64PFR0_SEL2_NONE		(0x0ULL << ID_AA64PFR0_SEL2_SHIFT)
#define	 ID_AA64PFR0_SEL2_IMPL		(0x1ULL << ID_AA64PFR0_SEL2_SHIFT)
#define	ID_AA64PFR0_MPAM_SHIFT		40
#define	ID_AA64PFR0_MPAM_MASK		(0xfULL << ID_AA64PFR0_MPAM_SHIFT)
#define	ID_AA64PFR0_MPAM(x)		((x) & ID_AA64PFR0_MPAM_MASK)
#define	 ID_AA64PFR0_MPAM_NONE		(0x0ULL << ID_AA64PFR0_MPAM_SHIFT)
#define	 ID_AA64PFR0_MPAM_IMPL		(0x1ULL << ID_AA64PFR0_MPAM_SHIFT)
#define	ID_AA64PFR0_AMU_SHIFT		44
#define	ID_AA64PFR0_AMU_MASK		(0xfULL << ID_AA64PFR0_AMU_SHIFT)
#define	ID_AA64PFR0_AMU(x)		((x) & ID_AA64PFR0_AMU_MASK)
#define	 ID_AA64PFR0_AMU_NONE		(0x0ULL << ID_AA64PFR0_AMU_SHIFT)
#define	 ID_AA64PFR0_AMU_IMPL		(0x1ULL << ID_AA64PFR0_AMU_SHIFT)
#define	ID_AA64PFR0_DIT_SHIFT		48
#define	ID_AA64PFR0_DIT_MASK		(0xfULL << ID_AA64PFR0_DIT_SHIFT)
#define	ID_AA64PFR0_DIT(x)		((x) & ID_AA64PFR0_DIT_MASK)
#define	 ID_AA64PFR0_DIT_UNKNOWN	(0x0ULL << ID_AA64PFR0_DIT_SHIFT)
#define	 ID_AA64PFR0_DIT_IMPL		(0x1ULL << ID_AA64PFR0_DIT_SHIFT)
#define	ID_AA64PFR0_CSV2_SHIFT		56
#define	ID_AA64PFR0_CSV2_MASK		(0xfULL << ID_AA64PFR0_CSV2_SHIFT)
#define	ID_AA64PFR0_CSV2(x)		((x) & ID_AA64PFR0_CSV2_MASK)
#define	 ID_AA64PFR0_CSV2_UNKNOWN	(0x0ULL << ID_AA64PFR0_CSV2_SHIFT)
#define	 ID_AA64PFR0_CSV2_IMPL		(0x1ULL << ID_AA64PFR0_CSV2_SHIFT)
#define	 ID_AA64PFR0_CSV2_SCXT		(0x2ULL << ID_AA64PFR0_CSV2_SHIFT)
#define	 ID_AA64PFR0_CSV2_HCXT		(0x3ULL << ID_AA64PFR0_CSV2_SHIFT)
#define	ID_AA64PFR0_CSV3_SHIFT		60
#define	ID_AA64PFR0_CSV3_MASK		(0xfULL << ID_AA64PFR0_CSV3_SHIFT)
#define	ID_AA64PFR0_CSV3(x)		((x) & ID_AA64PFR0_CSV3_MASK)
#define	 ID_AA64PFR0_CSV3_UNKNOWN	(0x0ULL << ID_AA64PFR0_CSV3_SHIFT)
#define	 ID_AA64PFR0_CSV3_IMPL		(0x1ULL << ID_AA64PFR0_CSV3_SHIFT)

/* ID_AA64PFR1_EL1 */
#define	ID_AA64PFR1_MASK		0x000000000000ffffULL
#define	ID_AA64PFR1_BT_SHIFT		0
#define	ID_AA64PFR1_BT_MASK		(0xf << ID_AA64PFR1_BT_SHIFT)
#define	ID_AA64PFR1_BT(x)		((x) & ID_AA64PFR1_BT_MASK)
#define	 ID_AA64PFR1_BT_NONE		(0 << ID_AA64PFR1_BT_SHIFT)
#define	 ID_AA64PFR1_BT_IMPL		(1 << ID_AA64PFR1_BT_SHIFT)
#define	ID_AA64PFR1_SBSS_SHIFT		4
#define	ID_AA64PFR1_SBSS_MASK		(0xf << ID_AA64PFR1_SBSS_SHIFT)
#define	ID_AA64PFR1_SBSS(x)		((x) & ID_AA64PFR1_SBSS_MASK)
#define	 ID_AA64PFR1_SBSS_NONE		(0 << ID_AA64PFR1_SBSS_SHIFT)
#define	 ID_AA64PFR1_SBSS_PSTATE	(1 << ID_AA64PFR1_SBSS_SHIFT)
#define	 ID_AA64PFR1_SBSS_PSTATE_MSR	(2 << ID_AA64PFR1_SBSS_SHIFT)
#define	ID_AA64PFR1_MTE_SHIFT		8
#define	ID_AA64PFR1_MTE_MASK		(0xf << ID_AA64PFR1_MTE_SHIFT)
#define	ID_AA64PFR1_MTE(x)		((x) & ID_AA64PFR1_MTE_MASK)
#define	 ID_AA64PFR1_MTE_NONE		(0 << ID_AA64PFR1_MTE_SHIFT)
#define	 ID_AA64PFR1_MTE_IMPL		(1 << ID_AA64PFR1_MTE_SHIFT)
#define	ID_AA64PFR1_RAS_FRAC_SHIFT	12
#define	ID_AA64PFR1_RAS_FRAC_MASK	(0xf << ID_AA64PFR1_RAS_FRAC_SHIFT)
#define	ID_AA64PFR1_RAS_FRAC(x)		((x) & ID_AA64PFR1_RAS_FRAC_MASK)
#define	 ID_AA64PFR1_RAS_FRAC_NONE	(0 << ID_AA64PFR1_RAS_FRAC_SHIFT)
#define	 ID_AA64PFR1_RAS_FRAC_IMPL	(1 << ID_AA64PFR1_RAS_FRAC_SHIFT)

/* MAIR_EL1 - Memory Attribute Indirection Register */
#define	MAIR_ATTR_MASK(idx)	(0xff << ((n)* 8))
#define	MAIR_ATTR(attr, idx) ((attr) << ((idx) * 8))
#define	 MAIR_DEVICE_nGnRnE	0x00
#define	 MAIR_NORMAL_NC		0x44
#define	 MAIR_NORMAL_WT		0x88
#define	 MAIR_NORMAL_WB		0xff

/* PAR_EL1 - Physical Address Register */
#define	PAR_F_SHIFT		0
#define	PAR_F			(0x1 << PAR_F_SHIFT)
#define	PAR_SUCCESS(x)		(((x) & PAR_F) == 0)
/* When PAR_F == 0 (success) */
#define	PAR_SH_SHIFT		7
#define	PAR_SH_MASK		(0x3 << PAR_SH_SHIFT)
#define	PAR_NS_SHIFT		9
#define	PAR_NS_MASK		(0x3 << PAR_NS_SHIFT)
#define	PAR_PA_SHIFT		12
#define	PAR_PA_MASK		0x0000fffffffff000
#define	PAR_ATTR_SHIFT		56
#define	PAR_ATTR_MASK		(0xff << PAR_ATTR_SHIFT)
/* When PAR_F == 1 (aborted) */
#define	PAR_FST_SHIFT		1
#define	PAR_FST_MASK		(0x3f << PAR_FST_SHIFT)
#define	PAR_PTW_SHIFT		8
#define	PAR_PTW_MASK		(0x1 << PAR_PTW_SHIFT)
#define	PAR_S_SHIFT		9
#define	PAR_S_MASK		(0x1 << PAR_S_SHIFT)

/* SCTLR_EL1 - System Control Register */
#define	SCTLR_RES0	0xffffffffc8222400	/* Reserved, write 0 */
#define	SCTLR_RES1	0x0000000030d00800	/* Reserved, write 1 */

#define	SCTLR_M		0x0000000000000001
#define	SCTLR_A		0x0000000000000002
#define	SCTLR_C		0x0000000000000004
#define	SCTLR_SA	0x0000000000000008
#define	SCTLR_SA0	0x0000000000000010
#define	SCTLR_CP15BEN	0x0000000000000020
#define	SCTLR_THEE	0x0000000000000040
#define	SCTLR_ITD	0x0000000000000080
#define	SCTLR_SED	0x0000000000000100
#define	SCTLR_UMA	0x0000000000000200
#define	SCTLR_I		0x0000000000001000
#define	SCTLR_EnDB	0x0000000000002000
#define	SCTLR_DZE	0x0000000000004000
#define	SCTLR_UCT	0x0000000000008000
#define	SCTLR_nTWI	0x0000000000010000
#define	SCTLR_nTWE	0x0000000000040000
#define	SCTLR_WXN	0x0000000000080000
#define	SCTLR_SPAN	0x0000000000800000
#define	SCTLR_EOE	0x0000000001000000
#define	SCTLR_EE	0x0000000002000000
#define	SCTLR_UCI	0x0000000004000000
#define	SCTLR_EnDA	0x0000000008000000
#define	SCTLR_EnIB	0x0000000040000000
#define	SCTLR_EnIA	0x0000000080000000

/* SPSR_EL1 */
/*
 * When the exception is taken in AArch64:
 * M[4]   is 0 for AArch64 mode
 * M[3:2] is the exception level
 * M[1]   is unused
 * M[0]   is the SP select:
 *         0: always SP0
 *         1: current ELs SP
 */
#define	PSR_M_EL0t	0x00000000
#define	PSR_M_EL1t	0x00000004
#define	PSR_M_EL1h	0x00000005
#define	PSR_M_EL2t	0x00000008
#define	PSR_M_EL2h	0x00000009
#define	PSR_M_MASK	0x0000001f

#define	PSR_F		0x00000040
#define	PSR_I		0x00000080
#define	PSR_A		0x00000100
#define	PSR_D		0x00000200
#define	PSR_BTYPE	0x00000c00
#define	PSR_SSBS	0x00001000
#define	PSR_IL		0x00100000
#define	PSR_SS		0x00200000
#define	PSR_PAN		0x00400000
#define	PSR_UAO		0x00800000
#define	PSR_DIT		0x01000000
#define	PSR_TCO		0x02000000
#define	PSR_V		0x10000000
#define	PSR_C		0x20000000
#define	PSR_Z		0x40000000
#define	PSR_N		0x80000000

/* TCR_EL1 - Translation Control Register */
#define	TCR_AS		(1UL << 36)

#define	TCR_IPS_SHIFT	32
#define	TCR_IPS_32BIT	(0UL << TCR_IPS_SHIFT)
#define	TCR_IPS_36BIT	(1UL << TCR_IPS_SHIFT)
#define	TCR_IPS_40BIT	(2UL << TCR_IPS_SHIFT)
#define	TCR_IPS_42BIT	(3UL << TCR_IPS_SHIFT)
#define	TCR_IPS_44BIT	(4UL << TCR_IPS_SHIFT)
#define	TCR_IPS_48BIT	(5UL << TCR_IPS_SHIFT)

#define	TCR_TG1_SHIFT	30
#define	TCR_TG1_16K	(1UL << TCR_TG1_SHIFT)
#define	TCR_TG1_4K	(2UL << TCR_TG1_SHIFT)
#define	TCR_TG1_64K	(3UL << TCR_TG1_SHIFT)

#define	TCR_SH1_SHIFT	28
#define	TCR_SH1_IS	(0x3UL << TCR_SH1_SHIFT)
#define	TCR_ORGN1_SHIFT	26
#define	TCR_ORGN1_WBWA	(0x1UL << TCR_ORGN1_SHIFT)
#define	TCR_IRGN1_SHIFT	24
#define	TCR_IRGN1_WBWA	(0x1UL << TCR_IRGN1_SHIFT)

#define	TCR_A1		(1UL << 22)

#define	TCR_TG0_SHIFT	14
#define	TCR_TG0_4K	(0UL << TCR_TG0_SHIFT)
#define	TCR_TG0_64K	(1UL << TCR_TG0_SHIFT)
#define	TCR_TG0_16K	(2UL << TCR_TG0_SHIFT)

#define	TCR_SH0_SHIFT	12
#define	TCR_SH0_IS	(0x3UL << TCR_SH0_SHIFT)
#define	TCR_ORGN0_SHIFT	10
#define	TCR_ORGN0_WBWA	(0x1UL << TCR_ORGN0_SHIFT)
#define	TCR_IRGN0_SHIFT	8
#define	TCR_IRGN0_WBWA	(0x1UL << TCR_IRGN0_SHIFT)

#define	TCR_CACHE_ATTRS	((TCR_IRGN0_WBWA | TCR_IRGN1_WBWA) |\
				(TCR_ORGN0_WBWA | TCR_ORGN1_WBWA))
#define	TCR_SMP_ATTRS	(TCR_SH0_IS | TCR_SH1_IS)

#define	TCR_T1SZ_SHIFT	16
#define	TCR_T0SZ_SHIFT	0
#define	TCR_T1SZ(x)	((x) << TCR_T1SZ_SHIFT)
#define	TCR_T0SZ(x)	((x) << TCR_T0SZ_SHIFT)
#define	TCR_TxSZ(x)	(TCR_T1SZ(x) | TCR_T0SZ(x))

/* Monitor Debug System Control Register */
#define	DBG_MDSCR_SS	(0x1 << 0)
#define	DBG_MDSCR_TDCC	(0x1 << 12)
#define	DBG_MDSCR_KDE	(0x1 << 13)
#define	DBG_MDSCR_MDE	(0x1 << 15)

/* Performance Monitoring Counters */
#define	PMCR_E		(1 << 0) /* Enable all counters */
#define	PMCR_P		(1 << 1) /* Reset all counters */
#define	PMCR_C		(1 << 2) /* Clock counter reset */
#define	PMCR_D		(1 << 3) /* CNTR counts every 64 clk cycles */
#define	PMCR_X		(1 << 4) /* Export to ext. monitoring (ETM) */
#define	PMCR_DP		(1 << 5) /* Disable CCNT if non-invasive debug*/
#define	PMCR_LC		(1 << 6) /* Long cycle count enable */
#define	PMCR_IMP_SHIFT	24 /* Implementer code */
#define	PMCR_IMP_MASK	(0xff << PMCR_IMP_SHIFT)
#define	PMCR_IDCODE_SHIFT	16 /* Identification code */
#define	PMCR_IDCODE_MASK	(0xff << PMCR_IDCODE_SHIFT)
#define	 PMCR_IDCODE_CORTEX_A57	0x01
#define	 PMCR_IDCODE_CORTEX_A72	0x02
#define	 PMCR_IDCODE_CORTEX_A53	0x03
#define	PMCR_N_SHIFT	11       /* Number of counters implemented */
#define	PMCR_N_MASK	(0x1f << PMCR_N_SHIFT)

/* Individual CPUs are probably best IDed by everything but the revision. */
#define	CPU_ID_CPU_MASK		0xfffffff0

/* ARM64 CPUs */
#define	CPU_ID_CORTEX_A53	0x410fd030
#define	CPU_ID_CORTEX_A53_R1	0x411fd030
#define	CPU_ID_CORTEX_A53_MASK	0xff0ffff0
#define	CPU_ID_CORTEX_A57	0x410fd070
#define	CPU_ID_CORTEX_A57_R1	0x411fd070
#define	CPU_ID_CORTEX_A57_MASK	0xff0ffff0
#define	CPU_ID_CORTEX_A72	0x410fd080
#define	CPU_ID_CORTEX_A72_R1	0x411fd080
#define	CPU_ID_CORTEX_A57_MASK	0xff0ffff0

#define I_bit (1 << 7)		/* IRQ disable */
#define F_bit 0			/* FIQ disable - not actually used */

#endif /* !_MACHINE_ARMREG_H_ */
