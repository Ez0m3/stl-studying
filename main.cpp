#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
void test()
{
    int count = 0;
    auto sf=[count]()mutable
    {
        count++;
        std::cout<<count;
    };
    sf();
} 
int main()
{
    test();
    test();
    test();
    return 0;   
}