#include<iostream>
#include<stack>
class MyQueue {
private:
    std::stack<int> via;
    std::stack<int> stk;
public:
    MyQueue() {
    
    }
    
    void push(int x) {
        stk.push(x);
        while(!stk.empty()){
            int temp=stk.top();
            stk.pop();
            via.push(temp);
        }
        via.swap(stk);
    }
    
    int pop() {
        int value=stk.top();
        stk.pop();
        return value;
    }
    
    int peek() {
        return stk.top();
    }
    
    bool empty() {
        return stk.empty();
    }
};
int main(){

}