#include <iostream>
#include <string>
//
int main()
{
    int a=5;
    auto func=[a](int b=10)mutable
    {
        a++;
        std::cout<<a*b<<"\n";
    };
    func();
    func();
}