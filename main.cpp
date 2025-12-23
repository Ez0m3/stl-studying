#include <iostream>
#include <string>
#include<limits>
using std::string;
void reverse(string& s)
{
    size_t size=s.size();
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
string myadd(const string& a,const string& b)
{
    int i=a.size()-1;
    int j=b.size()-1;
    string sum;
    int carry=0;
    while(i>=0||j>=0||carry>0)
    {
        if(i>=0)
        {
            carry+=a[i--]-'0';
        }
        if(j>=0)
        {
            carry+=b[j--]-'0';
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
    while(diff.back()=='0'&&diff.size()>1)diff.pop_back();
    if(!compare(a,b))
    {

        diff.push_back('-');
    }
    reverse(diff);
    return diff;
}
string mymul(const string& a,const string& b)
{
    if(a=="0"||b=="0")return "0";
    string mul;
    int n=a.size()-1;
    int m=b.size()-1;
    int* temp=new int[n+m+2]();
    for(int i=n;i>=0;i--)
    {
        for(int j=m;j>=0;j--)
        {
            int carry=(a[i]-'0')*(b[j]-'0');
            int sum=carry+temp[i+j+1];
            temp[i+j+1]=sum%10;
            temp[i+j]+=sum/10;
        }
    }
    for(int i=0;i<=n+m+1;i++)
    {
        mul.push_back(temp[n+m+1-i]+'0');
    }
    while(mul.back()=='0'&&mul.size()>1)mul.pop_back();
    delete[] temp;
    reverse(mul);
    return mul;
}
string mydiv(const string& a,const string& b)
{return a;}
void print()
{
    std::cout<<"输入：1.加法2.减法3.乘法4.除法0.退出"<<"\n";
}
void menu()
{
    string s1,s2;
    std::cout<<"请输入高精度整数"<<"\n";
    std::cin>>s1;
    std::cout<<"请输入高精度整数"<<"\n";
    std::cin>>s2;
    print();
    while(true)
    {
        int op;
        if(!(std::cin>>op))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout<<"非法输入，请输入0~4"<<'\n';
            continue;
        }
        if(op<0||op>4)
        {
            std::cout<<"非法输入，请输入0~4"<<'\n';
            continue;
        }
        if(op==0)
        {
            std::cout<<"退出运算"<<"\n";
        }
        if(op==1)
        {
            string ret=myadd(s1,s2);
            for(auto c:ret)std::cout<<c;
        }
        if(op==2)
        {
            string ret=mysub(s1,s2);
            for(auto c:ret)std::cout<<c;
        }
        if(op==3)
        {
            string ret=mymul(s1,s2);
            for(auto c:ret)std::cout<<c;
        }
        if(op==4)
        {
            string ret=mydiv(s1,s2);
            for(auto c:ret)std::cout<<c;
        }
        return;
    }
}
int main()
{
    menu();
}