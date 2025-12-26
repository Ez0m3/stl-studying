#include<iostream>
template<typename T>
class sequencelist
{
    private:
    int size;
    int capacity;
    T* ptr;
    void grow_to(int mincap);
    public:
    sequencelist();                                   //无参，默认构造  
    sequencelist(int n);                              //有参构造
    ~sequencelist();                                  //析构函数
    sequencelist(const sequencelist& s);              //拷贝构造
    sequencelist(sequencelist&& s)noexcept;           //移动构造
    sequencelist& operator=(const sequencelist& s);   //拷贝=重载
    sequencelist& operator=(sequencelist&& s)noexcept;//移动=重载
    bool isempty()const;
    int getsize()const;
    int getcapacity()const;
    void clear();
    void clearandrelease();
    void shrink_to(int newcapacity);
    void reserve(int n);
    int findindex(const T& t)const;
    void push_back(const T& t);
    void push_back(T&& t);
    void insert(const T& t,int n);
    T& getdata(int n);
    const T& getdata(int index)const;
    T& operator[](int index);
    const T& operator[](int index)const;
};
template<typename T>
sequencelist<T>::sequencelist()
    :size(0),capacity(1),ptr(new T[capacity]){}
template<typename T>
sequencelist<T>::sequencelist(int n)
    :size(0),capacity(n>0?n:1),ptr(new T[capacity]){}
