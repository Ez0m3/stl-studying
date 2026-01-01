#include<iostream>
template<typename T,int MAXSIZE=100>
class stack{
private:
    T arr[MAXSIZE];
    int top;
public:
    stack()
        :top(-1){}
    void push(const T& value){
        if(top>=MAXSIZE-1)throw std::out_of_range("stack flow");
        arr[++top]=value;
    }
    void push(T&& value){
        if(top>=MAXSIZE-1)throw std::out_of_range("stack flow");
        arr[++top]=std::move(value);
    }
    T pop(){
        if(top<0)throw std::out_of_range("stack empty");
        return arr[top--];
    }
    T get_top()const{return arr[top];}
};
int main(){

}