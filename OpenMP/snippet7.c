#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

int fib (int n)
{
   int x, y;
   if (n < 2) return n;
   #pragma omp task shared(x)
   x = fib(n-1);
   #pragma omp task shared(y)
   y = fib(n-2);
   #pragma omp taskwait
   return x + y;
}

int main(int argc, char *argv[]) {
   printf("fib returns: %d \n",fib(20));
   return 0;
}

