#include <iostream>
#include <string>
#include<cmath>
using std::string;
void reverse(string& s)
{
    int size=s.size();
    for(size_t i=0;i<size/2;i++)
    {
        char temp=s[i];
        s[i]=s[size-i-1];
        s[size-i-1]=temp;
    }
}
bool compare(const string& s1,const string& s2)
{
    if(s1.size()!=s2.size())return s1.size()>s2.size();
    if(s1.size()==s2.size())
    {
        for(size_t i=0;i<s1.size();i++)
        {
            if(s1[i]!=s2[i])return s1[i]>s2[i];
        }
    }
    return true;
}
string myadd(const string& s1,const string& s2)
{
    int i=s1.size()-1;
    int j=s2.size()-1;
    string sum;
    int carry=0;
    while(i>=0||j>=0||carry>0)
    {
        if(i>=0)
        {
            carry+=s1[i--]-'0';
        }
        if(j>=0)
        {
            carry+=s2[j--]-'0';
        }
        sum.push_back(carry%10+'0');
        carry/=10;
    }
    reverse(sum);
    return sum;
}
string mysub(const string& a,const string& b)
{
    const string& s1 = compare(a, b) ? a : b; // s1 = max(a,b)
    const string& s2 = compare(a, b) ? b : a; // s2 = min(a,b)
    int i=s1.size()-1;
    int j=s2.size()-1;
    string diff;
    int flag=0;
    while(i>=0||j>=0)
    {
        int borrow=flag;
        if(i>=0)
        {
            borrow+=s1[i--]-'0';
        }
        if(j>=0)
        {
            borrow-=(s2[j--]-'0');
        }
        flag=0;
        if(borrow<0)
        {
            borrow+=10;
            flag=-1;
        }
        diff.push_back(borrow+'0');
    }
    if(!compare(a,b))
    {

        diff.push_back('-');
    }
    reverse(diff);
    return diff;
}
void menu()
{
    string s1,s2;
    std::cout<<"请输入高精度整数"<<"\n";
    std::cin>>s1;
    std::cout<<"请输入高精度整数"<<"\n";
    std::cin>>s2;
    string sub=mysub(s1,s2);
    for(auto c:sub)
    {
        std::cout<<c;
    }
    std::cout<<"\n";
}
int main()
{
    menu();
}