#include<iostream>
#include<cassert>
class list{
private:
    struct node{
        int data;
        node* node_prev;
        node* node_next;
        node(int value=0,node* prev=nullptr,node* next=nullptr)
            :data(value),node_prev(prev),node_next(next){}
    };
    node* phead;
    node* ptail;
    int size;
    void node_add(int value,node* prev,node* next){
        node* temp=new node(value,prev,next);               //此辅助函数(在俩个目标节点直接新增节点)必须按前后顺序传指针！
        prev->node_next=temp;
        next->node_prev=temp;
    }
    void node_delete(node* curr){
        curr->node_prev->node_next=curr->node_next;         //此辅助函数(删除目标节点)未做安全检查，小心删除哨兵节点！
        curr->node_next->node_prev=curr->node_prev;
        delete curr;
    }
public:
    class iterator{
        node* curr;
    public:
        using difference_type=std::ptrdiff_t;
        using value_type=int;
        using iterator_category=std::bidirectional_iterator_tag;
        using pointer=int*;
        using reference=int&;
        iterator(node* p=nullptr):curr(p){};
        iterator& operator++(){
            curr=curr->node_next;
            return *this;
        }
        iterator operator++(int){
            iterator temp=*this;
            ++(*this);
            return temp;    
        }
        iterator& operator--(){
            curr=curr->node_prev;
            return *this;
        }
        iterator operator--(int){
            iterator temp=*this;
            --(*this);
            return temp;
        }
        reference operator*(){return curr->data;}
        pointer operator->(){return &curr->data;}
        bool operator==(const iterator& other)const{return curr==other.curr;}
        bool operator!=(const iterator& other)const{return curr!=other.curr;}
    };
    list()
        :phead(new node),ptail(new node),size(0){
        phead->node_next=ptail;
        ptail->node_prev=phead;
    }
    ~list(){
        clear();
        delete phead;
        delete ptail;
    }
    list(const list& other)
        :list(){
        for(node* curr=other.phead->node_next;curr!=other.ptail;curr=curr->node_next){
            node_add(curr->data,ptail->node_prev,ptail);
            ++size;
        }
    }
    list& operator=(const list& other){
        if(this==&other)return *this;
        clear();
        for(node* curr=other.phead->node_next;curr!=other.ptail;curr=curr->node_next){
            node_add(curr->data,ptail->node_prev,ptail);
            ++size;
        }
        return *this;       
    }
    iterator begin(){return iterator(phead->node_next);}
    iterator end(){return iterator(ptail);}
    void clear(){
        while(phead->node_next!=ptail)node_delete(phead->node_next);
        size=0;
    }
    void push_front(int value){
        node_add(value,phead,phead->node_next);
        ++size;
    }
    void push_back(int value){
        node_add(value,ptail->node_prev,ptail);
        ++size;
    }
    int popfront(){
        if(phead->node_next==ptail)throw std::out_of_range("list empty");
        int value=phead->node_next->data;
        node_delete(phead->node_next);
        --size;
        return value;
    }
    int popback(){
        if(ptail->node_prev==phead)throw std::out_of_range("list empty");
        int value=ptail->node_prev->data;
        node_delete(ptail->node_prev);
        --size;
        return value;
    }
    int find_index(int value){
        int index=0;
        for(node* curr=phead->node_next;curr!=ptail;curr=curr->node_next,++index){
            if(curr->data==value)return index;
        }
        return -1;
    }
    void modify(int index,int value){
        if(index<0||index>=size)throw std::out_of_range("index out of range");
        for(node* curr=phead->node_next;curr!=ptail;curr=curr->node_next,--index){
            if(index==0){
                curr->data=value;
                return;
            }
        }
    }
    void reverse(){
        if(size<=1)return; //可不加
        for(node* curr=phead;curr!=nullptr;curr=curr->node_prev){
            std::swap(curr->node_prev,curr->node_next);
        }
        std::swap(phead,ptail);
    }
};
// 测试函数
void test_basic_operations() {
    std::cout << "=== 测试基本操作 ===" << std::endl;
    
    // 测试1：构造和析构
    list list1;
    assert(list1.find_index(1) == -1);  // 空链表查找
    
    // 测试2：push_back
    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);
    assert(list1.find_index(1) == 0);
    assert(list1.find_index(2) == 1);
    assert(list1.find_index(3) == 2);
    
    // 测试3：遍历
    std::cout << "正向遍历: ";
    int expected1[] = {1, 2, 3};
    int i = 0;
    for (auto x : list1) {
        std::cout << x << " ";
        assert(x == expected1[i++]);
    }
    std::cout << std::endl;
}

void test_push_pop() {
    std::cout << "\n=== 测试push/pop操作 ===" << std::endl;
    
    list list2;
    
    // 测试push_front
    list2.push_front(3);
    list2.push_front(2);
    list2.push_front(1);
    
    std::cout << "push_front后: ";
    for (auto x : list2) std::cout << x << " ";
    std::cout << std::endl;
    assert(list2.find_index(1) == 0);
    
    // 测试popfront
    int val1 = list2.popfront();
    assert(val1 == 1);
    assert(list2.find_index(1) == -1);
    std::cout << "popfront后(" << val1 << "): ";
    for (auto x : list2) std::cout << x << " ";
    std::cout << std::endl;
    
    // 测试popback
    int val2 = list2.popback();
    assert(val2 == 3);
    std::cout << "popback后(" << val2 << "): ";
    for (auto x : list2) std::cout << x << " ";
    std::cout << std::endl;
    
    // 测试异常
    try {
        list empty_list;
        empty_list.popfront();
        assert(false);  // 不应该执行到这里
    } catch (const std::out_of_range& e) {
        std::cout << "正确抛出异常: " << e.what() << std::endl;
    }
}

