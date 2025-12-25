#include<iostream>
template<typename T>
class sequencelist
{
    private:
    int size;
    int capacity;
    T* ptr;
    public:
    sequencelist();                                   //无参，默认构造  
    sequencelist(int n);                              //有参构造
    ~sequencelist();                                  //析构函数
    sequencelist(const sequencelist& s);              //拷贝构造
    sequencelist(sequencelist&& s)noexcept;           //移动构造
    sequencelist& operator=(const sequencelist& s);   //拷贝=重载
    sequencelist& operator=(sequencelist&& s)noexcept;//移动=重载

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
    for(int i=0;i<size;i++)
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
int main()
{
    sequencelist<int> list1(10);
    sequencelist<int> list2(list1);  // 拷贝构造
    sequencelist<int> list3(std::move(list1));  // 移动构造
    sequencelist<int> list4(5);
    list4 = list2;  // 拷贝赋值
    list4 = std::move(list3);  // 移动赋值
}