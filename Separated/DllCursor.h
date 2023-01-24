#ifndef DLLCURSOR_H
#define DLLCURSOR_H

class DeclObject;
template <typename T>
class Variable;
template <typename T>
class operations;
template <typename T>
class Datastruct;
template <typename T>
class DoubleLinkedList;
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
#include "Dll.h"
#include "Program.h"
using namespace std;



template <class T>
class DLListCursor : public DeclObject
{
    private:
        DoubleLinkedList<T>* list;                      
        typename DoubleLinkedList<T>::DNode* current;    

    public:

        DLListCursor();

        void pointToStart(DoubleLinkedList<T>& dll);

        void pointToEnd(DoubleLinkedList<T>& dll);

        void moveToNext();

        void moveToPrev();

        T getNodeValue();

        bool checkEnd();

        bool checkStart();
};

#endif
