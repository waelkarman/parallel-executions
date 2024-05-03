#include <stdio.h>
#include <omp.h>

 /**
  * The integration of 4 / (1 + x^2) from 0 to 1 is π.
  * 
  * run it with gcc -fopenmp snippet4.c; ./a.out
  * 
  * */

static long num_steps = 100000;
double step;
int main ()
{
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

