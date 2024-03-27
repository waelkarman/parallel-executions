#include <pthread.h>
#include <stdio.h>
#include "timer.hpp"

/*
* Overload a single core.
* test NUMA arch & asymmetric Cores design
* Code for Linux
* Use htop to check core affinity
* Ref: https://linux.die.net/man/3/cpu_zero
*/

unsigned long long fibonacci_recursive(int n) {
    if (n <= 1) return n;
    return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
}

void* threadFunction(void* arg) {
    Timer t;
    unsigned long long  res = fibonacci_recursive(46);
    return (void*)res;
}

int main() {
    pthread_t thread0;
    pthread_t thread1;
    cpu_set_t cpuset;
    int cpunum = 0;

    // TEST CORE 0
    printf("Set CPU %d\n",cpunum);

    pthread_create(&thread0, NULL, &threadFunction, NULL);

    CPU_ZERO(&cpuset);
    CPU_SET(cpunum, &cpuset);

    int result0 = pthread_setaffinity_np(thread0, sizeof(cpu_set_t), &cpuset);
    if (result0 != 0) {
        perror("Error");
    }

    pthread_join(thread0, NULL);


    // TEST CORE 18
    cpunum = 18;
    printf("Set CPU %d\n",cpunum);

    pthread_create(&thread1, NULL, &threadFunction, NULL);

    CPU_ZERO(&cpuset);
    CPU_SET(cpunum, &cpuset);

    int result1 = pthread_setaffinity_np(thread1, sizeof(cpu_set_t), &cpuset);
    if (result1 != 0) {
        perror("Error");
    }

    pthread_join(thread1, NULL);


    return 0;
}
