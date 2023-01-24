#include "Sll.h"
template class Sll<int>;
template class Sll<float>;
template class Sll<double>;


// Creates new node and initializes it with the provided newValue 
// then returns a pointer to the new node.
template <class T>
void *SingleLinkedList<T>::getNew(T newValue)
{
    Node *newNode = new Node;     
    newNode->value = newValue;    
    newNode->next = nullptr;      
    return newNode; 
};

// Returns a pointer to the last element of the list.
template <class T>
void *SingleLinkedList<T>::movetoend()
{
    Node *current = head;
    while(current->next != nullptr)
        current = current->next;    
    return current; 

};

// Cosntructor
template <class T>
SingleLinkedList<T>::SingleLinkedList()
{
    head = nullptr;
    listSize = 0;
};

// Destructor
template <class T>
SingleLinkedList<T>::~SingleLinkedList(){deleteDS();}

// Get List Size
template <class T>
int SingleLinkedList<T>::getSize(){return listSize;}

template <class T>
void SingleLinkedList<T>::addToHead(T newValue)
{
    Node *newNode = static_cast<Node*>(getNew(newValue));
    if(head == nullptr){head = newNode;}
    else
    {
        newNode->next = head;
        head = newNode;
    }
    listSize++; 
};

template <class T>
void SingleLinkedList<T>::addToTail(T newValue)
{
    Node *newNode = static_cast<Node*>(getNew(newValue));

    if (head == nullptr) { head = newNode;} 
    else {
        Node *ptr = static_cast<Node*> (movetoend()); 
        ptr->next = newNode;
        newNode->next = nullptr; 
    }
    listSize++; 
};

template <class T>
void SingleLinkedList<T>::insertAfterNode(int nodeValue, T newValue)
{
    if(nodeValue > listSize || nodeValue < 0){return;}  

    Node *current = head;  

    for (int i = 0; i < nodeValue && current != nullptr; i++) 
    {
        current = current->next;    
    }

    if (current->next == nullptr){addToTail(newValue);}
    else
    {
        Node *newNode = static_cast<Node*>(getNew(newValue));
        newNode->next = current->next;  
        current->next = newNode;       
        listSize++; 
    }
};

template <class T>
void SingleLinkedList<T>::removeFromHead()
{
    if(head == nullptr){return;}

    Node *ptr = head;     // set a pointer to the contents of the head pointer
    head = head->next;    // points head to the next node i.e. second node

    listSize--;
    delete ptr;
    return;
};

template <class T>
void SingleLinkedList<T>::removeFromTail()
{
    if(head == nullptr){return;}

    Node *current = head; 
    Node *previous = nullptr;

    while(current->next)
    {
        previous = current;             
        current = current->next;        
    }
    
    previous->next = nullptr;       
    listSize--;
    delete current;
    return;
};

template <class T>
void SingleLinkedList<T>::deleteDS()
{
    Node *current = head;         
    while(current != nullptr)
    {
        Node *nextNode = current->next;     
        delete current;                     
        current = nextNode;               
    }
    head = nullptr;
    listSize = 0;
};

template <class T>
void SingleLinkedList<T>::printDS() 
{
    Node *current = head; 
    while (current != nullptr)
    {
        cout << current->value << ":";
        current = current->next;
    }
    cout << endl;
};


template <class T>
bool SingleLinkedList<T>::searchDS(T value)
{
    Node* current = head;
    while (current != nullptr) {
        if (current->value == value) {
            return true;
        }
        current = current->next;
    }
    return false;
};

template <class T>
void SingleLinkedList<T>::cloneDS()
{
    cout << "Not implemented" << endl;
};

template <class T>
void SingleLinkedList<T>::sortDS()
{
    cout << "Not implemented" << endl;
};

// Clone/Copy Constructor: clone a data structure 
// SingleLinkedList<T> cloneDS() {
//     SingleLinkedList<T> newList;
//     Node *current = head;
//     while (current != nullptr) {
//         newList.addToTail(current->value);
//         current = current->next;
//     }
//     return newList; // Returns a copy of the current list
// }
