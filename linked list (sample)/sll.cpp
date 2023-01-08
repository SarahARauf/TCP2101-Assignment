#include <iostream>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

template<typename T>
class SLinkedList{
private:

    // Declare a structure for the list
    struct Node{
        T value;    // The value stored in this node
        Node *next; // To point to the next node
    };

    Node *head; // List head pointer
    int listSize; // Size of list

    // Creates a new node
    void *getNew(T newValue){ 

        Node *newNode = new Node;     // Allocates memory for the new node
        newNode->value = newValue;    // Initializes the contents of the node
        newNode->next = nullptr;      // Sets the pointer field to nullptr

        return newNode;
    };

    // void *search(T);

    void *movetoend(){
        Node *ptr = head;
        while(ptr->next != nullptr)
        ptr=ptr->next;
        return ptr;
    };

public:

    // Constructor
    SLinkedList(){
        head = nullptr; 
        listSize = 0;
    }

    // Destructor
    ~SLinkedList(){

        // To traverse the list in the while statement
        // Position nodePtr at the head of the list.
        Node *ptr = head; 
        Node *nextNode; // To point to the next node
    
        // While nodePtr is not at the end of the list...
        while (ptr != nullptr)
        {
            // Save a pointer to the next node.
            nextNode = ptr->next;
            
            // Delete the current node.
            delete ptr;

            // Position nodePtr at the next node.
            ptr = nextNode;
        }
    };

    // Operations
    // Note: function names will be changed later on when combining it with the running program.

    // AddE = adds node to the end of the list.
    void push_back(T newValue){ 

        // Creates a new node
        Node *newNode = static_cast<Node*>(getNew(newValue));

        listSize++; // Increases the size of list since new node is created

        // If the head is empty (aka not pointing to anything), head will point to the new node
        if (head == nullptr) { 
            head = newNode;
        } 

        // Else, set the current last node to point to the new node
        // The new node will then point to 'nullptr'
        else {
            Node *ptr = static_cast<Node*> (movetoend()); //
            ptr->next = newNode;
            newNode->next = nullptr; 
        }
    };

    //AddF = adds node to the front of the list.
    void push_front(T newValue){ 

        // Creates a new node
        Node *newNode = static_cast<Node*>(getNew(newValue));
        
        listSize++; // Increases the size of list since new node is created

        // If the head is empty , head will point to the new node
        if(head == nullptr)
        {
            head = newNode;
        }
        // Else, set the head to point to the new node
        else
        {
            newNode->next = head;
            head = newNode;
        }
    };
    

    // DelF = Delete a node from the front
    bool delete_front(){

        if(head == nullptr){
            cout << "linked list is empty !" << endl;
            // return false;
        }

        Node *ptr = head;     // set a pointer to the contents of the head pointer
        head = head->next;    // points head to the next node i.e. second node
        
        cout << "~ first item removed" << endl;

        listSize--;
        delete ptr;
        return true;
    };


    // DelE = Delete a node from the end.
    bool delete_back(){

        if(head == nullptr){
            cout<<"linked list is empty !"<<endl;
            // return false;
        }

        // To traverse the list in the while statement
        Node *cur = head; 
        Node *prev = nullptr;

        while(cur->next)
        {
            prev = cur;             
            cur = cur->next;        // points current node ptr to the next node
        }
        
        prev->next = nullptr;       // points to the previous element (last second element)
                                    // Change next pointer to null

        cout << "~ last item removed" <<endl;
        
        listSize--;
        delete cur;
        return true;
        };


    // AddA = Insert value AFTER a node (so nodeValue cannot be = 0, since nothing comes before the first element)
    void insert(int nodeValue, T newValue){

        if(nodeValue > listSize || nodeValue < 0){
            cout << "Node value out of bound !" << endl;
            // return false;
        }

        // Creates a new node
        Node *newNode = static_cast<Node*>(getNew(newValue));

        listSize++; // Increases the size of list since new node is created

        // To traverse the list in the while statement
        Node *cur = head; // set a pointer to the contents of the head pointer

        int count = 0;

        // Note: have to redo this part.
        while(cur != nullptr && count < nodeValue){
            if(count == (nodeValue-1)){ 
                if(cur->next != nullptr){
                    newNode->next = cur->next; // Make next ptr of new node as next of cur
                }
                cur->next = newNode; // move the next of cur as newNode
                cout<<"~ New node added at the node value " << nodeValue << " !" << endl;
                // return true;
                break;
            }
            count++;
            cur = cur->next;
        }
    };

    // bool insert(nodeValue, T newValue);

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

    int getSize(){return listSize;} 
};

int main(){

    SLinkedList<int> lst;
    
    lst.push_front(10);
    cout << "List Size = " << lst.getSize() << endl;
    lst.print();

    lst.push_back(20);
    cout << "List Size = " << lst.getSize() << endl;
    lst.print();

    lst.push_back(50);
    cout << "List Size = " << lst.getSize() << endl;
    lst.print();
    // lst.delete_front();
    // cout << "List Size = " << lst.getSize() << endl;
    // lst.print();

    lst.insert(1, 30);
    cout << "List Size = " << lst.getSize() << endl;
    lst.print();

    lst.push_back(40);
    cout << "List Size = " << lst.getSize() << endl;
    lst.print();

    lst.push_front(5);
    cout << "List Size = " << lst.getSize() << endl; 
    lst.print();

    lst.delete_back();
    cout << "List Size = " << lst.getSize() << endl; 
    lst.print();

    lst.push_back(50);
    cout << "List Size = " << lst.getSize() << endl;
    lst.print();

    SLinkedList<char> lst2;

    lst2.push_front('a');
    lst2.push_front('b');
    lst2.push_front('c');
    lst2.print();

    return 0;
}
