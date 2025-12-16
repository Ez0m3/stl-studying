#include<iostream>
#include<vector>
void test();
int main()
{
    test();
    return 0;
}
void test()
{
    std::vector<int> v;
    v.push_back(3);
    v.push_back(6);
    v.push_back(9);
    for(std::vector<int>::iterator it=v.begin();it<v.end();it++)
    {
        std::cout<<*it;
    }
    std::system("pause");
}