#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>


using namespace std;

/**
 * This code snippet implements the producer, consumer pattern.
 * As just 2 thread can access to the counter variable in mutual exclusion mode no needs to sinchronize it.
 *
*/

std::mutex mtx;
std::condition_variable cv;
int counter = 0;

void producer() {
    while(true){
        std::unique_lock<std::mutex> lock(mtx);
        cout << "producer get the lock mtx" << endl;
        counter += 1;
        std::cout << "producer has produced data: " << counter << std::endl;

        cv.notify_one();
        lock.unlock(); 
        cout << "producer release the lock mtx" << endl;
        
        std::this_thread::sleep_for(std::chrono::seconds(5)); // move thread to interruptible sleep (S)
    }
}

void consumer() {
    while(true){
        std::unique_lock<std::mutex> lock(mtx);
        cout << "consumer release the lock mtx" << endl;
        cv.wait(lock, []{ //wait release the lock mtx
            cout << "consumer get the lock mtx" << endl;
            if(counter>0){
                cout<<"consumer resume"<<endl;
                return true;
            }else{
                cout<<"consumer stop"<<endl;
                return false;
            }
        });

        counter--;
        std::cout << "consumer has consumed the data: " << counter << std::endl;
    }
}

int main() {
    std::thread t1(consumer);
    std::thread t2(producer);

    
    t1.join();
    t2.join();

    return 0;
}
