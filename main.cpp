#include <iostream>

class DoublyLinkedList {
private:
    struct Node {
        int data;
        Node* prev;
        Node* next;
        Node(int value) : data(value), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;

public:
    class ListEmptyException {
    public:
        const char* what() const {
            return "List is empty";
        }
    };

    class OutOfMemoryException {
    public:
        const char* what() const {
            return "Out of memory";
        }
    };

    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void insertFront(int value) {
        Node* newNode = new(std::nothrow) Node(value);
        if (!newNode) {
            throw OutOfMemoryException();
        }
        if (!head) {
            head = tail = newNode;
        }
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void removeFront() {
        if (!head) {
            throw ListEmptyException();
        }
        Node* temp = head;
        head = head->next;
        if (head) {
            head->prev = nullptr;
        }
        else {
            tail = nullptr;
        }
        delete temp;
    }

    void printList() {
        Node* current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

int main() {
    DoublyLinkedList list;

    try {
        list.removeFront(); 
    }
    catch (const DoublyLinkedList::ListEmptyException& ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
    }

    try {
        for (int i = 0; i < 5; ++i) {
            list.insertFront(i);
        }
    }
    catch (const DoublyLinkedList::OutOfMemoryException& ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
    }

    list.printList();

    return 0;
}
