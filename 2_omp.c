#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <math.h>
#include <time.h>

static long iterations = 100000;

double start, end;
double cpu_time_used;

int main()
{
    start = omp_get_wtime();

    double x, y, z, pi;
    int i;
    int count = 0;
    int numthreads = 10;

    #pragma omp parallel firstprivate(x, y, z, i) shared(count) num_threads(numthreads)
    {
        srandom((int)time(NULL) ^ omp_get_thread_num());

        for ( i = 0; i < iterations; i++)
        {
            x = (double)random()/RAND_MAX;
            y = (double)random()/RAND_MAX;
            z = sqrt((x*x) + (y*y));

            if (z <= 1)
            {
                ++count;
            }
            
        }
        
    }
    pi = ((double)count/(double)(iterations*numthreads))*4.0;
    printf("Pi = %f\n", pi);

    end =  omp_get_wtime();
    cpu_time_used = (double) (end - start);
    printf("Execution time = %f", cpu_time_used);

    return 0;
}