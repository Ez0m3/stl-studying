#include<iostream>
void test()
{
    try
    {
        throw std::runtime_error("我肚子饿了");
    }
    catch(const std::exception& e)
    {
        std::cout<<e.what();
    }   
}
int main()
{
    test();
    return 0;
}