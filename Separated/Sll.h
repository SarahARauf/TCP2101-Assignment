#ifndef SLL_H
#define SLL_H

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
class SingleLinkedList : public Datastruct
{
    private:
        struct Node 
        {
            T value;        
            Node *next;     
        };

        Node *head;     
        int listSize;   

        void *getNew(T newValue);

        void *movetoend();

    public:
        template <typename U> friend class SLListCursor;
        
        SingleLinkedList();

        ~SingleLinkedList();

        int getSize(); 

        void addToHead(T newValue);
    
        void addToTail(T newValue);

        void insertAfterNode(int nodeValue, T newValue);

        void removeFromHead();

        void removeFromTail();

        void deleteDS();

        void printDS();
        
        bool searchDS(T value);

        void cloneDS();

        void sortDS();

        // SingleLinkedList<T> cloneDS();

};

#endif