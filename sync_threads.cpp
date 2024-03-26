#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <condition_variable>

using namespace std;
/**
 *
 *
 *
 *
 *
*/

std::mutex mtx;
std::condition_variable cv;
bool ready = false;
void parallel_op(int id){
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, []{
        return ready;
    });
    cout << "Thread " << id << " start!" << endl;
    cout << "Process.. on thread " << id << endl;
}

void startThread() {
    std::lock_guard<std::mutex> lock(mtx);
    ready = true;
    cv.notify_all();
}

int main() {
    vector<thread> th_vector;
    for(int i=0;i<100;i++){
        th_vector.push_back(thread(parallel_op,i));
    }

    for(thread& i : th_vector){
        cout << i.get_id() << endl;
    }

    startThread();

    for(thread& i : th_vector){
        i.join();
    }

    return 0;
}
