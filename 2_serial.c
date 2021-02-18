#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

static long iterations = 100000;

clock_t start, end;
double cpu_time_used;

int main(){
    start = clock();

    int i , count;
    double x, y, z, pi;
    count = 0;

    for ( i = 0; i < iterations; i++)
    {
        x = (double)random() / RAND_MAX;
        y = (double)random() / RAND_MAX;

        z = sqrt((x*x) + (y*y));
        if  (z <= 1) count++;
    }

    pi =((double) count / iterations)*4.0;

    printf("pi = %f", pi);

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Execution time = %f", cpu_time_used);

    return 0;
    
}