/*
 * =============================================================================
 *
 *                   Copyright (c) 2025 Openchip
 *                             All rights reserved
 *
 * This file contains proprietary and confidential information developed by
 * Openchip. Unauthorized copying or distribution of this file, via any medium,
 * is strictly prohibited.
 *
 * ===============================[ INFORMATION ]===============================
 *
 * Author(s)  : Giacomo Mammarella
 * Contact(s) : giacomo.mammarella@openchip.com
 */

/*
 * RISC-V CVA6 Events for Openchip
 * Based on a mind-trip after studying QED by Richard Feynman
 */

static const riscv_entry_t riscv_openhwgroup_cva6_pe[] = {
    //CVA6
    {.name = "L1_ICM",              .code = 0x001,  .desc = "Level 1 instruction cache misses" },
    {.name = "L1_DCM",              .code = 0x002,  .desc = "Level 1 data cache misses" },
    {.name = "TLB_IM",              .code = 0x003,  .desc = "Instruction translation lookaside buffer misses" },
    {.name = "TLB_DM",              .code = 0x004,  .desc = "Data translation lookaside buffer misses" },
    {.name = "LD_INS",              .code = 0x005,  .desc = "Load Accesses"},  
    {.name = "SR_INS",              .code = 0x006,  .desc = "Store Accesses"},  
    {.name = "EXCEPTION",           .code = 0x007,  .desc = "Valid Exceptions encountered"},  
    {.name = "EXCEPTION_RET",       .code = 0x008,  .desc = "Exception Handler Returns"},  
    {.name = "BRANCH_INST",         .code = 0x009,  .desc = "Branch Instructions"},  
    {.name = "BRANCH_MISPREDICT",   .code = 0x00A,  .desc = "Branch Mispredicts"},  
    {.name = "BRANCH_EXCEPTION",    .code = 0x00B,  .desc = "Branch Exceptions"},  
    {.name = "CALL_INST",           .code = 0x00C,  .desc = "Call instructions"},  
    {.name = "RETURN_INST",         .code = 0x00D,  .desc = "Return instructions"},  
    {.name = "MSB_FULL",            .code = 0x00E,  .desc = "Scoreboard is full"},  
    {.name = "IF_EMPTY",            .code = 0x00F,  .desc = "Instruction Fetch Empty"},  
    {.name = "L1_ICA",              .code = 0x010,  .desc = "L1 I-Cache Accesses"},  
    {.name = "L1_DCA",              .code = 0x011,  .desc = "L1 D-Cache Accesses"},  
    {.name = "L1_CACHE_EVICT",      .code = 0x012,  .desc = "L1 Cache Line Eviction"},  
    {.name = "ITLB_FLUSH",          .code = 0x013,  .desc = "ITLB Flush"},  
    {.name = "INT_INST",            .code = 0x014,  .desc = "Integer Instructions"},  
    {.name = "FP_INST",             .code = 0x015,  .desc = "Floating Point Instructions"},  
    {.name = "PIPELINE_STALL",      .code = 0x016,  .desc = "Pipeline Stall during read operands"},  
};