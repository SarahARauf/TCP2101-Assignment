#ifndef DECLOBJECT_H
#define DECLOBJECT_H


template <typename T>
class Variable;
template <typename T>
class operations;
template <typename T>
class Datastruct;
template <typename T>
class Stack;
class Program;


#include <iostream>
using namespace std;



class DeclObject // A struct to declare the syntax of our DSL command
{
public:
    string cmd;                               // Var
    string dstype;                            // Type of datastructure/or variable
    string itemtype;                          // The datatype of the variable
    string dsName;                            // name given
    string getItemtype(); // Returns datatype
    string getDsName();
    string getDsType();
    DeclObject(const DeclObject &copyFrom) : cmd(copyFrom.cmd), dstype(copyFrom.dstype), itemtype(copyFrom.itemtype), dsName(copyFrom.dsName) {}
    DeclObject() {};
    virtual ~DeclObject() {};
};

#endif
