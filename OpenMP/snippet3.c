#include <stdio.h>
#include <omp.h>
#define NUM_THREADS 2
/**
 * This code solves the problem of the FAKE SHARING
 * Example of approximation of Pi with parallel programming
 * gcc -fopenmp snippet3.c
 * Each thread uses local variable and just in the end these local variable are summed in a critical section, this way no fake sharing could occur.
 * And the sum is already synchronized.
*/

static long num_steps = 9000000;
double step;

int main()
{
    int nthreads;
    double pi;
    step = 1.0/(double)num_steps;
    
    double start_time = omp_get_wtime();
    omp_set_num_threads(NUM_THREADS);
    #pragma omp parallel
    {
        int i, id, nthrds;
        double x, sum;
        id = omp_get_thread_num();
        nthrds = omp_get_num_threads();
        if(id==0) nthreads=nthrds;
        for(i=id, sum==0.0;i<num_steps;i=i+nthrds){
            x = (i+0.5)*step;
            sum+=4.0/(1.0+x*x);
        }
        #pragma omp critical
        pi+=sum*step;
    }
    
    double end_time = omp_get_wtime();
    printf("Time: %f\nValue:%f\n",end_time - start_time,pi);
}
