#include<iostream>
class list{
private:
    struct node{
        int data;
        node* node_prev;
        node* node_next;
        node(int value=0,node* prev=nullptr,node* next=nullptr)
            :data(value),node_prev(prev),node_next(next){}
    };
    node* phead;
    node* ptail;
    int size;
    void node_add(int value,node* prev,node* next){
        node* temp=new node(value,prev,next);               //此辅助函数(在俩个目标节点直接新增节点)必须按前后顺序传指针！
        prev->node_next=temp;
        next->node_prev=temp;
    }
    void node_delete(node* curr){
        curr->node_prev->node_next=curr->node_next;         //此辅助函数(删除目标节点)未做安全检查，小心删除哨兵节点！
        curr->node_next->node_prev=curr->node_prev;
        delete curr;
    }
public:
    class iterator{
        node* curr;
    public:
        using difference_type=std::ptrdiff_t;
        using value_type=int;
        using iterator_category=std::bidirectional_iterator_tag;
        using pointer=int*;
        using reference=int&;
        iterator(node* p=nullptr):curr(p){};
        iterator& operator++(){
            curr=curr->node_next;
            return *this;
        }
        iterator operator++(int){
            iterator temp=*this;
            ++(*this);
            return temp;    
        }
        iterator& operator--(){
            curr=curr->node_prev;
            return *this;
        }
        iterator operator--(int){
            iterator temp=*this;
            --(*this);
            return temp;
        }
        reference operator*(){return curr->data;}
        pointer operator->(){return &curr->data;}
        bool operator==(const iterator& other)const{return curr==other.curr;}
        bool operator!=(const iterator& other)const{return curr!=other.curr;}
    };
    list()
        :phead(new node),ptail(new node),size(0){
        phead->node_next=ptail;
        ptail->node_prev=phead;
    }
    ~list(){
        clear();
        delete phead;
        delete ptail;
    }
    list(const list& other)
        :list(){
        for(node* curr=other.phead->node_next;curr!=other.ptail;curr=curr->node_next){
            node_add(curr->data,ptail->node_prev,ptail);
            ++size;
        }
    }
    list& operator=(const list& other){
        if(this==&other)return *this;
        clear();
        for(node* curr=other.phead->node_next;curr!=other.ptail;curr=curr->node_next){
            node_add(curr->data,ptail->node_prev,ptail);
            ++size;
        }
        return *this;       
    }
    iterator begin(){return iterator(phead->node_next);}
    iterator end(){return iterator(ptail);}
    void clear(){
        while(phead->node_next!=ptail)node_delete(phead->node_next);
        size=0;
    }
    void push_front(int value){
        node_add(value,phead,phead->node_next);
        ++size;
    }
    void push_back(int value){
        node_add(value,ptail->node_prev,ptail);
        ++size;
    }
    int popfront(){
        if(phead->node_next==ptail)throw std::out_of_range("list empty");
        int value=phead->node_next->data;
        node_delete(phead->node_next);
        --size;
        return value;
    }
    int popback(){
        if(ptail->node_prev==phead)throw std::out_of_range("list empty");
        int value=ptail->node_prev->data;
        node_delete(ptail->node_prev);
        --size;
        return value;
    }
    int find_index(int value){
        int index=0;
        for(node* curr=phead->node_next;curr!=ptail;curr=curr->node_next,++index){
            if(curr->data==value)return index;
        }
        return -1;
    }
    void modify(int index,int value){
        if(index<0||index>=size)throw std::out_of_range("index out of range");
        for(node* curr=phead->node_next;curr!=ptail;curr=curr->node_next,--index){
            if(index==0){
                curr->data=value;
                return;
            }
        }
    }
    void reverse(){
        if(size<=1)return; //可不加
        for(node* curr=phead;curr!=nullptr;curr=curr->node_prev){
            std::swap(curr->node_prev,curr->node_next);
        }
        std::swap(phead,ptail);
    }
    bool has_circle(){
        node* fast=phead->node_next;
        node* slow=phead->node_next;
        while(fast!=nullptr&&fast->node_next!=nullptr){
            fast=fast->node_next->node_next;
            slow=slow->node_next;
            if(fast==slow)return true;
        }
        return false;
    }
    int get_cycle_entry(){
        node* fast=phead->node_next;
        node* slow=phead->node_next;
        while(fast!=slow){
            fast=fast->node_next->node_next;
            slow=slow->node_next;
        }
        fast=phead->node_next;
        while(fast!=slow){
            fast=fast->node_next;
            slow=slow->node_next;
        }
        return fast->data;
    }
};
int josephus_problem(int n,int gap){
    int result=0;
    for(int i=1;i<n;++i){
        result=(result+gap)%(i+1);
    }
    return result;
}
int main(){
    for(int i=1;i<=10;++i){
        std::cout<<josephus_problem(i,2);
    }
}