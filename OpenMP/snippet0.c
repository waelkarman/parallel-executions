#include <omp.h>

/**
 * This simple code demonstrate the problem of the race condition
 * gcc -fopenmp snippet0.c
*/

int main()
{
    #pragma omp parallel
    {
        int ID = omp_get_thread_num();
        printf("hello(%d)",ID);
        printf(" world(%d)\n",ID);
    }
    omp_set_num_threads(4);
    #pragma omp parallel
    {
        int ID = omp_get_thread_num();
        printf("Hey(%d)",ID);
        printf(" man(%d)\n",ID);
    }
    printf("all done\n");
    #pragma omp parallel num_threads(5)
    {
        int ID = omp_get_thread_num();
        printf("Hey(%d)",ID);
        printf(" boy(%d)\n",ID);
    }
}