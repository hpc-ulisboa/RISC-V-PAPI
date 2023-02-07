/*
 * pfmlib_riscv_perf_event.c : perf_event RISC-V functions
 *
 */

/* private headers */
#include "pfmlib_priv.h" /* library private */
#include "pfmlib_riscv_priv.h"
#include "pfmlib_perf_event_priv.h"

int pfm_riscv_get_perf_encoding(void *this, pfmlib_event_desc_t *e)
{
    pfmlib_pmu_t *pmu = this;
    pfm_riscv_reg_t reg;
    struct perf_event_attr *attr = e->os_data;
    int ret;

    if (!pmu->get_event_encoding[PFM_OS_NONE])
        return PFM_ERR_NOTSUPP;

    /*
     * use generic raw encoding function first
     */
    ret = pmu->get_event_encoding[PFM_OS_NONE](this, e);
    if (ret != PFM_SUCCESS)
        return ret;

    if (e->count > 1)
    {
        DPRINT("%s: unsupported count=%d\n", e->count);
        return PFM_ERR_NOTSUPP;
    }

    attr->type = PERF_TYPE_RAW;
    reg.val = e->codes[0];

    attr->config = reg.val;

    // risc-v can not set privilege levels
    attr->exclude_hv = 0;
    attr->exclude_kernel = 0;
    attr->exclude_user = 0;

    return PFM_SUCCESS;
}