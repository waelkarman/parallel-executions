#include <functional>
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <random>
#include <atomic>

using namespace std;

/**
 * Thread pool
 *
 * This code snippet suppose to execute a heavy computation on all available core of your linux machine till all task defined in tasks are over.
 * Use htop to check core affinity.
*/

std::mutex queue_mutex;
std::atomic<int> i(0);
std::atomic<int> k(0);


unsigned long long fibonacci_recursive(int n) {
    if (n <= 1) return n;
    return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
}

void th_lodable(vector<std::function<void()>> & tasks){
    int id = i;
    while(true){
        std::function<void()> f;
        {
            std::lock_guard<std::mutex> lock(queue_mutex);
            
            if (tasks.empty()){
                return;
            }
            f = tasks.back();
            tasks.pop_back();
            cout << "Thread " << id << " loaded with task: " << tasks.size() << endl;
        }
        f();
    }
    i--;
}

int main() {
    unsigned int n = std::thread::hardware_concurrency();
    std::cout << "Total available Cores: " << n << endl;

    vector<thread> workers;
    vector<std::function<void()>> tasks;


    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(40, 46);

    for(int q=0; q<100; q++){
        int fib = distrib(gen);
        std::function<void()> task = [=](){
            fibonacci_recursive(fib);
        };

        tasks.push_back(std::move(task));
    }


    while(tasks.size()>0){
        if(i<n){
            workers.push_back(thread(th_lodable,std::ref(tasks)));
            i++;
        }
    }

    for(thread& w : workers){
        if(w.joinable()){
            w.join();
        }
    }

    return 0;
}
