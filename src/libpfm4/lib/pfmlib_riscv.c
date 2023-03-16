/*
 * pfmlib_riscv.c : support for RISC-V processors
 *
 */

#include <stdlib.h>

/* private headers */
#include "pfmlib_priv.h" /* library private */
#include "pfmlib_riscv_priv.h"

#include "events/riscv_sifive_u74_events.h" /* SiFive U74 event tables */

pfm_riscv_config_t pfm_riscv_cfg;

#ifdef CONFIG_PFMLIB_OS_LINUX
/*
 * helper function to retrieve one value from /proc/cpuinfo
 * for internal libpfm use only
 * attr: the attribute (line) to look for
 * ret_buf: a buffer to store the value of the attribute (as a string)
 * maxlen : number of bytes of capacity in ret_buf
 *
 * ret_buf is null terminated.
 *
 * Return:
 * 	0 : attribute found, ret_buf populated
 * 	-1: attribute not found
 */

static int
pfmlib_getcpuinfo_attr(const char *attr, char *ret_buf, size_t maxlen)
{
	FILE *fp = NULL;
	int ret = -1;
	size_t attr_len, buf_len = 0;
	char *p, *value = NULL;
	char *buffer = NULL;

	if (attr == NULL || ret_buf == NULL || maxlen < 1)
		return -1;

	attr_len = strlen(attr);

	fp = fopen("/proc/cpuinfo", "r");
	if (fp == NULL)
		return -1;

	while(pfmlib_getl(&buffer, &buf_len, fp) != -1){

		/* skip  blank lines */
		if (*buffer == '\n')
			continue;

		p = strchr(buffer, ':');
		if (p == NULL)
			goto error;

		/*
		 * p+2: +1 = space, +2= firt character
		 * strlen()-1 gets rid of \n
		 */
		*p = '\0';
		value = p+2;

		value[strlen(value)-1] = '\0';

		if (!strncmp(attr, buffer, attr_len))
			break;
	}
	strncpy(ret_buf, value, maxlen-1);
	ret_buf[maxlen-1] = '\0';
	ret = 0;
error:
	free(buffer);
	fclose(fp);
	return ret;
}
#else
static int
pfmlib_getcpuinfo_attr(const char *attr, char *ret_buf, size_t maxlen)
{
	return -1;
}
#endif

int pfm_riscv_detect(void *this)
{
    int ret;
    char buffer[128];

    ret = pfmlib_getcpuinfo_attr("uarch", buffer, sizeof(buffer));
    if (ret == -1)
        return PFM_ERR_NOTSUPP;
    if (strcmp(buffer, "sifive,u74-mc") == 0)
        pfm_riscv_cfg.architecture = SIFIVE_U74_MC;
    else
        return PFM_ERR_NOTSUPP;

    return PFM_SUCCESS;
}

static void pfm_riscv_display_reg(void *this, pfmlib_event_desc_t *e, pfm_riscv_reg_t reg)
{
    __pfm_vbprintf("[0x%x] %s\n", reg.val, e->fstr);
}

int pfm_riscv_get_encoding(void *this, pfmlib_event_desc_t *e)
{
    const riscv_entry_t *pe = this_pe(this);
    pfm_riscv_reg_t reg;

    reg.val = pe[e->event].code;

    evt_strcat(e->fstr, "%s", pe[e->event].name);

    e->codes[0] = reg.val;
    e->count = 1;

    pfm_riscv_display_reg(this, e, reg);

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
    info->equiv = NULL;
    info->idx = idx;
    info->pmu = pmu->pmu;

    /* no attributes defined for ARM yet */
    info->nattrs = 0;

    return PFM_SUCCESS;
}
