/**
 * 内存对齐极简指南 - 10分钟搞懂
 * 核心知识点：对齐是什么 + 为什么重要 + 怎么写代码
 */

 //**对齐 = 数据地址必须是类型大小的整数倍**
#include <iostream>
#include <cstdint>

// ============ 1. 对齐是什么？ ============
struct BadStruct {    // 实际大小：24字节！
    char a;           // 1字节，偏移0
    double b;         // 8字节，偏移8（跳了7字节！）
    char c;           // 1字节，偏移16
    int d;            // 4字节，偏移20
};

struct GoodStruct {   // 实际大小：16字节 ✓
    double b;         // 8字节，偏移0（最大的放前面）
    int d;            // 4字节，偏移8
    char a;           // 1字节，偏移12
    char c;           // 1字节，偏移13
    // 自动填充到8的倍数
};

// ============ 2. 为什么重要？ ============
// x86：不对齐 → 慢3倍
// ARM（ESP32）：不对齐 → 直接崩溃！

// ============ 3. Union的危险 ============
union Dangerous {
    char c;      // 1字节
    int i;       // 4字节
    double d;    // 8字节（最严格）
};

// 问题：如果union地址不是8的倍数，访问d会崩溃！

// ============ 4. 通信协议必须打包 ============
#pragma pack(push, 1)   // 取消对齐，保证跨平台
struct SerialPacket {   // 固定13字节
    uint8_t header;     // 1
    uint16_t length;    // 2
    uint8_t data[8];    // 8
    uint16_t crc;       // 2
};
#pragma pack(pop)

// ============ 5. 实用技巧 ============
// ESP32传感器数据结构
struct SensorData {     // 24字节，完美对齐
    double timestamp;   // 8字节（最严格）
    float temperature;  // 4字节
    float humidity;     // 4字节
    uint16_t id;        // 2字节
    uint8_t status;     // 1字节
    // 自动填充到8的倍数
};

// 检查对齐
static_assert(sizeof(SensorData) == 24, "大小必须24字节");
static_assert(alignof(SensorData) == 8, "必须8字节对齐");

// ============ 6. 演示代码 ============
int main() {
    std::cout << "=== 内存对齐极简指南 ===\n\n";
    
    // 1. 展示内存浪费
    std::cout << "BadStruct大小: " << sizeof(BadStruct) << "字节\n";
    std::cout << "GoodStruct大小: " << sizeof(GoodStruct) << "字节\n";
    std::cout << "节省: " << sizeof(BadStruct) - sizeof(GoodStruct) 
              << "字节（" << (1.0 - double(sizeof(GoodStruct))/sizeof(BadStruct))*100 
              << "%）\n\n";
    
    // 2. Union警告
    std::cout << "⚠️ Union警告:\n";
    std::cout << "Dangerous大小: " << sizeof(Dangerous) << "字节\n";
    std::cout << "Dangerous对齐: " << alignof(Dangerous) << "字节\n";
    std::cout << "问题：如果Dangerous放在不对齐地址，访问double会崩溃！\n\n";
    
    // 3. 通信协议
    std::cout << "✅ 通信协议最佳实践:\n";
    std::cout << "SerialPacket大小: " << sizeof(SerialPacket) << "字节（固定）\n";
    std::cout << "跨平台传输时必须用 #pragma pack(1)\n\n";
    
    // 4. ESP32实战
    std::cout << "🎯 ESP32开发实战:\n";
    SensorData sensor;
    std::cout << "SensorData地址: " << &sensor << "\n";
    std::cout << "地址能被8整除吗？" 
              << (reinterpret_cast<uintptr_t>(&sensor) % 8 == 0 ? "是 ✓" : "否 ✗") 
              << "\n";
    std::cout << "大小: " << sizeof(sensor) << "字节\n";
    
    return 0;
}