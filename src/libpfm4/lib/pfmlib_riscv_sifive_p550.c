/*
 * =============================================================================
 *
 *                   Copyright (c) 2025 BSC
 *                             All rights reserved
 *
 * This file contains BSC proprietary and confidential information and has
 * been developed by BSC within the EPI-SGA1 Project (GA 826647).
 * The permission rights for this file are governed by the EPI Grant Agreement
 * and the EPI Consortium Agreement.
 *
 * ===============================[ INFORMATION ]===============================
 *
 * Author(s)  : Rafel Albert Esqueu
 * Contact(s) : rafel.brosesqueu@bsc.es
 */

/* private headers */
#include "pfmlib_priv.h"			/* library private */
#include "pfmlib_riscv_priv.h"
#include "events/riscv_sifive_p550_events.h"

static int pfm_riscv_detect_sifive_p550(void *this)
{
    int ret;

    ret = pfm_riscv_detect(this);
    if (ret != PFM_SUCCESS)
        return PFM_ERR_NOTSUPP;
    
    if (pfm_riscv_cfg.implementation == SIFIVE_P550)
        return PFM_SUCCESS;

    return PFM_ERR_NOTSUPP;
}

/* RISC-V SiFive P550 support */
pfmlib_pmu_t riscv_sifive_p550_support = {
    .desc = "RISC-V SiFive P550",
    .name = "riscv_sifive_p550",
    .pmu = PFM_PMU_RISCV_SIFIVE_P550,
    .pme_count = LIBPFM_ARRAY_SIZE(riscv_sifive_p550_pe),
    .type = PFM_PMU_TYPE_CORE,
    .supported_plm = RISCV_PLM,
    .pe = riscv_sifive_p550_pe,
    .pmu_detect = pfm_riscv_detect_sifive_p550,
    .num_cntrs = 2,
    .num_fixed_cntrs = 2,
    .max_encoding = 1,

    .get_event_encoding[PFM_OS_NONE] = pfm_riscv_get_encoding,
    PFMLIB_ENCODE_PERF(pfm_riscv_get_perf_encoding),
    .get_event_first = pfm_riscv_get_event_first,
    .get_event_next = pfm_riscv_get_event_next,
    .event_is_valid = pfm_riscv_event_is_valid,
    .validate_table = pfm_riscv_validate_table,
    .get_event_info = pfm_riscv_get_event_info,
};
