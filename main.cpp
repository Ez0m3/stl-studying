#include<iostream>
#include<string>
void cintest()
{
   std::cout<<"abc1";
   std::cout<<"abc2"<<std::endl;
   std::cout<<"abc3";
}
int main()
{
    cintest();
    std::cout<<std::endl;
    std::cout<<"abc4";
    return 0;
}