void test_modify() {
    std::cout << "\n=== 测试修改操作 ===" << std::endl;
    
    list list3;
    for (int i = 0; i < 5; ++i) {
        list3.push_back(i * 10);
    }
    
    std::cout << "修改前: ";
    for (auto x : list3) std::cout << x << " ";
    std::cout << std::endl;
    
    // 修改元素
    list3.modify(2, 999);
    assert(list3.find_index(999) == 2);
    
    std::cout << "修改索引2为999后: ";
    for (auto x : list3) std::cout << x << " ";
    std::cout << std::endl;
    
    // 测试越界异常
    try {
        list3.modify(10, 100);
        assert(false);
    } catch (const std::out_of_range& e) {
        std::cout << "正确抛出越界异常: " << e.what() << std::endl;
    }
}

void test_copy() {
    std::cout << "\n=== 测试拷贝操作 ===" << std::endl;
    
    list list4;
    list4.push_back(100);
    list4.push_back(200);
    list4.push_back(300);
    
    // 拷贝构造
    list list5(list4);
    std::cout << "原始链表: ";
    for (auto x : list4) std::cout << x << " ";
    std::cout << std::endl;
    
    std::cout << "拷贝的链表: ";
    for (auto x : list5) std::cout << x << " ";
    std::cout << std::endl;
    
    // 验证是深拷贝
    list5.modify(1, 999);
    assert(list4.find_index(999) == -1);  // 原链表不应受影响
    assert(list5.find_index(999) == 1);   // 新链表已修改
    
    // 赋值操作
    list list6;
    list6 = list4;
    std::cout << "赋值后的链表: ";
    for (auto x : list6) std::cout << x << " ";
    std::cout << std::endl;
}

void test_reverse() {
    std::cout << "\n=== 测试反转操作 ===" << std::endl;
    
    list list7;
    for (int i = 1; i <= 5; ++i) {
        list7.push_back(i);
    }
    
    std::cout << "反转前: ";
    for (auto x : list7) std::cout << x << " ";
    std::cout << std::endl;
    
    list7.reverse();
    
    std::cout << "反转后: ";
    for (auto x : list7) std::cout << x << " ";
    std::cout << std::endl;
    
    // 验证反转正确性
    int expected_reverse[] = {5, 4, 3, 2, 1};
    int j = 0;
    for (auto x : list7) {
        assert(x == expected_reverse[j++]);
    }
    
    // 测试空链表反转
    list empty_list;
    empty_list.reverse();  // 应该正常执行，不崩溃
    
    // 测试单元素链表反转
    list single_list;
    single_list.push_back(42);
    single_list.reverse();
    assert(single_list.find_index(42) == 0);
}

void test_clear() {
    std::cout << "\n=== 测试清空操作 ===" << std::endl;
    
    list list8;
    for (int i = 0; i < 10; ++i) {
        list8.push_back(i);
    }
    
    std::cout << "清空前大小: ";
    int count = 0;
    for (auto x : list8) { ++count; std::cout << x << " "; }
    std::cout << " (共" << count << "个元素)" << std::endl;
    
    list8.clear();
    
    std::cout << "清空后: ";
    count = 0;
    for (auto x : list8) { ++count; }
    std::cout << "剩余" << count << "个元素" << std::endl;
    assert(count == 0);
    
    // 清空后应该能继续使用
    list8.push_back(100);
    list8.push_back(200);
    assert(list8.find_index(100) == 0);
    assert(list8.find_index(200) == 1);
}

void test_iterator() {
    std::cout << "\n=== 测试迭代器操作 ===" << std::endl;
    
    list list9;
    for (int i = 0; i < 3; ++i) {
        list9.push_back(i * 10 + 1);
    }
    
    // 测试前置和后置++
    std::cout << "使用迭代器遍历: ";
    for (list::iterator it = list9.begin(); it != list9.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // 测试后置++
    list::iterator it = list9.begin();
    list::iterator it2 = it++;
    assert(*it2 == 1);  // it2指向第一个元素
    assert(*it == 11);  // it指向第二个元素
    
    // 测试--
    it = list9.end();
    --it;
    assert(*it == 21);  // 指向最后一个元素
    
    // 测试箭头操作符
    it = list9.begin();
    ++it;
}

void test_edge_cases() {
    std::cout << "\n=== 测试边界情况 ===" << std::endl;
    
    // 测试空链表的各种操作
    list empty;
    assert(empty.find_index(42) == -1);
    
    try {
        empty.popfront();
    } catch (...) {
        std::cout << "空链表popfront正确抛出异常" << std::endl;
    }
    
    // 测试单元素链表
    list single;
    single.push_back(99);
    assert(single.find_index(99) == 0);
    single.reverse();
    assert(single.find_index(99) == 0);
    int val = single.popfront();
    assert(val == 99);
    assert(single.find_index(99) == -1);
    
    // 测试重复元素
    list duplicates;
    duplicates.push_back(5);
    duplicates.push_back(5);
    duplicates.push_back(5);
    assert(duplicates.find_index(5) == 0);  // 返回第一个匹配的位置
}

int main() {
    try {
        test_basic_operations();
        test_push_pop();
        test_modify();
        test_copy();
        test_reverse();
        test_clear();
        test_iterator();
        test_edge_cases();
        
        std::cout << "\n🎉 所有测试通过！" << std::endl;
        return 0;
    } 
    catch (const std::exception& e) {
        std::cerr << "\n❌ 测试失败: " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "\n❌ 未知错误" << std::endl;
        return 1;
    }
}