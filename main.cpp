#include <iostream>
#include <string>
using std::string;
void reverse(string& s)
{
    for(size_t i=0;i<s.size()/2;i++)
    {
        char temp=s[i];
        s[i]=s[s.size()-i-1];
        s[s.size()-i-1]=temp;
    }
}
string myadd(const string& s1,const string& s2)
{
    int size1=s1.size();
    int size2=s2.size();
    int maxsize=size1>size2?size1:size2;
    string sum;
    int ret=0;
    for(int i=0;i<=maxsize;i++)
    {
        if(i<size1)
        {
            ret+=s1[size1-i-1]-'0';
        }
        if(i<size2)
        {
            ret+=s2[size2-i-1]-'0';
        }
        if(i<maxsize||ret>0)
        {
            sum.push_back(ret%10+'0');
        }
        ret/=10;
    }
    reverse(sum);
    for(auto c:sum)
    {
        std::cout<<c;
    }
    std::cout<<"\n";
    return sum;
}
string mysub(const string& s1,const string& s2)
{

}
void menu()
{
    string s1,s2;
    std::cout<<"请输入高精度整数"<<"\n";
    std::cin>>s1;

    std::cout<<"请输入高精度整数"<<"\n";
    std::cin>>s2;
    string sum=myadd(s1,s2);
    //string sub=mysub(s1,s2);
}
int main()
{
    menu();
}