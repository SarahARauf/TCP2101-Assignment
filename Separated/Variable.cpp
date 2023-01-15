#include "Variable.h"

template class Variable<int>;
template class Variable<float>;
template class Variable<double>;
template class Variable<bool>;





template <typename T>
void Variable<T>::setValue(const Variable<T> &val) // For assigning a variable to this variable //= <var> <var1>
{
    value = val.value; // the value of val is assigned to this value
}

template <typename T>
void Variable<T>::setValue(T val) // for assigning a value to this variable //= <var> <value>
{
    value = val;
}

template <typename T>
T Variable<T>::getValue()
{
    // cout << "inside the function:" << value << endl;
    return value;
}