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

#include "testcode.h"

   /* Test a simple loop of 1 million instructions             */
   /* Most implementations should count be correct within 1%   */
   /* This loop in in assembly language, as compiler generated */
   /* code varies too much.                                    */

int instructions_million(void) {

#if defined(__i386__) || (defined __x86_64__)
	asm(	"	xor	%%ecx,%%ecx\n"
		"	mov	$499999,%%ecx\n"
		"55:\n"
		"	dec	%%ecx\n"
		"	jnz	55b\n"
		: /* no output registers */
		: /* no inputs */
		: "cc", "%ecx" /* clobbered */
	);
	return 0;
#elif defined(__PPC__)
	asm(	"	nop			# to give us an even million\n"
		"	lis	15,499997@ha	# load high 16-bits of counter\n"
		"	addi	15,15,499997@l	# load low 16-bits of counter\n"
		"55:\n"
		"	addic.  15,15,-1              # decrement counter\n"
		"	bne     0,55b                  # loop until zero\n"
		: /* no output registers */
		: /* no inputs */
		: "cc", "15" /* clobbered */
	);
	return 0;
#elif defined(__ia64__)

	asm(	"	mov	loc6=166666	// below is 6 instr.\n"
		"	;;			// because of that we count 4 too few\n"
		"55:\n"
		"	add	loc6=-1,loc6	// decrement count\n"
		"	;;\n"
		"	cmp.ne	p2,p3=0,loc6\n"
		"(p2)	br.cond.dptk	55b	// if not zero, loop\n"
		: /* no output registers */
		: /* no inputs */
		: "p2", "loc6" /* clobbered */
	);
	return 0;
#elif defined(__sparc__)
	asm(	"	sethi	%%hi(333333), %%l0\n"
		"	or	%%l0,%%lo(333333),%%l0\n"
		"55:\n"
		"	deccc	%%l0		! decrement count\n"
		"	bnz	55b		! repeat until zero\n"
		"	nop			! branch delay slot\n"
		: /* no output registers */
		: /* no inputs */
		: "cc", "l0" /* clobbered */
	);
	return 0;
#elif defined(__arm__)
	asm(	"	ldr	r2,42f		@ set count\n"
		"	b       55f\n"
		"42:	.word 333332\n"
		"55:\n"
		"	add	r2,r2,#-1\n"
		"	cmp	r2,#0\n"
		"	bne	55b		@ repeat till zero\n"
		: /* no output registers */
		: /* no inputs */
		: "cc", "r2" /* clobbered */
	);
	return 0;
#elif defined(__aarch64__)
	asm(	"	ldr	x2,=333332	// set count\n"
		"55:\n"
		"	add	x2,x2,#-1\n"
		"	cmp	x2,#0\n"
		"	bne	55b		// repeat till zero\n"
		: /* no output registers */
		: /* no inputs */
		: "cc", "r2" /* clobbered */
	);
	return 0;

#elif defined(__riscv)
	asm("	li x5,333332 # set count\n"
		"55:\n"
		"	addi x5,x5,-1\n"
		"	bnez x5,55b #repeat till zero\n"
		: /* no output registers */
		: /* no inputs */
		: "cc", "x5" /* clobbered */);

	return 0;
#endif

	return CODE_UNIMPLEMENTED;

}


/* fldcw instructions are counted oddly on Pentium 4 machines */

int instructions_fldcw(void) {

#if defined(__i386__) || (defined __x86_64__)

	int saved_cw,result,cw;
	double three=3.0;

	asm(	"	mov	$100000,%%ecx\n"
		"44:\n"
		"	fldl	%1		# load value onto fp stack\n"
		"	fnstcw	%0		# store control word to mem\n"
		"	movzwl	%0, %%eax	# load cw from mem, zero extending\n"
		"	movb	$12, %%ah	# set cw for \"round to zero\"\n"
		"	movw	%%ax, %3	# store back to memory\n"
		"	fldcw	%3		# save new rounding mode\n"
		"	fistpl	%2		# save stack value as integer to mem\n"
		"	fldcw	%0		# restore old cw\n"
		"	loop	44b		# loop to make the count more obvious\n"
		: /* no output registers */
		: "m"(saved_cw), "m"(three), "m"(result), "m"(cw) /* inputs */
		: "cc", "%ecx","%eax" /* clobbered */
	);
    return 0;
#endif

	return CODE_UNIMPLEMENTED;
}


/* rep instructions are counted a bit non-intuitively */
/* some tools like Valgrind and Pin may count differently than real hardware */

int instructions_rep(void) {

#if defined(__i386__) || defined(__ILP32__)

	char buffer_out[16384];

	asm(	"	mov	$1000,%%edx\n"
		"	cld\n"
		"66:				# test 8-bit store\n"
		"	mov	$0xd, %%al	# set eax to d\n"
		"	mov	$16384, %%ecx\n"
		"	mov	%0, %%edi	# set destination\n"
		"	rep	stosb		# store d 16384 times, auto-increment\n"
		"	dec	%%edx\n"
		"	jnz	66b\n"
		: /* outputs */
		: "rm" (buffer_out) /* inputs */
		: "cc", "%esi","%edi","%edx","%ecx","%eax","memory" /* clobbered */
	);
	return 0;
#elif defined (__x86_64__)

	char buffer_out[16384];

	asm(	"	mov	$1000,%%edx\n"
		"	cld\n"
		"66:				# test 8-bit store\n"
		"	mov	$0xd, %%al	# set eax to d\n"
		"	mov	$16384, %%ecx\n"
		"	mov	%0, %%rdi	# set destination\n"
		"	rep	stosb		# store d 16384 times, auto-increment\n"
		"	dec	%%edx\n"
		"	jnz	66b\n"
		: /* outputs */
		: "rm" (buffer_out) /* inputs */
		: "cc", "%esi","%edi","%edx","%ecx","%eax","memory" /* clobbered */
	);
	return 0;
#endif

	return CODE_UNIMPLEMENTED;

}
