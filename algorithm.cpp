#include<iostream>
#include<queue>
class MyStack {
private:
    std::queue<int> q;
public:
    MyStack() {
        
    }
    
    void push(int x) {
        q.push(x);
        int size=q.size();
        while(--size){
            int temp=q.front();
            q.pop();
            q.push(temp);
        }
    }
    
    int pop() {
        int p=q.front();
        q.pop();
        return p;
    }
    
    int top() {
        return q.front();
    }
    
    bool empty() {
        return q.empty();
    }
};
int main(){

}