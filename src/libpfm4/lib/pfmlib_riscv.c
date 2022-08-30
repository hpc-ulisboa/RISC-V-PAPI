/*
 * pfmlib_riscv.c : support for RISC-V processors
 *
 */

/* private headers */
#include "pfmlib_priv.h" /* library private */
#include "pfmlib_riscv_priv.h"

#include "events/riscv_sifive_u74_events.h"; /* SiFive U74 event tables */

static int pfm_riscv_detect_sifive_u74(void *this)
{
    return PFM_SUCCESS;
}

int pfm_riscv_get_encoding(void *this, pfmlib_event_desc_t *e)
{
    return PFM_SUCCESS;
}

int pfm_riscv_get_event_first(void *this)
{
    return 0;
}

int pfm_riscv_get_event_next(void *this, int idx)
{
    pfmlib_pmu_t *p = this;

    if (idx >= (p->pme_count - 1))
        return -1;

    return idx + 1;
}

int pfm_riscv_event_is_valid(void *this, int pidx)
{
    pfmlib_pmu_t *p = this;
    return pidx >= 0 && pidx < p->pme_count;
}

int pfm_riscv_validate_table(void *this, FILE *fp)
{
    pfmlib_pmu_t *pmu = this;
    const riscv_entry_t *pe = this_pe(this);
    int i, j, error = 0;

    for (i = 0; i < pmu->pme_count; i++)
    {
        if (!pe[i].name)
        {
            fprintf(fp, "pmu: %s event%d: :: no name (prev event was %s)\n", pmu->name, i, i > 1 ? pe[i - 1].name : "??");
            error++;
        }
        if (!pe[i].desc)
        {
            fprintf(fp, "pmu: %s event%d: %s :: no description\n", pmu->name, i, pe[i].name);
            error++;
        }
        for (j = i + 1; j < pmu->pme_count; j++)
        {
            if (pe[i].code == pe[j].code)
            {
                fprintf(fp, "pmu: %s events %s and %s have the same code 0x%x\n", pmu->name, pe[i].name, pe[j].name, pe[i].code);
                error++;
            }
        }
    }
    return error ? PFM_ERR_INVAL : PFM_SUCCESS;
}

int pfm_riscv_get_event_info(void *this, int idx, pfm_event_info_t *info)
{
    pfmlib_pmu_t *pmu = this;
    const riscv_entry_t *pe = this_pe(this);

    info->name = pe[idx].name;
    info->desc = pe[idx].desc;
    info->code = pe[idx].code;
    info->idx = idx;
    info->pmu = pmu->pmu;

    /* no attributes defined for ARM yet */
    info->nattrs = 0;

    return PFM_SUCCESS;
}

/* RISC-V SiFive U74 support */
pfmlib_pmu_t riscv_sifive_u74_support = {
    .desc = "SiFive U74",
    .name = "riscv_u74",
    .pmu = PFM_PMU_RISCV_SIFIVE_U74,
    .pme_count = LIBPFM_ARRAY_SIZE(riscv_sifive_u74_pe),
    .type = PFM_PMU_TYPE_CORE,
    .supported_plm = RISCV_PLM,
    .pe = riscv_sifive_u74_pe,
    .pmu_detect = pfm_riscv_detect_sifive_u74,
    .num_cntrs = 2,
    .num_fixed_cntrs = 2,

    .get_event_encoding[PFM_OS_NONE] = pfm_riscv_get_encoding,
    PFMLIB_ENCODE_PERF(pfm_riscv_get_perf_encoding),
    .get_event_first = pfm_riscv_get_event_first,
    .get_event_next = pfm_riscv_get_event_next,
    .event_is_valid = pfm_riscv_event_is_valid,
    .validate_table = pfm_riscv_validate_table,
    .get_event_info = pfm_riscv_get_event_info,
    // .get_event_attr_info = pfm_riscv_get_event_attr_info,
    // PFMLIB_VALID_PERF_PATTRS(pfm_riscv_perf_validate_pattrs),
    // .get_event_nattrs = pfm_riscv_get_event_nattrs,
};
