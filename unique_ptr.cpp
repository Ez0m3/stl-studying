#include <iostream>
#include <memory>

int main() {
    // 创建裸指针
    int* rawPtr = new int(42);
    std::cout << "裸指针地址: " << rawPtr 
              << ", 值: " << *rawPtr << std::endl;
    std::cout << "&rawPtr (指针本身的地址): " << &rawPtr << std::endl;
    
    std::unique_ptr<int> smartPtr(rawPtr);

    std::cout << "智能指针管理的值: " << *smartPtr << std::endl;
    int a=100;
    rawPtr=&a;
    *rawPtr = 100;
    std::cout << "修改后智能指针的值: " << *smartPtr << std::endl; 
    std::cout << "修改后指针的值: " << *rawPtr << std::endl; 

    return 0;
}