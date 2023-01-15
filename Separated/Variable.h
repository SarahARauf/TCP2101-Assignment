#ifndef VARIABLE_H
#define VARIABLE_H


class DeclObject;
template <typename T>
class operations;
template <typename T>
class Datastruct;
template <typename T>
class Stack;
class Program;


#include <iostream>
#include <map>
#include <sstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include "DeclObject.h"
#include "operations.h"
#include "Datastruct.h"
#include "Stack.h"
#include "Program.h"
using namespace std;


template <typename T> // Template, so that a variable can accept any datatype
class Variable : public DeclObject
{
    public:
    // string name;
    T value; // Store value of the variable

    // Some overloading, to distinguish between value assignment or variable assignment
    void setValue(const Variable<T> &val);
    void setValue(T val);

    T getValue();
};

#endif
