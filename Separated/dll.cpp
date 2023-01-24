#include "Dll.h"
template class DoubleLinkedList<int>;
template class DoubleLinkedList<float>;
template class DoubleLinkedList<double>;


// Creates new node and initializes it with the provided newValue 
// then returns a pointer to the new node.
template <class T>
void *DoubleLinkedList<T>::getNew(T newValue)
{
    DNode *newNode = new DNode;     // Allocates memory for the new node
    newNode->value = newValue;      // Initializes the contents of the node
    newNode->next = nullptr;        // Sets the pointer field to nullptr
    newNode->prev = nullptr;        // Sets the pointer field to nullptr

    return newNode; 
};

// Cosntructor
template <class T>
DoubleLinkedList<T>::DoubleLinkedList()
{
    head = nullptr;
    tail = nullptr;
    listSize = 0;
};

// Destructor
template <class T>
DoubleLinkedList<T>::~DoubleLinkedList(){deleteDS();}

// Get List Size
template <class T>
int DoubleLinkedList<T>::getSize(){return listSize;}

// Add node to the front
template <class T>
void DoubleLinkedList<T>::addToHead(T newValue)
{
    // Creates a new DNode object
    DNode *newNode = static_cast<DNode*>(getNew(newValue));

    if(head == nullptr) // check if its empty
    {   
        head = newNode;
        tail = newNode;
    }
    // Else, set the head to point to the new node
    else
    {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }

    listSize++;
};

// Add node to the end
template <class T>
void DoubleLinkedList<T>::addToTail(T newValue)
{
    // Creates a new DNode object
    DNode *newNode = static_cast<DNode*>(getNew(newValue));
    
    if(head == nullptr) // check if it is empty
    {   
        head = newNode; 
        tail = newNode;
    }
    else
    {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    listSize++;
};

// Insert value after a node
template <class T>
void DoubleLinkedList<T>::insertAfterNode(int nodeValue, T newValue)
{
    // check if nodeValue within range
    if(nodeValue > listSize || nodeValue < 0){return;}

    // set a pointer to the contents of the head pointer
    DNode *current = head;  // Used to traverse the list

    // traverse the list until the desired position is reached
    for (int i = 0; i < nodeValue  && current != nullptr; i++)
    {
        current = current->next;    // move to next node
    }

    if (current == tail)    // check if node value is equal to last element on list
    {
        addToTail(newValue);
    }
    else
    {
        // Creates a new DNode object
        DNode *newNode = static_cast<DNode*>(getNew(newValue));
        newNode->next = current->next;
        current->next = newNode;
        newNode->next->prev = newNode;
        newNode->prev = current;

        listSize++;
    }
};

// Delete a node from the front
template <class T>
void DoubleLinkedList<T>::removeFromHead()
{
    if(tail == nullptr){return;} // check if it is empty
    else
    {
        DNode* current = head;
        head = head->next;
        head->prev = nullptr;
        delete current;
    }
    listSize++;
};

// Delete a node from the end
template <class T>
void DoubleLinkedList<T>::removeFromTail()
{
    if(tail == nullptr){return;} // check if it is empty
    else
    {
        DNode *current = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete current;
    }
    listSize--;
};

// Delete/Destructor: delete the entire list.
template <class T>
void DoubleLinkedList<T>::deleteDS()
{
    while (head != nullptr) {
        DNode* current = head;
        head = head->next;
        delete current;
    }
    head = tail = nullptr;
    listSize = 0;
};


// Print: prints entire list
template <class T>
void DoubleLinkedList<T>::printDS() 
{
    DNode *current = head; 
    while (current != nullptr)
    {
        cout << current->value << ":";
        current=current->next;
    }
    cout << endl;
};


// Print: prints entire list, but backwards
// template <class T>
// void DoubleLinkedList<T>::print_back() 
// {
//     DNode *current = tail;
//     while (current!=nullptr)
//     {
//         cout << current->value << ":";
//         current=current->prev;
//     }
//     cout << endl;
// };


template <class T>
bool DoubleLinkedList<T>::searchDS(T value)
{
    DNode* current = head;
    while (current != nullptr) {
        if (current->value == value) {
            return true;
        }
        current = current->next;
    }
    return false;
};

template <class T>
void DoubleLinkedList<T>::cloneDS()
{
    cout << "Not implemented" << endl;
};

template <class T>
void DoubleLinkedList<T>::sortDS()
{
    cout << "Not implemented" << endl;
};

// // Clone/Copy Constructor: returns a copy of the current list
// DoubleLinkedList<T> cloneDS() 
// {
//     DoubleLinkedList<T> newList;
//     DNode* current = head;  
//     DNode* previous = nullptr;

//     while (current != nullptr) 
//     {
//         newList.addToTail(current->value);
//         previous = newList.tail;
//         current = current->next;

//         if(current != nullptr)
//             newList.tail->prev = previous;
//     }
//     return newList; 
// }
