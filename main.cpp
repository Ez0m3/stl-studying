#include <iostream>
#include <string>
class person
{
    private:
    std::string name;
    int age;
    public:
    person(std::string n,int a):name(n),age(a)
    {
        std::cout<<"调用了俩构造";
    }
    person(int a):person("int",a)
    {
        std::cout<<"调用了单参数int构造";
    }
    person(std::string n):person(n,20)
    {
        std::cout<<"调用了单参数string构造";
    }
    person():person("wucan",12)
    {
        std::cout<<"调用了无参构造";    
    }
    void showinfo()
    {
        std::cout<<name<<"  "<<age<<"\n";
    }    
};
int main()
{
    person p1;
    p1.showinfo();
    person p2(33);
    p2.showinfo();
    person p3("ccc");
    p3.showinfo();
    person p4("hwx",24);
    p4.showinfo();
}