#include<iostream>
#include<utility>
#include<memory>
using std::unique_ptr;
using std::size_t;
template<typename T>
class queue{
private:
    std::unique_ptr<T[]> arr;
    size_t front;    //前面出队，指向第一个元素，空为0
    size_t rear;     //后面入队,指向最后一个元素的下一位，空为0
    size_t capacity;
    void resize(){            //push后若人满则触发扩容，扩容策略：小于100时*2，大于100*时1.5
        size_t newcap=capacity>=100?capacity*3/2:capacity*2;   
        auto newarr=std::make_unique<T[]>(newcap);
        size_t curr=front;
        for(size_t i=0;i<capacity;++i){       //数据迁移
            newarr[i]=std::move(arr[curr]);
            curr=(curr+1)%capacity;
        }
        arr=std::move(newarr);            //更新参数
        front=0;
        rear=capacity;
        capacity=newcap;
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
    T& getfront()const{
        if(empty())throw std::out_of_range("empty queue");
        return arr[front];
    }
    T& getrear()const{
        if(empty())throw std::out_of_range("empty queue");
        size_t prev=(rear-1+capacity)%capacity;
        return arr[prev];
    }
    bool empty()const{
        return front==rear;
    }
    bool pop(){
        if(empty()){
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
    void print()const{
        for(size_t i=front;i!=rear;i=(i+1)%capacity){
            std::cout<<arr[i]<<"  ";
        }
    }
};
template<typename T,int MAXSIZE=100>
class stack{
private:
    T arr[MAXSIZE];
    int top;
public:
    stack()
        :top(-1){}
    bool empty()const{return top==-1;}
    template<typename U>
    void push(U&& value){
        if(top>=MAXSIZE-1)throw std::out_of_range("stack flow");
        arr[++top]=std::forward<U>(value);
    }
    T pop(){
        if(top<0)throw std::out_of_range("stack empty");
        return arr[top--];
    }
    const T& get_top()const{
        if(top<0)throw std::out_of_range("stack empty");
        return arr[top];
    }
    T& get_top(){
        if(top<0)throw std::out_of_range("stack empty");
        return arr[top];
    }
};
template<typename T>
class BST{
private:
    struct node{
        T data;
        unique_ptr<node> left;
        unique_ptr<node> right;
        template<typename U>
        explicit node(U&& value):data(std::forward<U>(value)){}
    };
    unique_ptr<node> root;
    size_t node_count;
    const node* find_node(const T& key)const{    //只读版本，返回目标node的const裸指针
        const node* curr=root.get();
        while(curr){
            if(curr->data==key)return curr;
            curr=(key<curr->data)
                ?curr->left.get()
                :curr->right.get();
        }
        return nullptr;
    }
    unique_ptr<node>* find_slot(const T& key){     //修改版本，返回指向node的智能指针的指针
        auto curr=&root;
        while(*curr){
            if((*curr)->data==key)return curr;
            curr=(key<(*curr)->data)
                ?&((*curr)->left)
                :&((*curr)->right);
        }
        return curr;
    }
public:
    BST():root(nullptr),node_count(0){}
    BST(const BST& other)=delete;
    BST& operator=(const BST& other)=delete;
    bool empty()const{
        return root==nullptr;
    }
    size_t size()const{
        return node_count;
    }
    template<typename U>
    bool insert(U&& value){                     
        const T& key=value;
        auto slot=find_slot(key);
        if(*slot)return false;
        *slot=std::make_unique<node>(std::forward<U>(value));
        ++node_count;
        return true;
    }
    bool contains(const T& key)const{
        return find_node(key)!=nullptr;
    }
    bool remove(const T& key){
        auto slot=find_slot(key);
        if(!(*slot))return false;
        if(!(*slot)->left){
            *slot=std::move((*slot)->right);
        }else if(!(*slot)->right){
            *slot=std::move((*slot)->left);
        }else{
            auto curr=&((*slot)->left);
            while((*curr)->right){
                curr=&((*curr)->right);
            }
            (*slot)->data=std::move((*curr)->data);
            *curr=std::move((*curr)->left);
        }
        --node_count;
        return true;
    }
    void clear(){
        root.reset();
        node_count=0;
    }
    void breadth_traversal()const{      //接口函数，迭代算法(queue)
        if(!root)return;
        queue<const node*> q;
        q.push(root.get());
        while(!q.empty()){
            const node* curr=q.getfront();
            q.pop();
            if(curr->left)q.push(curr->left.get());
            if(curr->right)q.push(curr->right.get());
            std::cout<<curr->data<<"\n";
        }
    }
    void depth_traversal()const{        //接口函数，递归算法
        std::cout<<"中序遍历：\n";
        const node* curr=root.get();
        LDR(curr);
    }
    void LDR(const node* curr)const{    //辅助函数，递归算法
        if(!curr)return;
        if(curr->left)LDR(curr->left.get());
        std::cout<<curr->data<<"\n";
        if(curr->right)LDR(curr->right.get());       
    }
    void DLR2()const{                   //接口函数，迭代算法(stack)
        if(!root)return;
        stack<const node*> s;
        const node* curr=root.get();
        s.push(curr);
        while(!s.empty()){
            curr=s.get_top();
            s.pop();
            if(curr->right)s.push(curr->right.get());
            if(curr->left)s.push(curr->left.get());
            std::cout<<curr->data<<"\n";
        }
    }
    void LDR2()const{                   //接口函数，迭代算法(stack)
        if(!root)return;
        stack<const node*> s;
        const node* curr=root.get();
        s.push(curr);
        bool backflag=false;
        while(curr||!s.empty()){
            while(curr){
                s.push(curr);
                curr=curr->left.get();
            }
            curr=s.get_top();
            s.pop();
            std::cout<<curr->data<<"\n";
            curr=curr->right.get();
        }
    }
};
int main(){
    BST<int> bst;
    bst.insert(95);
    bst.insert(15);
    bst.insert(5);
    bst.insert(35);
    bst.insert(75);
    bst.insert(25);
    bst.insert(25);
    bst.insert(35);
    bst.insert(225);
    bst.insert(115);
    bst.insert(155);
    bst.LDR2();  //morris
}