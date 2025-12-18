#include<iostream>
#include<string>
void cintest()
{
    char c[100];
    char d[100];
    char e[100];
    std::cin.getline(c,50,'@');
    std::cin.getline(d,3);
    std::cin.getline(e,50);
    std::cout<<c<<std::endl;
    std::cout<<d<<std::endl;
    std::cout<<e<<std::endl;
}      
int main()
{
    cintest();
    std::cout<<std::endl;
    return 0;   
}