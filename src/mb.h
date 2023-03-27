/*
 * Copyright (c) 2023 INESC-ID, Instituto Superior Técnico, Universidade de Lisboa
 * Changed by Tiago Rocha <tiagolopesrocha@tecnico.ulisboa.pt>
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

#ifndef _MB_H
#define _MB_H

/* These definitions are not yet in distros, so I have cut and pasted just
   the needed definitions in here */

#ifdef __powerpc__
#define rmb() asm volatile ("sync" : : : "memory")

#elif defined (__s390__)
#define rmb() asm volatile("bcr 15,0" ::: "memory")

#elif defined (__sh__)
#if defined(__SH4A__) || defined(__SH5__)
#define rmb()          asm volatile("synco" ::: "memory")
#else
#define rmb()          asm volatile("" ::: "memory")
#endif

#elif defined (__hppa__)
#define rmb()           asm volatile("" ::: "memory")

#elif defined (__sparc__)
#define rmb()           asm volatile("":::"memory")

#elif defined (__alpha__)
#define rmb()           asm volatile("mb" ::: "memory")

#elif defined(__ia64__)
#define rmb()           asm volatile ("mf" ::: "memory")

#elif defined(__arm__)
/*
 * Use the __kuser_memory_barrier helper in the CPU helper page. See
 * arch/arm/kernel/entry-armv.S in the kernel source for details.
 */
#define rmb()           ((void(*)(void))0xffff0fa0)()

#elif defined(__aarch64__)
#define rmb()           asm volatile("dmb ld" ::: "memory")

#elif defined(__mips__)
#define rmb()           asm volatile(                                   \
                                ".set   mips2\n\t"                      \
                                "sync\n\t"                              \
                                ".set   mips0"                          \
				: /* no output */                       \
				: /* no input */                        \
				: "memory")

#elif defined(__i386__)
#define rmb() asm volatile("lock; addl $0,0(%%esp)" ::: "memory")

#elif defined(__NEC__)
#define rmb() asm volatile("lfence":::"memory")

#elif defined(__x86_64)

#if defined(__KNC__)
#define rmb() __sync_synchronize()
#else
#define rmb() asm volatile("lfence":::"memory")
#endif

#elif defined(__riscv)
#define rmb() asm volatile("fence":::"memory")

#else
#error Need to define rmb for this architecture!
#error See the kernel source directory: tools/perf/perf.h file
#endif

#endif
