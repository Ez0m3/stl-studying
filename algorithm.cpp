#include<iostream>
#include<stack>
int josephus_problem(int n,int gap){
    int result=0;
    for(int i=2;i<=n;++i){
        result=(result+gap)%i;
        std::cout<<"参加游戏"<<i<<"人，报数为"<<gap<<"幸存者编号为（从0开始）:"<<result<<"\n";
    }
    return result;
}
bool ismatched(const std::string& s){   //s为经过筛选只有括号信息的字符串
    std::stack<char> stk;
    for(auto c:s){
        if(c=='['||c=='{'||c=='('){
            stk.push(c);
        }else{
            if(stk.empty())return false;
            char top=stk.top();
            stk.pop();
            if((top=='['&&c!=']')||(top=='{'&&c!='}')||(top=='('&&c!=')')){
                return false;
            }
        }
    }
    return stk.empty();
}
void test() {
    // 测试用例
    struct TestCase {
        std::string input;
        bool expected;
    };
    
    TestCase tests[] = {
        {"()", true},
        {"[]", true},
        {"{}", true},
        {"()[]{}", true},
        {"{[()]}", true},
        {"{{}}", true},
        {"", true},           // 空字符串
        {"(", false},
        {")", false},
        {"(]", false},
        {"([)]", false},
        {"}{", false},
        {"((()))", true},
        {"((())", false},     // 左括号多一个
        {"(()))", false},     // 右括号多一个
    };
    
    for (const auto& test : tests) {
        bool result = ismatched(test.input);
        if (result != test.expected) {
            std::cout << "测试失败: \"" << test.input 
                      << "\" 期望: " << test.expected
                      << " 实际: " << result << std::endl;
        } else {
            std::cout << "测试通过: \"" << test.input << "\"" << std::endl;
        }
    }
}
int main(){
    test();
}