template<typename T>
sequencelist<T>::~sequencelist()
{
    delete[] ptr;
}
template<typename T>
sequencelist<T>::sequencelist(const sequencelist& s)
    :size(s.size),capacity(s.capacity),ptr(new T[s.capacity])
{
    for(int i=0;i<size;++i)
    {
        ptr[i]=s.ptr[i];
    }
}
template<typename T>
sequencelist<T>::sequencelist(sequencelist&& s)noexcept
    :size(s.size),capacity(s.capacity),ptr(s.ptr)
{
    s.ptr=nullptr;
    s.size=0;
    s.capacity=0;
}
template<typename T>
sequencelist<T>& sequencelist<T>::operator=(const sequencelist& s)
{
    if(this==&s)return *this;
    delete[] ptr;
    size=s.size;
    capacity=s.capacity;
    ptr=new T[capacity];
    for(int i=0;i<size;++i)
    {
        ptr[i]=s.ptr[i];
    }
    return *this;
}
template<typename T>
sequencelist<T>& sequencelist<T>::operator=(sequencelist&& s)noexcept
{
    if(this==&s)return *this;
    delete[] ptr;
    size=s.size;
    capacity=s.capacity;
    ptr=s.ptr;
    s.ptr=nullptr;
    s.size=0;
    s.capacity=0;
    return *this;
}
template<typename T>
void sequencelist<T>::grow_to(int mincap)
{
    int newcapacity=mincap>2*capacity?mincap:2*capacity;
    T* newptr=new T[newcapacity];
    for(int i=0;i<size;++i)
    {
        newptr[i]=std::move(ptr[i]);

    }
    delete[] ptr;
    ptr=newptr;
    capacity=newcapacity;
}
template<typename T>
void sequencelist<T>::shrink_to(int newcapacity)
{
    if(newcapacity==0)
    {
        delete[] ptr;
        size=0;
        capacity=0;
        return;
    }
    int newsize=size<newcapacity?size:newcapacity;
    T* newptr=new T[newcapacity];
    for(int i=0;i<newsize;++i)
    {
        newptr[i]=std::move(ptr[i]);
    }
    delete[] ptr;
    ptr=newptr;
    size=newsize;
    capacity=newcapacity;
}
template<typename T>
bool sequencelist<T>::isempty()const
{
    return size==0;
}
template<typename T>
int sequencelist<T>::getsize()const
{
    return size;
}
template<typename T>
int sequencelist<T>::getcapacity()const
{
    return capacity;
}
template<typename T>
void sequencelist<T>::clear()
{
    if(size==0)return;
    size=0;
}
template<typename T>
void sequencelist<T>::clearandrelease()
{
    delete[] ptr;
    ptr=nullptr;
    size=0;
    capacity=0;
}
template<typename T>
void sequencelist<T>::reserve(int mincap)
{
    if(capacity<mincap)grow_to(mincap);
}
template<typename T>
int sequencelist<T>::findindex(const T& t)const
{
    for(int i=0;i<size;++i)
    {
        if(ptr[i]==t)return i;
    }
    return -1;
}
template<typename T>
void sequencelist<T>::push_back(const T& t)
{
    reserve(size+1);
    ptr[size++]=t;
}
template<typename T>
void sequencelist<T>::push_back(T&& t)
{
    reserve(size+1);
    ptr[size++]=std::move(t);
}
template<typename T>
void sequencelist<T>::insert(const T& t,int n)
{
    if(n>size||n<0)
    {
        std::cout<<"不能插入到该位置"<<"\n";
        return;
    }
    reserve(size+1);
    for(int i=size-1;i>=n;--i)
    {
        ptr[i+1]=std::move(ptr[i]);
    }
    ptr[n]=t;
    ++size;
}
template<typename T>
T& sequencelist<T>::getdata(int index)
{
    return ptr[index];
}
template<typename T>
const T& sequencelist<T>::getdata(int n)const
{
    return ptr[n-1];
}
template<typename T>
T& sequencelist<T>::operator[](int index)
{
    return ptr[index];
}
template<typename T>
const T& sequencelist<T>::operator[](int index)const
{
    return ptr[index];
}
int main()
{
    std::cout << "========== 顺序表综合测试 ==========\n\n";
    
    // 测试1：基本构造和容量
    std::cout << "测试1: 构造函数与基础功能\n";
    std::cout << "----------------------------\n";
    sequencelist<int> list1;  // 默认构造
    std::cout << "默认构造: size=" << list1.getsize() 
              << ", capacity=" << list1.getcapacity() 
              << ", empty? " << (list1.isempty() ? "是" : "否") << "\n";
    
    sequencelist<int> list2(10);  // 有参构造
    std::cout << "构造容量10: size=" << list2.getsize() 
              << ", capacity=" << list2.getcapacity() << "\n\n";
    
    // 测试2：push_back 和元素访问
    std::cout << "测试2: push_back 与 operator[]\n";
    std::cout << "----------------------------\n";
    for (int i = 0; i < 8; ++i) {
        list1.push_back(i * 10);  // 左值push_back
    }
    std::cout << "添加8个元素后: size=" << list1.getsize() 
              << ", capacity=" << list1.getcapacity() << "\n";
    
    std::cout << "元素遍历: ";
    for (int i = 0; i < list1.getsize(); ++i) {
        std::cout << list1[i] << " ";  // operator[]
    }
    std::cout << "\n";
    
    // 测试 getdata
    std::cout << "getdata(3): " << list1.getdata(2) << "\n";  // 索引2应该是20
    
    // 测试3：右值push_back
    std::cout << "\n测试3: 右值 push_back\n";
    std::cout << "----------------------------\n";
    list1.push_back(std::move(100));  // 右值
    std::cout << "添加右值100后: size=" << list1.getsize() 
              << ", 最后一个元素=" << list1[list1.getsize()-1] << "\n\n";
    
    // 测试4：insert 功能
    std::cout << "测试4: insert 插入功能\n";
    std::cout << "----------------------------\n";
    list1.insert(999, 3);  // 在索引3插入999
    std::cout << "在索引3插入999后: ";
    for (int i = 0; i < list1.getsize(); ++i) {
        std::cout << list1[i] << " ";
    }
    std::cout << "\n";
    
    // 测试边界插入
    list1.insert(-1, 0);  // 头部插入
    list1.insert(-2, list1.getsize());  // 尾部插入（边界情况）
    std::cout << "边界插入后 size=" << list1.getsize() 
              << ", 头部=" << list1[0] << ", 尾部=" << list1[list1.getsize()-1] << "\n";
    
    // 测试无效插入
    std::cout << "\n测试无效插入 (应显示错误信息):\n";
    list1.insert(999, -5);      // 负索引
    list1.insert(999, 999);     // 超范围索引
    
    // 测试5：findindex 功能
    std::cout << "\n测试5: 查找功能\n";
    std::cout << "----------------------------\n";
    int search_val = 30;
    int index = list1.findindex(search_val);
    std::cout << "查找值 " << search_val << ": ";
    if (index != -1) {
        std::cout << "找到在索引 " << index << " (值=" << list1[index] << ")\n";
    } else {
        std::cout << "未找到\n";
    }
    
    // 测试6：拷贝构造和拷贝赋值
    std::cout << "\n测试6: 拷贝语义\n";
    std::cout << "----------------------------\n";
    sequencelist<int> list_copy1(list1);  // 拷贝构造
    std::cout << "拷贝构造后: size=" << list_copy1.getsize() 
              << ", 前3个元素: " << list_copy1[0] << " " 
              << list_copy1[1] << " " << list_copy1[2] << "\n";
    
    sequencelist<int> list_copy2;
    list_copy2 = list1;  // 拷贝赋值
    std::cout << "拷贝赋值后: size=" << list_copy2.getsize() 
              << ", 验证相等性: " << (list_copy2[3] == list1[3] ? "相等" : "不相等") << "\n\n";
    
    // 测试7：移动语义
    std::cout << "测试7: 移动语义\n";
    std::cout << "----------------------------\n";
    sequencelist<int> list_temp;
    for (int i = 0; i < 5; ++i) {
        list_temp.push_back(i * 100);
    }
    
    std::cout << "移动前 list_temp: size=" << list_temp.getsize() 
              << ", capacity=" << list_temp.getcapacity() << "\n";
    
    sequencelist<int> list_moved(std::move(list_temp));  // 移动构造
    std::cout << "移动构造后 list_moved: size=" << list_moved.getsize() 
              << ", capacity=" << list_moved.getcapacity() << "\n";
    std::cout << "移动构造后 list_temp: size=" << list_temp.getsize() 
              << ", capacity=" << list_temp.getcapacity() 
              << ", empty? " << (list_temp.isempty() ? "是" : "否") << "\n";
    
    // 测试8：容量管理
    std::cout << "\n测试8: 容量管理\n";
    std::cout << "----------------------------\n";
    sequencelist<int> list_cap;
    std::cout << "初始容量: " << list_cap.getcapacity() << "\n";
    
    list_cap.reserve(20);
    std::cout << "reserve(20)后: capacity=" << list_cap.getcapacity() 
              << ", size=" << list_cap.getsize() << "\n";
    
    for (int i = 0; i < 25; ++i) {
        list_cap.push_back(i);
    }
    std::cout << "添加25个元素后: capacity=" << list_cap.getcapacity() 
              << " (应自动扩容)\n";
    
    list_cap.shrink_to(15);
    std::cout << "shrink_to(15)后: capacity=" << list_cap.getcapacity() 
              << ", size=" << list_cap.getsize() << "\n";
    
    list_cap.shrink_to(0);
    std::cout << "shrink_to(0)后: capacity=" << list_cap.getcapacity() 
              << ", empty? " << (list_cap.isempty() ? "是" : "否") << "\n\n";
    
    // 测试9：clear 功能
    std::cout << "测试9: 清空功能\n";
    std::cout << "----------------------------\n";
    sequencelist<int> list_clear;
    for (int i = 0; i < 5; ++i) {
        list_clear.push_back(i * 50);
    }
    std::cout << "清空前: size=" << list_clear.getsize() 
              << ", capacity=" << list_clear.getcapacity() << "\n";
    
    list_clear.clear();
    std::cout << "clear()后: size=" << list_clear.getsize() 
              << ", empty? " << (list_clear.isempty() ? "是" : "否") << "\n";
    
    for (int i = 0; i < 3; ++i) {
        list_clear.push_back(i * 10);
    }
    list_clear.clearandrelease();
    std::cout << "clearandrelease()后: size=" << list_clear.getsize() 
              << ", capacity=" << list_clear.getcapacity() << "\n\n";
    
    // 测试10：自赋值和异常安全
    std::cout << "测试10: 自赋值测试\n";
    std::cout << "----------------------------\n";
    sequencelist<int> list_self;
    list_self.push_back(1);
    list_self.push_back(2);
    list_self.push_back(3);
    
    list_self = list_self;  // 自赋值
    std::cout << "自赋值后 size=" << list_self.getsize() 
              << ", 元素: " << list_self[0] << " " << list_self[1] 
              << " " << list_self[2] << " (应保持原状)\n";
    
    std::cout << "\n========== 所有测试完成 ==========\n";
    
    return 0;

}