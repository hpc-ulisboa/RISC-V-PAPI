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

typedef enum {
    SIFIVE_U74_MC   // SiFive U74-MC Core
} pfm_riscv_architecture_t;

typedef struct {
    pfm_riscv_architecture_t architecture;
} pfm_riscv_config_t;

#define RISCV_PLM (0x0)

extern pfm_riscv_config_t pfm_riscv_cfg;

extern int pfm_riscv_get_perf_encoding(void *this, pfmlib_event_desc_t *e);
extern int pfm_riscv_detect(void *this);
extern int pfm_riscv_get_encoding(void *this, pfmlib_event_desc_t *e);
extern int pfm_riscv_get_event_first(void *this);
extern int pfm_riscv_get_event_next(void *this, int idx);
extern int pfm_riscv_event_is_valid(void *this, int pidx);
extern int pfm_riscv_validate_table(void *this, FILE *fp);
extern int pfm_riscv_get_event_info(void *this, int idx, pfm_event_info_t *info);


#endif /* __PFMLIB_RISCV_PRIV_H__ */
