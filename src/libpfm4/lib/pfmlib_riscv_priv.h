/*
 * Copyright (c) 2023 INESC-ID, Instituto Superior Técnico, Universidade de Lisboa
 * Created by Tiago Rocha <tiagolopesrocha@tecnico.ulisboa.pt>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

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
    SIFIVE_U74_MC,   // SiFive U74-MC Core
    SOPHON_SG2042,   // Sophon SG2042
    EPI_EPAC_AVISPADO,   // EPI EPAC Avispado+VPU
    SPACEMIT_K1_8 // SpacemiT K1 8
} pfm_riscv_implementation_t;

typedef struct {
    pfm_riscv_implementation_t implementation;
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
