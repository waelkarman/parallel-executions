#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

using namespace std;
/**
 *
 * Synchronisation between threads respects the RAII (Resource Acquisition Is Initialisation) principle.
 *
 * std::lock_guard ensures thread safety, using a single mutex for each operation can become a performance bottleneck with a high number of threads concurrently accessing the resource.
 *
*/

// Thread Safe class
class ts_vector{
    std::mutex mtx;
    vector<int> v;
public:

    void push_back(int n){
        std::lock_guard<std::mutex> guard(mtx);
        v.push_back(n);
        cout << "inserted in vector."<< endl;
    }

    void pop_back(){
        std::lock_guard<std::mutex> guard(mtx);
        if(v.size()>0){
            v.pop_back();
            cout << "popped from vector. " << endl;
        }
    }

    int getSize(){
        std::lock_guard<std::mutex> guard(mtx);
        return v.size();
    }

};


// void incr1000(ts_vector& p,int n){
//     for(int i = 0 ; i < 1000 ; i++){
//         p.push_back(n);
//     }
// }

// void decr1000(ts_vector& p){
//     for(int i = 0 ; i < 1000 ; i++){
//         p.pop_back();
//     }
// }

// int main() {
//     ts_vector v;

//     thread t0(incr1000,std::ref(v),1);
//     thread t1(decr1000,std::ref(v));
//     thread t2(incr1000,std::ref(v),1);
//     thread t3(decr1000,std::ref(v));

//     t0.join();
//     t1.join();
//     t2.join();
//     t3.join();


//     cout << "Controlled access test to a resource." << endl;
//     cout << "Vector size that could but may not necessarily be zero: "<< v.getSize() << endl;

//     return 0;
// }
