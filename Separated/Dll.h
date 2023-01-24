#ifndef DLL_H
#define DLL_H

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


template <class T>
class DoubleLinkedList : public Datastruct<T>
{
    private:
        struct DNode 
        {
            T value;                
            DNode *next;            
            DNode *prev;         
        };

        DNode *head;     
        DNode *tail;    
        int listSize;   

        void *getNew(T newValue);

    public:
        template <typename U> friend class DLListCursor;
        
        DoubleLinkedList();

        ~DoubleLinkedList();

        int getSize(); 

        void addToHead(T newValue);
    
        void addToTail(T newValue);

        void insertAfterNode(int nodeValue, T newValue);

        void removeFromHead();

        void removeFromTail();

        void deleteDS();

        void printDS();

        // void print_back();
        
        bool searchDS(T value);

        void cloneDS();

        void sortDS();

        // DoubleLinkedList<T> cloneDS();

};

#endif
