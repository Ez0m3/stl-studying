#include<iostream>
#include<thread>
void print(int x){
    for(int i=0;i<1000;++i){
        if(x>=0){
            std::cout<<x+i<<std::endl;
        }else{
            std::cout<<x-i<<std::endl;
        }
    }
}
int main(){
    std::thread thread1(print,1);
    std::thread thread2(print,-1);
    thread1.join();
    thread2.join();
    return 0;
}