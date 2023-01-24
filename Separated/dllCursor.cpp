#include "DllCursor.h"
template class DLListCursor<int>;
template class DLListCursor<float>;
template class DLListCursor<double>;


// Constructor
template <class T>
DLListCursor<T>::DLListCursor()
{
    list = nullptr;
    current = nullptr;
};

// points the current pointer to the head of the dLL list
template <class T>
void DLListCursor<T>::pointToStart(DoubleLinkedList<T>& dll)
{
    list = &dll;
    if(dll.head == nullptr) {
        // cout << "List is empty" << endl;
        return;
    }
    current = list->head;
};

// points the current pointer to the tail of the dLL list
template <class T>
void DLListCursor<T>::pointToEnd(DoubleLinkedList<T>& dll)
{
    list = &dll;
    if(dll.tail == nullptr) {
        // cout << "List is empty" << endl;
        return;
    }
    current = list->tail;
};

// moves the pointer to the next node
template <class T>
void DLListCursor<T>::moveToNext()
{
    if(current == nullptr)
    {
        // cout << "No current node" << endl;
        return;
    }

    if(current->next == nullptr)
    {
        // cout << "End of list has been reached!" << endl;
        return;
    }

    current = current->next;
};

// moves the pointer to the previous node
template <class T>
void DLListCursor<T>::moveToPrev()
{
    if(current == nullptr)
    {
        // cout << "No current node" << endl;
        return;
    }

    if(current->prev == nullptr)
    {
        // cout << "End of list has been reached!" << endl;
        return;
    }

    current = current->prev;
};

// returns the value stored in the node the current pointer is pointing to
template <class T>
T DLListCursor<T>::getNodeValue()
{
    return current->value;
};

// checks whether the pointer has reached the end
template <class T>
bool DLListCursor<T>::checkEnd()
{
    if(current->next == nullptr){return true;}
    return false;
};

// checks whether the pointer has reached the start
template <class T>
bool DLListCursor<T>::checkStart()
{
    if(current->prev == nullptr){return true;}
    return false;
};
