#include<iostream>
#include<utility>
#include<memory>
using std::unique_ptr;
using std::size_t;
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
};
int main(){

}