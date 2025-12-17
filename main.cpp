#include<iostream>
#include<vector>
#include<string>
class person
{
    public:
    person(std::string name,int age):p_name(name),p_age(age)
    {}
    std::string p_name;
    int p_age;
};
void test()
{
    person p1("hwx",24);
    person p2("cjw",23);
    person p3("micu",1);
    std::vector<person> pvector={p1,p2,p3};
    for(const auto& p:pvector)
    {
        std::cout<<p.p_name<<p.p_age<<"\n";
    }
}
int main()
{
    test();
    return 0;
}
