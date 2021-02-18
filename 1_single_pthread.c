#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

void *calculate_pi();

static long num_steps = 100000;
double step;

clock_t start, end;
double cpu_time_used;

int main()
{
    pthread_t thread1;

    start = clock();

    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_create(&thread1, &attr, calculate_pi, NULL);
    pthread_join(thread1, NULL);

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Execution time = %f\n", cpu_time_used);

    return  0;

}

void *calculate_pi()
{
    step = 1.0/(double) num_steps;

    int i; double x, pi, sum = 0.0;

    for(i=0; i< num_steps;i++){
        x = (i + 0.5)* step;
        sum = sum + 4.0/(1.0+x*x);
    }
    pi = step * sum;

    printf("pi = %f\n", pi);

}