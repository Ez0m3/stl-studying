#include<iostream>
#include<memory>
#include<string>
#include<cassert>
using std::unique_ptr;
template<typename T>
class queue{
private:
    struct node{
        T data;
        unique_ptr<node> pnext;
        node(T value=T(),unique_ptr<node> ptr=nullptr)
            :data(value),pnext(std::move(ptr)){}
    };
    unique_ptr<node> phead;
    node* ptail;
    int size;
public:
    queue()
        :phead(std::make_unique<node>()),ptail(phead.get()),size(0){}
    bool isempty()const{return phead->pnext==nullptr;}
    void push(T value){
        ptail->pnext=std::make_unique<node>(value);
        ptail=ptail->pnext.get();
        ++size;
    }
    T pop(){
        if(isempty())throw std::out_of_range("empty queue");
        T temp=std::move(phead->pnext->data);
        phead->pnext=std::move(phead->pnext->pnext);
        --size;
        return temp;
    }
    T getfront()const{
        return phead->pnext->data;
    }
    T getend()const{
        return ptail->data;
    }
};
int main() {
  
}