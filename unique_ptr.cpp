template<typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        std::unique_ptr<Node> next;  
        Node* prev;              
        Node(T value) : data(std::move(value)), next(nullptr), prev(nullptr) {}
    };
    std::unique_ptr<Node> head;  
    Node* tail = nullptr;       
};
int main(){

}