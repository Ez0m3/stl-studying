#include<iostream>
#include<memory>
using std::size_t;
template<typename T>
class queue{
private:
    std::unique_ptr<T[]> arr;
    size_t front;    //前面出队，指向第一个元素，空为0
    size_t rear;     //后面入队,指向最后一个元素的下一位，空为0
    size_t capacity;
    void resize(){
        size_t newcap=capacity>=100?capacity*3/2:capacity*2;   //扩容策略：小于100时*2，大于100*时1.5
        std::unique_ptr<T[]> newarr(newcap);

    }
public:
    queue(std::size_t cap=100)
        :arr(std::make_unique<T[]>(cap)),front(0),rear(0),capacity(cap){}
    void clear(){
        front=rear=0;
    }
    size_t getnum()const{
        return (rear-front+capacity)%capacity;
    }
    T getfront()const{
        if(isempty())throw std::out_of_range("empty queue");
        return arr[front];
    }
    T getrear()const{
        if(isempty())throw std::out_of_range("empty queue");
        size_t prev=(rear-1+capacity)%capacity;
        return arr[prev];
    }
    bool isempty()const{
        return front==rear;
    }
    bool pop(){
        if(isempty()){
            std::cout<<"queue empty\n";
            return false;
        }
        front=(front+1)%capacity;
        if(front==rear)front=rear=0;
        return true;
    }
    void push(const T& value){
        arr[rear]=value;
        rear=(rear+1)%capacity;
        if(front==rear)resize();
    }
    void push(T&& value){
        arr[rear]=std::move(value);
        rear=(rear+1)%capacity;
        if(front==rear)resize();
    }
};
int main(){

}