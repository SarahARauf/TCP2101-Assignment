#include "Queue.h"


template class Queue<double>;
template class Queue<float>;
template class Queue<int>;

// template <typename T>
// Queue<T>::Queue(const Queue<T> &copyFrom) // copy constructor
// {
//     this->data = copyFrom.data;
// }


template <typename T>
Queue<T>::Queue(const Queue<T> &copyFrom) : Datastruct<T>(copyFrom), data(copyFrom.data), SIZE(copyFrom.SIZE)
{
    // any other properties specific to Stack
}

template <typename T>
void Queue<T>::push(T V) { 

    if (isFull())
    {
        pop();
    }
    
    data.push_back(V); 
    

} // add an elemnt to the back of queue

template <typename T>
void Queue<T>::pop() 
{ 
    if (isEmpty()) // If the queue is empty:
    {
        cout << "Empty" << endl;
        return;
    }
    data.erase(data.begin()); 
    
} // remove elementn at the front 

template <typename T>
T Queue<T>::Front() { return data.front(); } // return the elemnt at front of the queue

template <typename T>
T Queue<T>::Back() { return data.back(); } // return elements at the back of the queue

template <typename T>
bool Queue<T>::isEmpty() { return data.empty(); } // return true if queue is empty and otherwise

template <typename T>
bool Queue<T>::isFull() { return data.size() == SIZE;; } // return true if queue is empty and otherwise

template <typename T>
void Queue<T>::printDS()
{
    if (isEmpty()) // If the stack is empty:
    {
        cout << "Empty" << endl;
        return;
    }
    this->print(data);
}

template <typename T>
bool Queue<T>::searchDS( T value)
{
    return this->search(data, value);
}