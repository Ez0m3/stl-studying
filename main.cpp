#include<iostream>
#include <utility>
#include<stdexcept>
#include <cassert> 
template<typename T>
class LinkedList{
private:
    struct Node{
        T data;
        Node* next;
        Node():data(T()),next(nullptr){}
        Node(const T& value,Node* nxt=nullptr):data(value),next(nxt){}
        Node(T&& value,Node* nxt=nullptr):data(std::move(value)),next(nxt){}
    };
    Node* phead;
    Node* ptail;
    size_t size;
public:
    LinkedList():phead(nullptr),ptail(nullptr),size(0){};
    ~LinkedList();
    LinkedList(const LinkedList& other);
    LinkedList& operator=(const LinkedList& other);
    LinkedList(LinkedList&& other)noexcept;
    LinkedList& operator=(LinkedList&& other)noexcept;
    size_t get_size()const{return size;}
    bool isempty()const{return phead==nullptr;}
    void clear();
    T& front(){
        if(isempty())throw std::out_of_range("front() on empty list");
        return phead->data;
    }
    const T& front()const{
        if(isempty())throw std::out_of_range("front() on empty list");
        return phead->data;
    }
    T& back(){
        if(isempty())throw std::out_of_range("back() on empty list");
        return ptail->data;
    }
    const T& back()const{
        if(isempty())throw std::out_of_range("back() on empty list");
        return ptail->data;
    }
    void push_front(const T& value);
    void push_front(T&& value);
    void push_back(const T& value);
    void push_back(T&& value);
    T pop_front();  
    T pop_back();    
    size_t find_index(const T& value)const;
    void print()const;
    void reverse();
};
template<typename T>
LinkedList<T>::~LinkedList(){
    clear();
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList& other)
    :phead(nullptr),ptail(nullptr),size(0){
    Node* ptemp=other.phead;
    while(ptemp!=nullptr){
        Node* pnewNode=new Node(ptemp->data);
        if(size==0){
            phead=ptail=pnewNode;
        }else{
            ptail=ptail->next=pnewNode;
        }
        ptemp=ptemp->next;
        ++size;
    }   
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& other){
    if(this==&other)return *this;
    clear();
    Node* ptemp=other.phead;
    while(ptemp!=nullptr){
        Node* pnewNode=new Node(ptemp->data);
        if(size==0){
            phead=ptail=pnewNode;
        }else{
            ptail=ptail->next=pnewNode;
        }
        ptemp=ptemp->next;
        ++size;
    }
    return *this;
}

template<typename T>
LinkedList<T>::LinkedList(LinkedList&& other)noexcept
    :phead(other.phead),ptail(other.ptail),size(other.size){
    other.phead=nullptr;
    other.ptail=nullptr;
    other.size=0;  
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList&& other)noexcept{
    clear();
    phead=other.phead;
    ptail=other.ptail;
    size=other.size;
    other.phead=nullptr;
    other.ptail=nullptr;
    other.size=0;
    return *this;
}

template<typename T>
void LinkedList<T>::clear(){
    while(phead!=nullptr){
        Node* ptemp=phead->next;
        delete phead;
        phead=ptemp;
    }
    ptail=phead=nullptr;
    size=0;
}

template<typename T>
void LinkedList<T>::push_front(const T& value){
    phead=new Node(value,phead);
    if(ptail==nullptr)ptail=phead;
    ++size;
}

template<typename T>
void LinkedList<T>::push_front(T&& value){
    phead=new Node(std::move(value),phead);
    if(ptail==nullptr)ptail=phead;
    ++size;
}

template<typename T>
void LinkedList<T>::push_back(const T& value){
    if(ptail==nullptr){
        phead=ptail=new Node(value);
    }else{
        ptail->next=new Node(value);
        ptail=ptail->next;
    }
    ++size;
}

template<typename T>
void LinkedList<T>::push_back(T&& value){
    if(ptail==nullptr){
        phead=ptail=new Node(std::move(value));
    }else{
        ptail->next=new Node(std::move(value));
        ptail=ptail->next;
    }
    ++size;
}

template<typename T>
T LinkedList<T>::pop_front(){
    if(phead==nullptr){
        throw std::out_of_range("pop_front on empty list");
    }else{
        Node* ptemp=phead->next;
        T value=std::move(phead->data);
        delete phead;
        phead=ptemp;
        if(phead==nullptr)ptail=nullptr;
        --size;
        return value;
    }
}

template<typename T>
T LinkedList<T>::pop_back(){
    if(phead==nullptr){
        throw std::out_of_range("pop_back on empty list");
    }else if(phead==ptail){
        T value=std::move(phead->data);
        delete phead;
        phead=ptail=nullptr;
        --size;
        return value;
    }else{
        Node* ptemp=phead;
        while(ptemp->next!=ptail)ptemp=ptemp->next;
        T value=std::move(ptail->data);
        delete ptail;
        ptail=ptemp;
        ptail->next=nullptr;
        --size;
        return value;
    }
}

template<typename T>
size_t LinkedList<T>::find_index(const T& value)const{
    size_t index=0;
    for(Node* ptemp=phead;ptemp!=nullptr;ptemp=ptemp->next,++index){
        if(ptemp->data==value)return index;
    }
    std::cout<<"未找到值为"<<value<<"的元素,返回88888888作为记号"<<"\n";
    return 88888888;
}

template<typename T>
void LinkedList<T>::print()const{
    for(Node* ptemp=phead;ptemp!=nullptr;ptemp=ptemp->next){
        std::cout<<ptemp->data<<" ";
    }
    std::cout<<"\n";
}

template<typename T>
void LinkedList<T>::reverse(){
    if(phead==ptail)return;
    Node* pprev=nullptr;
    Node* pcurr=phead;
    Node* pnext=pcurr;
    while(pnext!=nullptr){
        pnext=pcurr->next;
        pcurr->next=pprev;
        pprev=pcurr;
        pcurr=pnext;
    }
    pnext=phead;
    phead=ptail;
    ptail=pnext;
}

int main(){
    
}
