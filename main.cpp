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
void removeleadingzeros(string& s)
{
    if(s.empty())return;
    size_t pos=0;
    while(pos<s.size()-1&&s[pos]=='0')++pos;
    if(pos>0)s.erase(0,pos);
}
string myadd(const string& a,const string& b)
{
    int i=a.size()-1;
    int j=b.size()-1;
    string sum;
    sum.reserve(a.size()>b.size()?(a.size()+1):(b.size()+1));
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
    diff.reserve(s1.size());
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
    mul.reserve(a.size()+b.size());
    int n=a.size()-1;
    int m=b.size()-1;
    int* temp=new int[a.size()+b.size()]();
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
    int k=0;
    while(k<n+m+1&&temp[k]==0)++k;
    for(;k<=n+m+1;++k)mul.push_back(char(temp[k]+'0'));
    delete[] temp;
    return mul;
}
string mydiv(const string& a,const string& b)
{
    //前提：b非高精度
    string ret;
    ret.reserve(a.size());
    if(b=="0")
    {
        std::cout<<"除数不能为0！"<<"\n";
        return string();
    }
    if(a=="0")return "0";

    long long div{0};
    long long ten{1};
    for(int i=b.size()-1;i>=0;--i)
    {
        div+=ten*(b[i]-'0');
        ten*=10;
    }
    long long temp{0};
    for(size_t i=0;i<a.size();i++)
    {
        temp+=(a[i]-'0');
        ret.push_back((temp/div)+'0');
        temp=10*(temp%div);
    }
    removeleadingzeros(ret);
    return ret;
}
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
    removeleadingzeros(s1);
    removeleadingzeros(s2);
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
            std::cout << ret << '\n';
        }
        if(op==2)
        {
            string ret=mysub(s1,s2);
            std::cout << ret << '\n';
        }
        if(op==3)
        {
            string ret=mymul(s1,s2);
            std::cout << ret << '\n';
        }
        if(op==4)
        {
            string ret=mydiv(s1,s2);
            std::cout << ret << '\n';
        }
        return;
    }
}
int main()
{
    menu();
}