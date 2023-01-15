#include "operations.h"

template class operations<double>;
template class operations<float>;
template class operations<bool>;
template class operations<int>;





template <typename T>
operations<T>::operations(map<string, DeclObject *> &runningProgram)
{
    this->runningProgram = runningProgram;
}

template <typename T>
void operations<T>::assg_commands(string var, string value) // op = operation, var = variable to assign value to, assg = value or variable to assign from
{
    if (runningProgram.find(value) != runningProgram.end())
    {
        assignVariable(var, value);
    }
    else
    {
        assignValue(var, value);
    }
}

template <typename T>
void operations<T>::print_command(string var)
{
    Variable<T> *vptr = static_cast<Variable<T> *>(runningProgram[var]);
    // string varType = runningProgram[var]->getItemtype();

    // if (varType == "bool")
    // {
    cout << boolalpha << vptr->getValue() << endl;
    // }
    // else
    // {
    //     cout << vptr->getValue() << endl;
    // }
}

template <typename T>
void operations<T>::addition(string var, string value)
{
    if (runningProgram.find(value) != runningProgram.end())
    {
        additionVariable(var, value);
    }
    else
    {
        additionValue(var, value);
    }
}

template <typename T>
void operations<T>::subtraction(string var, string value)
{
    if (runningProgram.find(value) != runningProgram.end())
    {
        subtractionVariable(var, value);
    }
    else
    {
        subtractionValue(var, value);
    }
}

template <typename T>
void operations<T>::multiplication(string var, string value)
{
    if (runningProgram.find(value) != runningProgram.end())
    {
        multiplicationVariable(var, value);
    }
    else
    {
        multiplicationValue(var, value);
    }
}

template <typename T>
void operations<T>::division(string var, string value)
{
    if (runningProgram.find(value) != runningProgram.end())
    {
        divisionVariable(var, value);
    }
    else
    {
        divisionValue(var, value);
    }
}

template <typename T>
void operations<T>::mod(string var, string value)
{
    if (runningProgram.find(value) != runningProgram.end())
    {
        modVariable(var, value);
    }
    else
    {
        modValue(var, value);
    }
}

template <typename T>
void operations<T>::assignValue(string var, string value)
{
    T val;
    istringstream(value) >> boolalpha >> val;
    Variable<T> *vptr = static_cast<Variable<T> *>(runningProgram[var]);
    vptr->setValue(val);
}

template <typename T>
void operations<T>::assignVariable(string var, string value)
{
    Variable<T> *vptr = static_cast<Variable<T> *>(runningProgram[var]);
    Variable<T> *vptr2 = static_cast<Variable<T> *>(runningProgram[value]);
    vptr->setValue(*vptr2);
}

template <typename T>
void operations<T>::additionVariable(string var, string value)
{
    Variable<T> *vptr = static_cast<Variable<T> *>(runningProgram[var]);
    Variable<T> *vptr2 = static_cast<Variable<T> *>(runningProgram[value]);
    T addend1 = vptr->getValue();
    T addend2 = vptr2->getValue();
    T sum1 = addend1 + addend2;
    ostringstream oss;
    oss << sum1;
    string sum2 = oss.str();
    assignValue(var, sum2);
}

template <typename T>
void operations<T>::additionValue(string var, string value)
{
    T addend2;
    istringstream(value) >> addend2;
    Variable<T> *vptr = static_cast<Variable<T> *>(runningProgram[var]);
    T addend1 = vptr->getValue();
    T sum1 = addend1 + addend2;
    ostringstream oss;
    oss << sum1;
    string sum2 = oss.str();
    assignValue(var, sum2);
}

template <typename T>
void operations<T>::subtractionVariable(string var, string value)
{
    Variable<T> *vptr = static_cast<Variable<T> *>(runningProgram[var]);
    Variable<T> *vptr2 = static_cast<Variable<T> *>(runningProgram[value]);
    T minuend = vptr->getValue();
    T subtrahend = vptr2->getValue();
    T difference1 = minuend - subtrahend;
    ostringstream oss;
    oss << difference1;
    string difference2 = oss.str();
    assignValue(var, difference2);
}


template <typename T>
void operations<T>::subtractionValue(string var, string value)
{
    T subtrahend;
    istringstream(value) >> subtrahend;
    Variable<T> *vptr = static_cast<Variable<T> *>(runningProgram[var]);
    T minuend = vptr->getValue();
    T difference1 = minuend - subtrahend;
    ostringstream oss;
    oss << difference1;
    string difference2 = oss.str();
    assignValue(var, difference2);
}

template <typename T>
void operations<T>::multiplicationVariable(string var, string value)
{
    Variable<T> *vptr = static_cast<Variable<T> *>(runningProgram[var]);
    Variable<T> *vptr2 = static_cast<Variable<T> *>(runningProgram[value]);
    T multiplicand = vptr->getValue();
    T multiplier = vptr2->getValue();
    T product1 = multiplicand * multiplier;
    ostringstream oss;
    oss << product1;
    string product2 = oss.str();
    assignValue(var, product2);
}

template <typename T>
void operations<T>::multiplicationValue(string var, string value)
{
    T multiplier;
    istringstream(value) >> multiplier;
    Variable<T> *vptr = static_cast<Variable<T> *>(runningProgram[var]);
    T multiplicand = vptr->getValue();
    T product1 = multiplicand * multiplier;
    ostringstream oss;
    oss << product1;
    string product2 = oss.str();
    assignValue(var, product2);
}

template <typename T>
void operations<T>::divisionVariable(string var, string value)
{
    Variable<T> *vptr = static_cast<Variable<T> *>(runningProgram[var]);
    Variable<T> *vptr2 = static_cast<Variable<T> *>(runningProgram[value]);
    T dividend = vptr->getValue();
    T divisor = vptr2->getValue();
    T quotient1 = dividend / divisor;
    ostringstream oss;
    oss << quotient1;
    string quotient2 = oss.str();
    assignValue(var, quotient2);
}

template <typename T>
void operations<T>::divisionValue(string var, string value)
{
    T divisor;
    istringstream(value) >> divisor;
    Variable<T> *vptr = static_cast<Variable<T> *>(runningProgram[var]);
    T dividend = vptr->getValue();
    T quotient1 = dividend / divisor;
    ostringstream oss;
    oss << quotient1;
    string quotient2 = oss.str();
    assignValue(var, quotient2);
}

template <typename T>
void operations<T>::modVariable(string var, string value)
{
    Variable<T> *vptr = static_cast<Variable<T> *>(runningProgram[var]);
    Variable<T> *vptr2 = static_cast<Variable<T> *>(runningProgram[value]);
    T dividend = vptr->getValue();
    T divisor = vptr2->getValue();
    try{
        T remainder1 = fmod(dividend,divisor);
        ostringstream oss;
        oss << remainder1;
        string remainder2 = oss.str();
        assignValue(var, remainder2);
    }
    catch(...)
    {
        cout << "Dividend and divisor are invalid"<<endl;
    }

}

template <typename T>
void operations<T>::modValue(string var, string value)
{
    T divisor;
    istringstream(value) >> divisor;
    Variable<T> *vptr = static_cast<Variable<T> *>(runningProgram[var]);
    T dividend = vptr->getValue();
    try{
        T remainder1 = fmod(dividend, divisor);
        ostringstream oss;
        oss << remainder1;
        string remainder2 = oss.str();
        assignValue(var, remainder2);
    }
    catch(...)
    {
        cout << "Dividend and divisor are invalid"<<endl;
    }
}