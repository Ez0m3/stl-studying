#include <iostream>
#include <string>
#include<utility>
class person
{
    private:
    int x=1;
    int y=2;
    public:
    person():x(3)
    {
        x=4;
        y=5;
    }
    void showinfo()
    {
        std::cout<<x<<"  "<<y<<"\n";
    }
};
int main()
{
    person().showinfo();
}