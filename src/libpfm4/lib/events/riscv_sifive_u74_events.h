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

/*
 * SiFive U74 RISC-V Core
 * Based on SiFive U74-MC Core Complex Manual 21G3.02.00
 * Section 4.9.5 Event Selector Encodings
 */

static const riscv_entry_t riscv_sifive_u74_pe[] = {
    // Instruction Commit Events: .code[7:0]=0
    {.name = "EXCEPTION_TAKEN",
     .code = 0x0000100,
     .desc = "Exception taken"},
    {.name = "INTEGER_LOAD_RETIRED",
     .code = 0x0000200,
     .desc = "Integer load instruction retired"},
    {.name = "INTEGER_STORE_RETIRED",
     .code = 0x0000400,
     .desc = "Integer store instruction retired"},
    {.name = "ATOMIC_MEMORY_RETIRED",
     .code = 0x0000800,
     .desc = "Atomic memory operation retired"},
    {.name = "SYSTEM_INSTRUCTION_RETIRED",
     .code = 0x0001000,
     .desc = "System instruction retired"},
    {.name = "INTEGER_ARITHMETIC_RETIRED",
     .code = 0x0002000,
     .desc = "Integer arithmetic instruction retired"},
    {.name = "CONDITIONAL_BRANCH_RETIRED",
     .code = 0x0004000,
     .desc = "Conditional branch retired"},
    {.name = "JAL_INSTRUCTION_RETIRED",
     .code = 0x0008000,
     .desc = "JAL instruction retired"},
    {.name = "JALR_INSTRUCTION_RETIRED",
     .code = 0x0010000,
     .desc = "JALR instruction retired"},
    {.name = "INTEGER_MULTIPLICATION_RETIRED",
     .code = 0x0020000,
     .desc = "Integer multiplication instruction retired"},
    {.name = "INTEGER_DIVISION_RETIRED",
     .code = 0x0040000,
     .desc = "Integer division instruction retired"},
    {.name = "FP_LOAD_RETIRED",
     .code = 0x0080000,
     .desc = "Floating-point load instruction retired"},
    {.name = "FP_STORE_RETIRED",
     .code = 0x0100000,
     .desc = "Floating-point store instruction retired"},
    {.name = "FP_ADDITION_RETIRED",
     .code = 0x0200000,
     .desc = "Floating-point addition retired"},
    {.name = "FP_MULTIPLICATION_RETIRED",
     .code = 0x0400000,
     .desc = "Floating-point multiplication retired"},
    {.name = "FP_FUSEDMADD_RETIRED",
     .code = 0x0800000,
     .desc = "Floating-point fused multiply-add retired"},
    {.name = "FP_DIV_SQRT_RETIRED",
     .code = 0x1000000,
     .desc = "Floating-point division or square-root retired"},
    {.name = "OTHER_FP_RETIRED",
     .code = 0x2000000,
     .desc = "Other floating-point instruction retired"},
    // Microarchitectural Events: .code[7:0]=1
    {.name = "ADDRESSGEN_INTERLOCK",
     .code = 0x0000101,
     .desc = "Address-generation interlock"},
    {.name = "LONGLAT_INTERLOCK",
     .code = 0x0000201,
     .desc = "Long-latency interlock"},
    {.name = "CSR_READ_INTERLOCK",
     .code = 0x0000401,
     .desc = "CSR read interlock"},
    {.name = "ICACHE_ITIM_BUSY",
     .code = 0x0000801,
     .desc = "Instruction cache/ITIM busy"},
    {.name = "DCACHE_DTIM_BUSY",
     .code = 0x0001001,
     .desc = "Data cache/DTIM busy"},
    {.name = "BRANCH_DIRECTION_MISPREDICTION",
     .code = 0x0002001,
     .desc = "Branch direction misprediction"},
    {.name = "BRANCH_TARGET_MISPREDICTION",
     .code = 0x0004001,
     .desc = "Branch/jump target misprediction"},
    {.name = "PIPE_FLUSH_CSR_WRITE",
     .code = 0x0008001,
     .desc = "Pipeline flush from CSR write"},
    {.name = "PIPE_FLUSH_OTHER_EVENT",
     .code = 0x0010001,
     .desc = "Pipeline flush from other event"},
    {.name = "INTEGER_MULTIPLICATION_INTERLOCK",
     .code = 0x0020001,
     .desc = "Integer multiplication interlock"},
    {.name = "FP_INTERLOCK",
     .code = 0x0040001,
     .desc = "Floating-point interlock"},
    // Memory System Events: .code[7:0]=2
    {.name = "ICACHE_RETIRED",
     .code = 0x0000102,
     .desc = "Instruction cache miss"},
    {.name = "DCACHE_MISS_MMIO_ACCESSES",
     .code = 0x0000202,
     .desc = "Data cache miss or memory-mapped I/O access"},
    {.name = "DCACHE_WRITEBACK",
     .code = 0x0000402,
     .desc = "Data cache write-back"},
    {.name = "INST_TLB_MISS",
     .code = 0x0000802,
     .desc = "Instruction TLB miss"},
    {.name = "DATA_TLB_MISS",
     .code = 0x0001002,
     .desc = "Data TLB miss"},
    {.name = "UTLB_MISS",
     .code = 0x0002002,
     .desc = "UTLB miss"},
};
