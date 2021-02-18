#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

volatile double pi = 0.0;
pthread_mutex_t piLock;
long double intervals = 100000;
int numThreads = 1;

clock_t start, end;
double cpu_time_used;

void *calculate_pi(void *id)

int main()
{
    start = clock();

    pthread_t *threads;
    void *retval;
    int *thread_id;
    int i;

    threads = malloc(numThreads*sizeof(pthread_t));
    thread_id = malloc(numThreads*sizeof(int));
    pthread_mutex_init(&piLock, NULL);

    for ( i = 0; i < numThreads; i++)
    {
        thread_id[i] = i;
        pthread_create(&threads[i], NULL, calculate_pi, thread_id+i);
    }

    for ( i = 0; i < numThreads; i++)
    {
        pthread_join(threads[i], &retval);
    }

    printf("pi = %f", pi);

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Execution time = %f", cpu_time_used);


    return 0;

}

void *calculate_pi(void *id)
{
    long double x, step, local_sum = 0;
    
    int i, thread_id = *((int *)id);
    
    step = 1.0 / intervals;

    for ( i = thread_id; i < intervals; i+= numThreads)
    {
        x = (i+0.5) * step;
        local_sum += 4.0 / (1.0 + x*x);
    }

    local_sum *= step;
    pthread_mutex_lock(&piLock);
    pi += local_sum;
    pthread_mutex_unlock(&piLock);

    return NULL;
    
}