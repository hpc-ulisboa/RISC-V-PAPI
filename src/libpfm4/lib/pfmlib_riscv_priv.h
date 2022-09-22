#ifndef __PFMLIB_RISCV_PRIV_H__
#define __PFMLIB_RISCV_PRIV_H__

/*
 * This file contains the definitions used for RISC-V processors
 */
typedef struct
{
    const char *name;  /* event name */
    unsigned int code; /* event code */
    const char *desc;  /* event description */
} riscv_entry_t;

typedef union pfm_riscv_reg
{
    unsigned int val;
} pfm_riscv_reg_t;

#define RISCV_PLM (PFM_PLM0 | PFM_PLM3 | PFM_PLMH)

extern int pfm_riscv_get_perf_encoding(void *this, pfmlib_event_desc_t *e);

#endif /* __PFMLIB_RISCV_PRIV_H__ */
