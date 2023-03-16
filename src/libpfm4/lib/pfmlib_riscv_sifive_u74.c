/*
 * pfmlib_riscv_sifive_u74.c : support for SiFive U74-MC processor
 */

/* private headers */
#include "pfmlib_priv.h"			/* library private */
#include "pfmlib_riscv_priv.h"
#include "events/riscv_sifive_u74_events.h"

static int pfm_riscv_detect_sifive_u74(void *this)
{
    int ret;

    ret = pfm_riscv_detect(this);
    if (ret != PFM_SUCCESS)
        return PFM_ERR_NOTSUPP;
    
    if (pfm_riscv_cfg.architecture == SIFIVE_U74_MC)
        return PFM_SUCCESS;

    return PFM_ERR_NOTSUPP;
}

/* RISC-V SiFive U74 support */
pfmlib_pmu_t riscv_sifive_u74_support = {
    .desc = "RISC-V SiFive U74",
    .name = "riscv_sifive_u74",
    .pmu = PFM_PMU_RISCV_SIFIVE_U74,
    .pme_count = LIBPFM_ARRAY_SIZE(riscv_sifive_u74_pe),
    .type = PFM_PMU_TYPE_CORE,
    .supported_plm = RISCV_PLM,
    .pe = riscv_sifive_u74_pe,
    .pmu_detect = pfm_riscv_detect_sifive_u74,
    .num_cntrs = 2, // TODO_RISCV: check if this should not be 4
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
