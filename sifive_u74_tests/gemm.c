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

#include <stdlib.h>
#include <stdio.h>

#include "gemm.h"

// #define NI 650
// #define NJ 700
// #define NK 750

static void init_array(int ni, int nj, int nk, double *alpha, double *beta,
                       double C[ni][nj], double A[ni][nk], double B[nk][nj])
{
    int i, j;

    *alpha = 1.5;
    *beta = 1.2;
    for (i = 0; i < ni; i++)
        for (j = 0; j < nj; j++)
            C[i][j] = (double)((i * j + 1) % ni) / ni;
    for (i = 0; i < ni; i++)
        for (j = 0; j < nk; j++)
            A[i][j] = (double)(i * (j + 1) % nk) / nk;
    for (i = 0; i < nk; i++)
        for (j = 0; j < nj; j++)
            B[i][j] = (double)(i * (j + 2) % nj) / nj;
}

static void kernel_gemm_priv(int ni, int nj, int nk, double alpha, double beta,
                        double C[ni][nj], double A[ni][nk], double B[nk][nj])
{
    int i, j, k;

    for (i = 0; i < ni; i++)
    {
        for (j = 0; j < nj; j++)
            C[i][j] *= beta;
        for (k = 0; k < nk; k++)
        {
            for (j = 0; j < nj; j++)
                C[i][j] += alpha * A[i][k] * B[k][j];
        }
    }
}

static void *polybench_alloc(unsigned long long int n, int size)
{
    void *ret = NULL;
    size_t alloc_size = n;
    alloc_size *= size;

    int err = posix_memalign(&ret, 4096, alloc_size);
    if (!ret || err)
    {
        fprintf(stderr, "[PolyBench] posix_memalign: cannot allocate memory");
        exit(1);
    }

    return ret;
}

void kernel_gemm(int ni, int nj, int nk)
{
    /* Retrieve problem size. */
    // int ni = NI;
    // int nj = NJ;
    // int nk = NK;

    /* Variable declaration/allocation. */
    double alpha;
    double beta;
    double *C;
    double *A;
    double *B;

    C = (double(*)[ni][nj])polybench_alloc(ni * nj, sizeof(double));
    A = (double(*)[ni][nk])polybench_alloc(ni * nk, sizeof(double));
    B = (double(*)[nk][nj])polybench_alloc(nk * nj, sizeof(double));

    init_array(ni, nj, nk, &alpha, &beta, C, A, B);

    kernel_gemm_priv(ni, nj, nk, alpha, beta, C, A, B);
}
