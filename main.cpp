#include <iostream>
#include <string>
#include<utility>
class person
{
    public:
    int x;
    int y=5;
    person():x(3)
    {
        std::cout<<"x的地址是"<<&x<<std::endl;
        std::cout<<"y的地址是"<<&y<<std::endl;
        std::cout<<"this的地址是"<<this<<std::endl;
    }
    int* getads()
    {
        return &y;
    }
};
int main()
{
    const int &a=person().x;
    std::cout<<a<<std::endl;
    std::cout<<&a<<std::endl;
    int* b=person().getads();
    *(b-3)=10;
    std::cout<<a<<std::endl;
    std::cout<<*b<<std::endl;
}