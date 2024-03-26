#include <pthread.h>
#include <stdio.h>

/*
* Overload a single core.
* Code for Linux
*
*/

unsigned long long fibonacci_recursive(int n) {
    if (n <= 1) return n;
    return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
}

void* threadFunction(void* arg) {
    unsigned long long  res = fibonacci_recursive(46);
    printf("Executed.\n");
    return (void*)res;
}

int main() {
    pthread_t thread;
    cpu_set_t cpuset;

    pthread_create(&thread, NULL, &threadFunction, NULL);

    CPU_ZERO(&cpuset);
    CPU_SET(1, &cpuset);
    printf("Num core that will serve the task: %d\n",CPU_COUNT(&cpuset));

    int result = pthread_setaffinity_np(thread, sizeof(cpu_set_t), &cpuset);
    if (result != 0) {
        perror("Error");
    }

    pthread_join(thread, NULL);

    return 0;
}
