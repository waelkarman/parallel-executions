#include <functional>
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <condition_variable>
#include "ts_vector.hpp"
#include <random>

using namespace std;

/**
 * Thread pool draft
 * threads creation overhead still not managed
 *
*/

std::mutex mtx;
std::condition_variable cv;
bool ready = false;


unsigned long long fibonacci_recursive(int n) {
    if (n <= 1) return n;
    return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
}

void th_lodable(int i, vector<std::function<void(int)>> & tasks){
    std::function<void(int)> f;
    {
        std::lock_guard<std::mutex> lock(queue_mutex);
        if (tasks.empty()){
            return;
        }
        f = tasks.back();
        tasks.pop_back();
    }
    f(i);
}

int main() {
    unsigned int n = std::thread::hardware_concurrency();
    std::cout << "Total available Cores: " << n << endl;

    vector<thread> workers;
    vector<std::function<void(int)>> tasks;


    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(40, 46);

    for(int q=0; q<100; q++){
        int fib = distrib(gen);
        std::function<void(int)> task = [=](int i){
            cout << "execute task " << q << " on thread " << i << endl;
            fibonacci_recursive(fib);
        };

        tasks.push_back(std::move(task));
    }

    int i = 0;
    while(tasks.size()>0){
        while(tasks.size()>0 && i<n){
            workers.push_back(thread(th_lodable,i,std::ref(tasks)));
            i++;
        }

        
        for(thread& w : workers){
            if(w.joinable()){
                w.join();
                i--;
            }
        }
    }

    return 0;
}
