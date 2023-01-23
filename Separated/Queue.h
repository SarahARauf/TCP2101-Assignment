#ifndef QUEUE_H
#define QUEUE_H

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
class Queue : public Datastruct<T>
{
public:
    vector<T> data; // declare the queue
    int SIZE;
    Queue() { SIZE = 3; }
    Queue(const Queue<T> &copyFrom);
    ~Queue(){cout << "deleted a queue" << endl;};
    bool isFull();
    bool isEmpty();          // return true if queue is empty and otherwise
    void pop();              // remove elementn at the front
    void push(T V); // add an elemnt to the back of queue
    T Front();               // return the elemnt at front of the queue
    T Back();                // return elements at the back of the queue
    void printDS();
    bool searchDS( T value);    
    void sortDS(string choice);
};

#endif
