#include "SllCursor.h"
template class SLListCursor<int>;
template class SLListCursor<float>;
template class SLListCursor<double>;


// Constructor
template <class T>
SLListCursor<T>::SLListCursor()
{
    list = nullptr;
    current = nullptr;
};

// points the current pointer to the head of the sll list
template <class T>
void SLListCursor<T>::pointToStart(SingleLinkedList<T>& sll)
{
    list = &sll;
    if(sll.head == nullptr) {
        // cout << "List is empty" << endl;
        return;
    }
    current = list->head;
};

// moves the pointer to the next node
template <class T>
void SLListCursor<T>::moveToNext()
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

// returns the value stored in the node the current pointer is pointing to
template <class T>
T SLListCursor<T>::getNodeValue()
{
    return current->value;
};

// checks whether the pointer has reached the end
template <class T>
bool SLListCursor<T>::checkEnd()
{
    if(current->next == nullptr){return true;}
    return false;
};
