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


// ========== 高精度加法优化指南 ==========
// 
// 优化点总结：
// 1. 内存预分配：sum.reserve(max(s1.size(), s2.size()) + 1);
// 2. 使用标准库reverse：reverse(s.begin(), s.end());
// 3. 避免复杂分支：分别处理两个字符串，不用else if
// 4. 变量命名清晰：用carry代替next表示进位
// 5. 使用size_t避免符号警告
// 6. 考虑不修改输入参数：传值代替传引用
// 7. 提前计算max_len减少重复计算
// 
// 优化版本示例：
// #include <algorithm>  // 需要包含这个头文件

// string myadd_optimized(string s1, string s2) {
//     // 使用标准库reverse
//     reverse(s1.begin(), s1.end());
//     reverse(s2.begin(), s2.end());
    
//     // 预分配内存（重要！）
//     string sum;
//     size_t max_len = max(s1.size(), s2.size());
//     sum.reserve(max_len + 1);  // +1为可能的进位
    
//     // 清晰变量名，避免复杂分支
//     int carry = 0;
//     for(size_t i = 0; i < max_len; i++) {
//         int digit_sum = carry;  // 每次重置
        
//         // 分别处理，不用else if
//         if(i < s1.size()) digit_sum += s1[i] - '0';
//         if(i < s2.size()) digit_sum += s2[i] - '0';
        
//         sum.push_back((digit_sum % 10) + '0');
//         carry = digit_sum / 10;
//     }
    
//     // 处理最后进位
//     if(carry > 0) {
//         sum.push_back(carry + '0');
//     }
    
//     reverse(sum.begin(), sum.end());
//     return sum;  // 不修改输入，直接返回结果
// }
// 
// 小数据（<100位）时差异不大，大数据时优化明显
// =========================================