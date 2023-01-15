#ifndef OPERATIONS_H
#define OPERATIONS_H


class DeclObject;
template <typename T>
class Variable;
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

#include <cmath>

#include "DeclObject.h"
#include "Variable.h"
#include "Datastruct.h"
#include "Stack.h"
#include "Program.h"
using namespace std;






template <typename T> // Template, so that a variable can accept any datatype
class operations
{
public:
    
    map<string, DeclObject*> runningProgram;

    operations(map<string, DeclObject *> &runningProgram);

    void assg_commands(string var, string value); // op = operation, var = variable to assign value to, assg = value or variable to assign from


    void print_command(string var);

    void addition(string var, string value);

    void subtraction(string var, string value);

    void multiplication(string var, string value);

    void division(string var, string value);

    void mod(string var, string value);

private:
    void assignValue(string var, string value);

    void assignVariable(string var, string value);

    void additionVariable(string var, string value);

    void additionValue(string var, string value);

    void subtractionVariable(string var, string value);

    void subtractionValue(string var, string value);

    void multiplicationVariable(string var, string value);

    void multiplicationValue(string var, string value);

    void divisionVariable(string var, string value);

    void divisionValue(string var, string value);

    void modVariable(string var, string value);

    void modValue(string var, string value);
};

#endif
