#include<iostream>
#include<memory>
#include<string>
using std::string;
class man{
public:
    string m_name;
    man(string name="xxx")
        :m_name(name){
        std::cout<<m_name<<"我构造了"<<"\n";
    }
    ~man(){
        std::cout<<m_name<<"析构了"<<"\n";
    }
};
int main(){
    std::unique_ptr<man> ptr1=std::make_unique<man>("hwx");
    std::cout<<ptr1->m_name;
}