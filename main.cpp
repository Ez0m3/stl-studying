#include<iostream>
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
    bool isempty()const{return size==0;}
    void clear();
    void push_front(const T& value);
    void push_front(T&& value);
    void push_back(const T& value);
    void push_back(T&& value);
    T& pop_front();  //增加返回值？
    void pop_back();    //增加返回值？
    int find_index(const T& value)const;
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
LinkedList<T>::LinkedList(LinkedList&& other)noexcept{
    phead=other.phead;
    ptail=other.ptail;
    size=other.size;
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
    other.clear();
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
T& LinkedList<T>::pop_front(){
    if(phead==nullptr){
        throw std::out_of_range("pop_front on empty list");
    }else{
        Node* ptemp=phead->next;
        T temp=std::move(phead->data);
        delete phead;
        phead=ptemp;
        if(phead==nullptr)ptail=nullptr;
        --size;
        T& value=temp;
        return value;
    }
}

template<typename T>
void LinkedList<T>::print()const{
    for(Node* ptemp=phead;ptemp!=nullptr;ptemp=ptemp->next){
        std::cout<<ptemp->data<<" ";
    }
    std::cout<<"\n";
}

int main(){
    LinkedList<int> list;
    list.push_front(10);
    list.push_front(20);
    list.push_front(30);
    list.print();
    auto& x=list.pop_front();
    list.pop_front();
    std::cout<<x;
}