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

#define RISCV_PLM (PFM_PLM0 | PFM_PLM3 | PFM_PLMH)

extern int pfm_riscv_detect_sifive_u74(void *this);

#endif /* __PFMLIB_RISCV_PRIV_H__ */
