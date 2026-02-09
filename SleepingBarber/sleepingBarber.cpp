#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <algorithm>
using namespace std;

class BarberShop{
public:
    int cap; //num of chairs or queue size
    queue<int> q; //waiting_customers
    mutex mtx; //Mutex to protect shared state (queue, shop_closed)
    condition_variable cv_customer_waiting; //Condition variable to signal barbers when customers arrive
    bool shop_closed = false; //Flag to indicate shop shutdown

public:
    BarberShop(int capacity){
        this->cap=capacity;
    }

    void barber(int id){
        //Barbers are long-lived worker threads
        //They keep serving customers until the shop is closed
        while(true){
            int curr_cust=-1;
            {
                unique_lock<mutex> lock(mtx);
                cv_customer_waiting.wait(lock, [this](){ //sleeps when no cust waiting
                    return !q.empty() || shop_closed;
                });
                if(shop_closed && q.empty()){
                    cout<<"Barber "<<id<<" is going home"<<endl;
                    return;
                }
                curr_cust=q.front();
                q.pop();
            }
            //cut hair
            cout<<"Barber "<<id<<" is cutting hair for customer "<<curr_cust<<endl;
            this_thread::sleep_for(chrono::seconds(2)); //mimic hair cut or any work done
        }
    }

    void customer(int id){
        {
            lock_guard<mutex> lock(mtx);
            if(shop_closed){
                cout<<"Customer "<<id<<" leaves because shop is closed"<<endl;
                return;
            }
            if(waiting>=cap){
                cout<<"Customer "<<id<<" leaves because no chairs available"<<endl;
                return;
            }
            q.push(id);
        }
        cv_customer_waiting.notify_one(); //notify barber that cust waiting
    }

    void closeShop(){
        {
            lock_guard<mutex> lock(mtx);
            shop_closed=true; //keep lock as other threads should not read outdated value
        }
        cv_customer_waiting.notify_all(); //notify all barber threads to wake up and re-check the condition
    }
};

int main(){
    BarberShop bs(10); //Barber shop with capacity of 10

    //Barber threads
    thread barber_thread1(&BarberShop::barber, &bs, 1);
    thread barber_thread2(&BarberShop::barber, &bs, 2);

    //Customer thread
    vector<thread> threads; 
    for (int i = 0; i < 100; ++i) {
        threads.emplace_back(&BarberShop::customer, &bs, i);
    }
    for(auto& t: threads){
        t.join();
    }
    bs.closeShop();
    barber_thread1.join();
    barber_thread2.join();
    return 0;
}
