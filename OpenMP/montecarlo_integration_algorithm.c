#include <stdio.h>


 /**
  * The integration of 4 / (1 + x^2) from 0 to 1 is π.
  * 
  * */

static long num_steps = 100000;
double step;
int main ()
{
    int i; double x, pi, sum = 0.0;
    step = 1.0/(double) num_steps;
    for (i=0; i<num_steps; i++)
    {
        x = (i+0.5)*step; // Calculation of the value at the center of the interval scaled to the [0,1] range.
        sum = sum + 4.0/(1.0+x*x); // n-th partial sums
    }
    pi = step * sum;

    printf("Value: %f\n",pi);
}

