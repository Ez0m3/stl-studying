#include <iostream>
#include <string>
int main()
{
    int a=5;
    auto func=[a](int b=10)mutable
    {
        a++;
        std::cout<<a*b<<"\n";
    };
    func();
    func(8);
    //std::cout<<func.a;    无法访问！func类的权限为私有，编译时可以索引到成员变量，但是无法在类外访问
}