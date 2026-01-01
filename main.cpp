#include<iostream>
#include<memory>
using std::unique_ptr;
// template<typename T>
// class deque{
// private:
//     struct node{
//         T data;
//         unique_ptr<node> pnext;
//         node(T value=T(),unique_ptr<node> ptr)
//             :data(value),pnext(ptr){}
//     };
// };
template<typename T>
struct node{
        T data;
        unique_ptr<node> pnext;
        node(T value=T(),unique_ptr<node> ptr=nullptr)
            :data(value),pnext(ptr){}
    };
int main(){
    node<int> node1(3);
    node<int> node2(4);
    node1=std::move(node2);
    std::cout<<node2.data<<"\n";
}