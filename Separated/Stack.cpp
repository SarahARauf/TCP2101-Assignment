#include "Stack.h"
template class Stack<int>;
template class Stack<float>;
template class Stack<double>;



// template <typename T>
// Stack<T>::Stack(const Stack<T> &copyFrom) // copy constructor
// {
//     this->data = copyFrom.data;
//     this->
// }
template <typename T>
Stack<T>::Stack(const Stack<T> &copyFrom) : Datastruct<T>(copyFrom), data(copyFrom.data), SIZE(copyFrom.SIZE)
{
    // any other properties specific to Stack
}

template <typename T>
bool Stack<T>::isFull() { return data.size() == SIZE; }

template <typename T>
bool Stack<T>::isEmpty() { return data.empty(); }

template <typename T>
void Stack<T>::push(T V)
{
    if (isFull())
    {
        cout << "Full" << endl;
        return;
    }
    data.push_back(V);
}

template <typename T>
void Stack<T>::pop()
{
    if (isEmpty()) // If the stack is empty:
    {
        cout << "Empty" << endl;
        return;
    }
    data.pop_back();
}

template <typename T>
T Stack<T>::Top()
{
    if (isEmpty()) // If the stack is empty:
    {
        cout << "Empty" << endl;
        return T();
    }
    else
    {
        return data.back();
    }
}

template <typename T>
void Stack<T>::printDS()
{
    if (isEmpty()) // If the stack is empty:
    {
        cout << "Empty" << endl;
        return;
    }
    this->print(data);
    // for (auto x : data)
    // {
    //     cout << x << ":";
    // }
    // cout << endl;
}

template <typename T>
bool Stack<T>::searchDS(T value)
{
    return this->search(data, value);
    // return std::find(data.begin(), data.end(), value) != data.end();
    //  for (auto it = data.begin(); it != data.end(); ++it) {
    //  if (*it == value)
    //      return true;
    //  }
    //  return false;
}

template <typename T>
void Stack<T>::sortDS(string choice)
{
    if (isEmpty()) // If the stack is empty:
    {
        cout << "Empty" << endl;
        return;
    }
    if (choice == "ASC")
    {
        this->bubbleASC(data);
    }
    else
    {
        this->bubbleDESC(data);
    }

}
