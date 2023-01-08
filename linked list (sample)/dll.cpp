#include <iostream>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

template <typename T>
class DLL {
private:
    struct Node 
    { 
        T value;
        Node* next;
        Node* prev;
        Node(T value) : value(value), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    int listSize;

public:
    DLL() : head(nullptr), tail(nullptr), listSize(0) {}

    void push_front(T value) {
        Node* node = new Node(value);
        if (head == nullptr) {
        head = tail = node;
        } else {
        node->next = head;
        head->prev = node;
        head = node;
        }
        listSize++;
    }

    void push_back(T value) {
        Node* node = new Node(value);
        if (tail == nullptr) {
        head = tail = node;
        } else {
        tail->next = node;
        node->prev = tail;
        tail = node;
        }
        listSize++;
    }

    void delete_front() {
        if (head == nullptr) {return;}

        Node* cur = head;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        }
        delete cur;
        listSize--;
    }

    void delete_back() {
        if (tail == nullptr) {return;}
        Node* cur = tail;
        tail = tail->prev;
        if (tail != nullptr) {
        tail->next = nullptr;
        }
        delete cur;
        listSize--;
    }

    // AddA = Insert value AFTER a node (so nodeValue cannot be = 0, since nothing comes before the first element)
    void insert(int nodeValue, T value){

        if(nodeValue > listSize || nodeValue < 0){
            cout << "Node value out of bound !" << endl;
            // return false;
        }

        // Creates a new node
        Node* node = new Node(value);

        listSize++; // Increases the size of list since new node is created

        // To traverse the list in the while statement
        Node *cur = head; // set a pointer to the contents of the head pointer
        int count = 0;

        // Note: have to redo this part.
        while(cur != nullptr && count < nodeValue){
            if(count == (nodeValue-1)){ 
                if(cur->next != nullptr){
                    node->next = cur->next; // Make next ptr of new node as next of cur
                }
                node->prev = cur;
                cur->next = node;
                cout<<"~ New node added at the node value " << nodeValue << " !" << endl;
                // return true;
                break;
            }
            count++;
            cur = cur->next;
        }
    };


    void print() const{
        
        // To move through the list in the while statement.
        Node *ptr = head; // Position ptr at the head of the list.
        
        // While ptr points to a node, traverse the list.
        while (ptr != nullptr)
        {
            cout << ptr->value << ":";
            ptr=ptr->next;
        }
        cout << endl;
    };

    // NOT NEEDED(?)
    void print_back() const
    {
        Node *ptr = tail;
        while (ptr!=nullptr){
        cout << ptr->value << ":";
        ptr=ptr->prev;
        }
        cout << endl;
    }

  int getlistSize() const {
    return listSize;
  }
};

int main(){
    DLL<int> list;
    list.push_front(5);
    list.print();

    list.push_front(10);
    list.print();

    list.push_back(15);
    list.print();
    
    list.print_back();

    list.insert(1, 30);
    list.print();

    cout << "listSize: " << list.getlistSize() << endl;  // Outputs: listSize: 3

    list.delete_front();
    list.print();
    list.delete_back();
    list.print();

    return 0;
}
