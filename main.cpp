#include <iostream>
#include <string>
#include <utility>
template<typename T>
void inner(T&& t)
{
    std::cout<<"调用了右值"<<t<<std::endl;
}
template<typename T>
void inner(T& t)
{
    std::cout<<"调用了左值"<<t<<std::endl;
}
template<typename T>
void outer(T&& t)
{
    inner(std::forward<T>(t));
}
class person
{

};
int main()
{
    outer(3);
    int a=3;
    outer(a);
    int* b=&a;
    outer(b);
    outer(std::move(b));
}