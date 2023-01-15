
class DeclObject;
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
#include "Program.h"
using namespace std;

// make sure you add in your .cpp file below
//g++ -o main main.cpp DeclObject.cpp Variable.cpp operations.cpp Datastruct.cpp Stack.cpp Queue.cpp Program.cpp
//.\main.exe
int main()
{
    Program p;
    // p.print();
    p.parseCommands();
    p.deallocProgram();
    cout << "Program ended" << endl;
}
