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
    {.name = "L1_ICM",
     .code = 0x001,
     .desc = "Level 1 instruction cache misses" },
    {.name = "L1_DCM",
     .code = 0x002,
     .desc = "Level 1 data cache misses" },
    {.name = "TLB_IM",
     .code = 0x003,
     .desc = "Instruction translation lookaside buffer misses" },
    {.name = "TLB_DM",
     .code = 0x004,
     .desc = "Data translation lookaside buffer misses" },
};
