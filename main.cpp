#include <iostream>
#include <string>
#include<utility>
class person
{
    private:
    std::string name;
    int age;
    public:
    person(std::string n,int a):name(n),age(a)
    {
        std::cout<<"调用了俩构造"<<"\n";
    }
    person(int a):person("int",a)
    {
        std::cout<<"调用了单参数int构造"<<"\n";
    }
    person(std::string n):person(n,20)
    {
        std::cout<<"调用了单参数string构造"<<"\n";
    }
    person():person("wucan",12)
    {
        std::cout<<"调用了无参构造"<<"\n";    
    }
    person(const person& other):name(other.name),age(other.age)
    {
 
        std::cout<<"触发了拷贝构造"<<"\n";
    }
    person(person&& other)noexcept
    :name(std::move(other.name)),age(std::exchange(other.age,0))
    {
        std::cout<<"触发了移动构造"<<"\n";
    }
    person& operator=(person&& other)noexcept
    {
        std::cout<<"触发了移动赋值运算符"<<"\n";
        if(this!=&other)
        {
            name=std::move(other.name);
            age=std::exchange(other.age,0);
        }
        return *this;
    }
    void showinfo()const
    {
        std::cout<<name<<"  "<<age<<"\n";
    }    
};
int main()
{

    person p4{21};
    person p1{std::move(p4)};
    person p2;
    p2=std::move(p1);
    p1.showinfo();
    p4.showinfo();
    p2.showinfo();
}