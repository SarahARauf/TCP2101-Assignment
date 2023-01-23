#ifndef STACK_H
#define STACK_H


class DeclObject;
template <typename T>
class Variable;
template <typename T>
class operations;
template <typename T>
class Datastruct;
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
#include "Datastruct.h"
#include "Program.h"
using namespace std;


template <typename T>
class Stack : public Datastruct<T>
{
    public:

    vector<T> data;
    int SIZE;

    Stack() { SIZE = 3; }

    Stack(const Stack<T> &copyFrom); // copy constructor

    ~Stack(){ cout << "deleted a stack" << endl;};

    bool isFull();

    bool isEmpty();

    void push(T V);

    void pop();

    T Top();

    void printDS();

    bool searchDS(T value);

    void sortDS(string choice);
};

#endif
