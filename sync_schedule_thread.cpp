#include <pthread.h>
#include <stdio.h>
#include <iostream>
#include <thread>
#include "timer.hpp"

/*
* Overload a single core.
* test NUMA arch & asymmetric Cores design
* Code for Linux
* Use htop to check core affinity
* Ref: https://www.gnu.org/software/libc/manual/html_node/CPU-Affinity.html
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

void threadlauncher(int cpunum){
    pthread_t thread;
    cpu_set_t cpuset;
    printf("Set CPU %d\n",cpunum);

    pthread_create(&thread, NULL, &threadFunction, NULL);

    CPU_ZERO(&cpuset);
    CPU_SET(cpunum, &cpuset);

    int result0 = pthread_setaffinity_np(thread, sizeof(cpu_set_t), &cpuset);
    if (result0 != 0) {
        perror("Error");
    }

    pthread_join(thread, NULL);
}


int main() {
    unsigned int n = std::thread::hardware_concurrency();
    std::cout << "Available Cores: " << n << std::endl;

    for(int i; i<n; i++){
        threadlauncher(i);
    }

    return 0;
}
