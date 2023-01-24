#ifndef SLLCURSOR_H
#define SLLCURSOR_H

class DeclObject;
template <typename T>
class Variable;
template <typename T>
class operations;
template <typename T>
class Datastruct;
template <typename T>
class SingleLinkedList;
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
#include "Sll.h"
#include "Program.h"
using namespace std;



template <class T>
class SLListCursor : public DeclObject<T>
{
    private:
        SingleLinkedList<T>* list;                      
        typename SingleLinkedList<T>::Node* current;    

    public:

        SLListCursor();

        void pointToStart(SingleLinkedList<T>& sll);

        void moveToNext();

        T getNodeValue();

        bool checkEnd();

};

#endif
