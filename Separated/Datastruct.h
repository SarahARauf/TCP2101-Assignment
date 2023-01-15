#ifndef DATASTRUCT_H
#define DATASTRUCT_H



class DeclObject;
template <typename T>
class Variable;
template <typename T>
class operations;
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
#include "Variable.h"
#include "operations.h"
#include "Stack.h"
#include "Program.h"
using namespace std;





template <typename T>
class Datastruct : public DeclObject
{
    public:
    // virtual void function for sort, search, clone
    // virtual void sortDS()=0;
    // virtual void searchDS()=0;
    template <template <typename, typename> class Container>
    bool search(const Container<T, std::allocator<T>> &container, const T &value);
    // virtual void printDS()=0;
    template <template <typename, typename> class Container>
    void print(const Container<T, std::allocator<T>> &container);
    // virtual void deleteDS()=0;
    // virtual void cloneDS()=0;
    Datastruct(const Datastruct<T> &copyFrom);
    Datastruct() {};
    ~Datastruct() {};

};
#endif



