#include <stdio.h>
#include <omp.h>
#define NUM_THREADS 2
/**
 * This code demonstrate the problem of the FAKE SHARING
 * Example of approximation of Pi with parallel programming
 * gcc -fopenmp snippet1.c
 * 
 * The program uses the number of threads and their ids to split the work and an array as container to join the results afterward. 
 * No sharing data just divide the loop cycle in several slice
*/

static long num_steps = 9000000;
double step;

int main()
{
    int i, nthreads;
    double pi, sum[NUM_THREADS];
    step = 1.0/(double)num_steps;
    
    double start_time = omp_get_wtime();
    omp_set_num_threads(NUM_THREADS);
    #pragma omp parallel
    {
        int i, id, nthrds;
        double x;
        id = omp_get_thread_num();
        nthrds = omp_get_num_threads();
        if(id==0) nthreads=nthrds;
        for(i=id, sum[id]==0.0;i<num_steps;i=i+nthrds){
            x = (i+0.5)*step;
            sum[id]+=4.0/(1.0+x*x);
        }
    }
    
    for(i=0, pi=0.0;i<nthreads;i++){
        pi+=sum[i]*step;
    }
    
    double end_time = omp_get_wtime();
    printf("Time: %f\nValue:%f\n",end_time - start_time,pi);
}
