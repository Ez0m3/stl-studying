#include <iostream>
#include <memory>
using std::unique_ptr;
class person{
public:
    person(){
        std::cout<<"构造"<<std::endl;
    }
    ~person(){
        std::cout<<"析构"<<std::endl;
    }
};
unique_ptr<person> makeperson(){
    return unique_ptr<person>(new person());
}
int main(){
    unique_ptr<person> ptr1=makeperson();
    unique_ptr<person> ptr2=std::move(ptr1);
}