#include <stdio.h>
#include <sys/time.h>

int main(int argc, char **argv)
{
    struct timeval begin, end;
    long seconds, microseconds;
    double elapsed;

    gettimeofday(&begin, 0);

    // TODO: Test Code

    gettimeofday(&end, 0);
    
    seconds = end.tv_sec - begin.tv_sec;
    microseconds = end.tv_usec - begin.tv_usec;
    elapsed = seconds + microseconds * 1e-6;
    printf("%.3f\n", elapsed);
}