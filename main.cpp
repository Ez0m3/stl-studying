#include <iostream>
#include <thread>
#include <mutex>
std::mutex mtx;
std::size_t NUM=1000000;
void add(int* p){
    for(std::size_t i=0;i<NUM;++i){
        mtx.lock();
        ++(*p);
        mtx.unlock();
    }
}

int main(){
    int x=0;
    int *p=&x;
    std::thread t1(add,p);
    std::thread t2(add,p);
    std::cout<<x<<"\n";
    if(t1.joinable())t1.join();
    if(t2.joinable())t2.join();
    std::cout<<x<<"\n";
}