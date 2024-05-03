#include <stdio.h>
#include <omp.h>

 /**
  * The integration of 4 / (1 + x^2) from 0 to 1 is π.
  * 
  * run it with gcc -fopenmp snippet4.1.c; ./a.out
  * 
  * */

static long num_steps = 100000;
double step;
int main ()
{
    omp_sched_t sched_type;
    int g_chunk_size;
    int s_chunk_size = 5;

    omp_set_schedule(omp_sched_auto,s_chunk_size);

    omp_get_schedule(&sched_type, &g_chunk_size);
        switch(sched_type) {
        case omp_sched_static:
            printf("Static, chunk size: %d\n", g_chunk_size);
            break;
        case omp_sched_dynamic:
            printf("Dynamic, chunk size: %d\n", g_chunk_size);
            break;
        case omp_sched_guided:
            printf("Guided, chunk size: %d\n", g_chunk_size);
            break;
        case omp_sched_auto:
            printf("Auto, chunk size: %d\n", g_chunk_size);
            break;
    }

    int i; double pi, sum = 0.0;
    step = 1.0/(double) num_steps;
    #pragma omp parallel
    {
        double x;
        #pragma omp for reduction(+:sum)
        for (i=0; i<num_steps; i++)
        {
            x = (i+0.5)*step; 
            sum = sum + 4.0/(1.0+x*x);
        }
    }

    pi = step * sum;

    printf("Value: %f\n",pi);
}

