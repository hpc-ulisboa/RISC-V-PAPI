/*
 * =============================================================================
 *
 *                   Copyright (c) 2024 Openchip
 *                             All rights reserved
 *
 * This file contains Openchip proprietary and confidential information.
 * Unauthorized copying or distribution of this file, via any medium, is strictly prohibited.
 *
 * ===============================[ INFORMATION ]===============================
 *
 * Author(s)  : Giacomo Mammarella
 * Contact(s) : giacomo.mammarella@openchip.com
 */

/* private headers */
#include "pfmlib_priv.h"			/* library private */
#include "pfmlib_riscv_priv.h"
#include "events/riscv_openhwgroup_cva6_events.h"

static int pfm_riscv_detect_openhwgroup_cva6(void *this)
{
    int ret;

    ret = pfm_riscv_detect(this);
    if (ret != PFM_SUCCESS)
        return PFM_ERR_NOTSUPP;
    
    if (pfm_riscv_cfg.implementation == OPENHWGROUP_CVA6) 
        return PFM_SUCCESS;

    return PFM_ERR_NOTSUPP;
}

/* RISC-V Openhwgroup CVA6 support */
pfmlib_pmu_t riscv_openhwgroup_cva6_support = {
    .desc = "RISC-V OpenHWGroup CVA6",
    .name = "riscv_openhwgroup_cva6",
    .pmu = PAPI_VENDOR_RISCV_OPENHWGROUP,
    .pme_count = LIBPFM_ARRAY_SIZE(riscv_openhwgroup_cva6_pe),
    .type = PFM_PMU_TYPE_CORE,
    .supported_plm = RISCV_PLM,
    .pe = riscv_openhwgroup_cva6_pe,
    .pmu_detect = pfm_riscv_detect_openhwgroup_cva6,
    .num_cntrs = 6,
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
