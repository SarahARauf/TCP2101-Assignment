#ifndef PROGRAM_H
#define PROGRAM_H


// #include "DeclObject.h"
// #include "Datastruct.h"
class DeclObject;
template <typename T>
class Variable;
template <typename T>
class operations;
template <typename T>
class Datastruct;
template <typename T>
class Stack;
template <typename T>
class Queue;



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
#include "Stack.h"
#include "Queue.h"
using namespace std;




class Program
{
    vector<string> commands; // our DSL command
    map<string, DeclObject *> runningProgram;
    // map --> {key:value, key:value, .....} collection of keys and values
    // keys are unique, dsName are unique

public:
    Program();

    int countWords(string &str);

    void deallocProgram();

    void parseCommands();

};


#endif