#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> nums = {1, 2, 3, 4, 5};
    
    cout << "VSCode配置测试成功！" << endl;
    cout << "向量内容：";
    
    for (int num : nums) {
        cout << num << " ";
    }
    cout << endl;
    
    // 设置一个断点测试调试功能
    int sum = 0;
    for (int num : nums) {
        sum += num;
    }
    cout << "总和：" << sum << endl;
    
    return 0;
}