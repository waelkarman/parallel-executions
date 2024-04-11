#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>


using namespace std;

/**
 * producer consumer
 *
 *
*/

std::mutex mtx;
std::condition_variable cv;

int counter = 0;


void producer() {
    while(true){
        std::unique_lock<std::mutex> lock(mtx); // Acquisisce il lock sul mutex
        cout << "producer blocca il lock" << endl;
        counter += 1;

        cv.notify_one(); // non sblocca il lock
        lock.unlock(); // !) leggi sopra
        cout << "producer sblocca il lock" << endl;

        std::cout << "Producer ha inserito il dato: " << counter << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}

void consumer() {
    while(true){
        std::unique_lock<std::mutex> lock(mtx);
        cout << "consumer blocca il lock" << endl;
        cv.wait(lock, []{ //wait sblocca il lock
            cout << "consumer sblocca il lock" << endl;
            if(counter>0){
                cout<<"consumer proceed"<<endl;
                return true;
            }else{
                cout<<"consumer stop"<<endl;
                return false;
            }
        }); // Verifica la condizione di consumo

        std::cout << "Consumer ha consumato il dato: " << counter << std::endl;
        counter--;
    }
}

int main() {
    std::thread t1(consumer); // il consumer resta in attesa nei prossimo 8 secondi finche un dato non è dispomnibile
    std::thread t2(producer);
    std::this_thread::sleep_for(std::chrono::seconds(3));
    t1.join();
    t2.join();

    return 0;
}
