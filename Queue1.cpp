#include <iostream>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

struct DeclObject // A struct to declare the syntax of our DSL command
{
    string cmd;                               // Var
    string dstype;                            // Type of datastructure/or variable
    string itemtype;                          // The datatype of the variable
    string dsName;                            // name given
    string getItemtype() { return itemtype; } // Returns datatype
    string getDsName() { return dsName; }
    string getDsType() { return dstype; }
};

template <typename T> // Template, so that a variable can accept any datatype
struct Variable : public DeclObject
{
    // string name;
    T value; // Store value of the variable

    // Some overloading, to distinguish between value assignment or variable assignment
    void setValue(const Variable &val) // For assigning a variable to this variable //= <var> <var1>
    {
        value = val.value; // the value of val is assigned to this value
    }

    void setValue(T val) // for assigning a value to this variable //= <var> <value>
    {
        value = val;
    }

    T getValue()
    {
        // cout << "inside the function:" << value << endl;
        return value;
    }
};


// template <typename T> // Template, so that a variable can accept any datatype
struct Datastruct : public DeclObject
{

    // virtual void function for sort, search, clone
    //virtual void sortDS()=0;
    //virtual void searchDS()=0;
    virtual void printDS()=0;
    //virtual void deleteDS()=0;
    //virtual void cloneDS()=0;

};

const int SIZE = 3;
template <class T>
struct Queue : public Datastruct
{
    private:
        vector<T> queue; // declare the queue

    public:
        void Push(T V) { queue.push_back(V); } // add an elemnt to the back of queue
        void Pop() { queue.erase(queue.begin()); } // remove elementn at the front 
        T Front() { return queue.front(); } // return the elemnt at front of the queue
        T Back() { return queue.back(); } // return elements at the back of the queue
        int Size() { return queue.size(); } // number of elements in the queue
        bool Empty() { return queue.empty(); } // return true if queue is empty and otherwise
        bool Full() { return false; }

        void printDS()
        {
             if (Empty()) //If the queue is empty:
                 {
                    cout << "Empty" << endl;
                    return;
                 }

            for (int i = 0; i < Size(); i++)
                {
                cout << Front() << ":";
                Push(Front());
                Pop();
                }
                cout << endl;
        }      
};

class Program
{
    vector<string> commands; // our DSL command
    map<string, DeclObject *> runningProgram;
    // map --> {key:value, key:value, .....} collection of keys and values
    // keys are unique, dsName are unique

public:
    Program()
    {
        string comm;
        getline(cin, comm);            // getting a command from the user
        while (comm.compare("#") != 0) // # = eoline
        {
            commands.push_back(comm); // pushing back the user's inputted command to the command vectpr
            getline(cin, comm);       // A loop, asking user to input more until they input # (end of line)
        }
    }

    int countWords(string &str)
    {
        stringstream s(str); // breaks the user's command into individual words
        int counter = 0;
        string wrd;      // to store individual words
        while (s >> wrd) // reads from the stringstream object
        {
            counter++; // for each word, increase the counter
        }
        return counter;
    }

    void deallocProgram()
    {
        for (auto &item : runningProgram)
        {
            delete item.second;
            item.second = nullptr;
        }
        runningProgram.clear();
    }

    void parseCommands()
    {
        for (auto c : commands) // for each of the user's commands
        {
            // cout << c << endl;
            stringstream s(c);              // allows you to read a string as if it were a stream (like cin)
            int numOfWords = countWords(c); // count the number of words in a user's command
            string commandType;
            s >> commandType;
            if (commandType.compare("Var") == 0)
            {
                if (numOfWords == 4) 
                {
                    //Datastruct v;
                    string dsType;  //data structure type
                    string varType; //variable type
                    s >> dsType;    // stores the second word (the data structure type) from user's command to the object
                    s >> varType;    // stores the third word (the variable type)

                    if (dsType == "Queue")
                    {
                        Queue<int> *v= new Queue<int>;
                        v->cmd = commandType;
                        v->dstype = dsType;
                        v->itemtype = varType;
                        s >> v->dsName;
                        runningProgram[v->dsName] = v;
                    }
                }
            
            }

            if (commandType.compare("push") == 0) 
            {
                string dsName; // stores the data structure name
                string value;  // stores value or variable
                s >> dsName; //getting the data structure name and storing to dsName
                s >> value; //getting value that user wants to push and storing to value as string
                string varType = runningProgram[dsName]->getItemtype();
                
                if (varType == "integer")//FOR NOW, ONLY INTEGER
                {
                    Queue<int> *v = static_cast<Queue<int> *>(runningProgram[dsName]); 
                    
                    if (commandType.compare("push") == 0) 
                    {
                        v->Push(); 
                    }
                }

            }
            if(commandType.compare("pop") == 0) 
            {
                string dsName; // stores the data structure name
                s >> dsName; //getting the data structure name and storing to dsName
                string varType = runningProgram[dsName]->getItemtype();

                if (varType == "integer")//FOR NOW, ONLY INTEGER
                {
                    Queue<int> *v = static_cast<Queue<int> *>(runningProgram[dsName]);
                    if (commandType.compare("pop") == 0) 
                    {
                        v->Pop(); 
                    }                    
                }
            }

            if (commandType.compare("front") == 0)
            {
                string dsName; 
                s >> dsName; 

                string nodeValue;
                s >> nodeValue;

                string value;  
                s >> value; 
                string varType = runningProgram[dsName]->getItemtype();

                if (varType == "integer")//FOR NOW, ONLY INTEGER
                {
                    Queue<int> *v = static_cast<Queue<int> *>(runningProgram[dsName]);
                    if (commandType.compare("front") == 0) 
                    {   
                        v->Front(); 
                    }
                }
            }

            if (commandType.compare("back") == 0)
            {
                string dsName; 
                s >> dsName; 

                string nodeValue;
                s >> nodeValue;

                string value;  
                s >> value; 
                string varType = runningProgram[dsName]->getItemtype();

                if (varType == "integer")//FOR NOW, ONLY INTEGER
                {
                    Queue<int> *v = static_cast<Queue<int> *>(runningProgram[dsName]);
                    if (commandType.compare("back") == 0) 
                    {   
                        v->Back(); 
                    }
                }
            }

            if (commandType.compare("print") == 0) 
            {
                string var; 
                s >> var;
                string varType = runningProgram[var]->getItemtype();

                if (varType == "integer")
                {
                    if (commandType.compare("print") == 0)
                    {
                        string dstype = runningProgram[var]->getDsType(); 
                        if (dstype.compare("Queue")==0)
                        {
                            Queue<int> *v = static_cast<Queue<int> *>(runningProgram[var]);
                            v->printDS();
                        }
                    }
                }
                
            }
       

            


        }
    }
};

int main()
{
    Program p;
    // p.print();
    p.parseCommands();
    p.deallocProgram();
    cout << "Program ended" << endl;
}

