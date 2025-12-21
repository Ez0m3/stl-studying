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
string myadd(string& s1,string& s2)
{
    reverse(s1);
    reverse(s2);
    string sum;
    string& l=(s1.size()>s2.size())?s1:s2;
    string& s=(s1.size()<=s2.size())?s1:s2;
    int temp=0;
    int next=0;
    for(size_t i=0;i<l.size();i++)
    {
        if(i<s.size())
        {
            temp=l[i]+s[i]-'0'-'0'+next;
            next=temp/10;
        }
        else if(i>=s.size()&&i<l.size())
        {
            temp=l[i]-'0'+next;
            next=temp/10;
        }
        sum.push_back(temp%10+'0');
    }
    if(next)
    {
        sum.push_back(next+'0');
    }
    reverse(sum);
        for(const auto& c:sum)
    {
        std::cout<<c;
    }
        std::cout<<"\n";
    for(const auto& c:l)
    {
        std::cout<<c;
    }
    std::cout<<"\n";
    for(const auto& c:s)
    {
        std::cout<<c;
    }
    return sum; 
}
int main()
{
    string s1,s2,s3;
    std::cin>>s1>>s2;
    s3=myadd(s1,s2);
}