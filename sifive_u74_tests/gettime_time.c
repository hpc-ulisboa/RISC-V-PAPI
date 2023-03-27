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

#include <stdio.h>
#include <time.h>

void subTimespec(struct timespec t1, struct timespec t2, struct timespec *td)
{
    td->tv_nsec = t2.tv_nsec - t1.tv_nsec;
    td->tv_sec = t2.tv_sec - t1.tv_sec;
    if (td->tv_nsec < 0)
    {
        td->tv_nsec += 1000000000;
        td->tv_sec--;
    }
}

int main(int argc, char **argv)
{
    struct timespec start, finish, delta, dummy_start, dummy_finish;

    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    clock_gettime(CLOCK_MONOTONIC_RAW, &dummy_start);

    clock_gettime(CLOCK_MONOTONIC_RAW, &dummy_finish);
    clock_gettime(CLOCK_MONOTONIC_RAW, &finish);

    subTimespec(start, finish, &delta);
    printf("%d.%.9ld\n", (int)delta.tv_sec, delta.tv_nsec);
}