#include <iostream>
#include <vector>
#include <map>
#include <sstream>


using namespace std;


//Idea, make finding datatype a separate function, and possible returing a pointer with the appropriate datatype 

struct DeclObject // A struct to declare the syntax of our DSL command
{
    string cmd;      // Var
    string dstype;   // Type of datastructure/or variable
    string itemtype; // The datatype of the variable
    string dsName;   // name given
    string getItemtype() { return itemtype; } //Returns datatype
    string getDsName() { return dsName;}
};


template <typename T> //Template, so that a variable can accept any datatype
struct Variable : public DeclObject
{
    // string name;
    T value; // Store value of the variable

    // Some overloading, to distinguish between value assignment or variable assignment
    void setValue(const Variable &val) // For assigning a variable to this variable //= <var> <var1>
    {
        value = val.value; //the value of val is assigned to this value
    }

    void setValue(T val) // for assigning a value to this variable //= <var> <value>
    {
        value = val;
    }

    T getValue(){
        //cout << "inside the function:" << value << endl;
        return value;
    }

    // void print()
    // {
    //     cout << value << endl;
    // }
};

// Ignore all this for now:
struct Datastruct : public DeclObject
{

    // virtual void function for sort, search, clone
};

struct SLL : public Datastruct
{
};

struct DLL : public Datastruct
{
};

struct Stack : public Datastruct
{
};

struct Queue : public Datastruct
{
};

struct BinarySearchTree : public Datastruct
{
};

struct Vector : public Datastruct
{
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
    
    void deallocProgram(){
        for (auto &item : runningProgram) {
            delete item.second;
            item.second = nullptr;
        }
        runningProgram.clear();
    }

    void parseCommands()
    {
        for (auto c : commands) // for each of the user's commands
        {
            //cout << c << endl;
            stringstream s(c);              // allows you to read a string as if it were a stream (like cin)
            int numOfWords = countWords(c); // count the number of words in a user's command
            string commandType;
            s >> commandType;
            if (commandType.compare("Var") == 0)
            {
                if (numOfWords == 4) // for data structure Var <DS type> <Data type> <DS Name> (implement later)
                {
                    Datastruct v;
                    v.cmd = commandType;
                    s >> v.dstype;                 // stores the second word (the data structure type) from user's command to the object
                    s >> v.itemtype;               // stores the third word (the variable type)
                    s >> v.dsName;                 // stores the fourth word (name given to the data structure)
                    runningProgram[v.dsName] = &v; // Adding the address of object v to the running program, with the key being the dsName
                }
                else
                { // for variable Var <var type> <var name>
                    string DStype = "Variable";
                    string varType;
                    s >> varType;
                    if (varType == "real")
                    {
                        Variable<double> *v = new Variable<double>;
                        v->cmd = commandType;
                        v->dstype = DStype;
                        v->itemtype = varType;
                        s >> v->dsName;
                        runningProgram[v->dsName] = v; // add object to the runningProgram, key is dsName, therefore dsName should be unique
                    }
                    else if (varType == "integer")
                    {
                        Variable<int> *v = new Variable<int>;
                        v->cmd = commandType;
                        v->dstype = DStype;
                        v->itemtype = varType;
                        s >> v->dsName;
                        runningProgram[v->dsName] = v;
                        //cout << "Here, I'm creating var: " << &v << endl;
                    }
                    else if (varType == "bool")
                    {
                        Variable<bool> *v = new Variable<bool>;
                        v->cmd = commandType;
                        v->dstype = DStype;
                        v->itemtype = varType;
                        s >> v->dsName;
                        runningProgram[v->dsName] = v;
                    }
                    else if (varType == "pointer")
                    {
                        Variable<void *> v;
                        v.cmd = commandType;
                        v.dstype = DStype;
                        v.itemtype = varType;
                        s >> v.dsName;
                        runningProgram[v.dsName] = &v;
                    }
                }
            }

            if (commandType.compare("=") == 0) //= <var> <value>, = <var> <var1>
            {
                string var;
                s >> var;                                            // var name
                string varType = runningProgram[var]->getItemtype(); // to get the datatype of var
                string value; // either <value> or <var1>
                s >> value;
                if (runningProgram.find(value) != runningProgram.end()) // for variable assignment  = <var> <var1>
                {//if the value is a variable name that is located in the runningProgram map:
                    if (varType == "integer")
                    {
                        //runningProgram[] is a DeclObject pointer, which is a parent class to Variable, 
                        //so in order to use the subclass method (in this case setValue) we need to downcast the DeclObject pointer to a Variable pointer
                        Variable<int> *vptr = static_cast<Variable<int> *>(runningProgram[var]);
                        Variable<int> *vptr2 = static_cast<Variable<int> *>(runningProgram[value]);
                        vptr->setValue(*vptr2); //Passing vptr2

                    }
                    if (varType == "real")
                    {
                        Variable<double> *vptr = static_cast<Variable<double> *>(runningProgram[var]);
                        Variable<double> *vptr2 = static_cast<Variable<double> *>(runningProgram[value]);
                        vptr->setValue(*vptr2);
                    }
                    if (varType == "bool")
                    {
                        Variable<bool> *vptr = static_cast<Variable<bool> *>(runningProgram[var]);
                        Variable<bool> *vptr2 = static_cast<Variable<bool> *>(runningProgram[value]);
                        vptr->setValue(*vptr2);
                    }
                    if (varType == "pointer") // Need further clarification on this
                    {
                        void *value;
                    };

                }
                else //for value assignment //= <var> <value>
                {//if the value is not a variable name:
                    //cout <<var <<":" <<value << endl;
                    if (varType == "integer")
                    {
                        Variable<int> *vptr = static_cast<Variable<int> *>(runningProgram[var]);
                        vptr->setValue(stoi(value)); //stoi will turn the value (which is currently a string) into an integer
                    }
                    if (varType == "real")
                    {
                        Variable<double> *vptr = static_cast<Variable<double> *>(runningProgram[var]);
                        vptr->setValue(stod(value)); //stod will turn the value (which is currently a string) into an decimal
                    }
                    if (varType == "bool")
                    {
                        //turning the string value into a boolean (theres no other way to change the type of a string into a bool using sto_)
                        bool bvalue;
                        istringstream(value) >> bvalue;  //stringstream for value is created so that it can be assigned into a bool variable
                        Variable<bool> *vptr = static_cast<Variable<bool> *>(runningProgram[var]);
                        vptr->setValue(bvalue);
                    }
                    if (varType == "pointer") // Need further clarification on this
                    {
                        void *value;
                    };
                }

            }

            if (commandType.compare("+") == 0)
            {
                string var;
                s >> var;
                string varType = runningProgram[var]->getItemtype(); // to get the datatype of var
                string value; // either <value> or <var1>
                s >> value;

            }

            if (commandType.compare("print") == 0) 
            { 
                //prints the value according to the name of the variable

                //runningProgram[var] is a DeclObject pointer, which is the parent class to the Variable subclass, 
                //hence, to access the methods (in this case, the getValue method, which resides in the Variable class) of the subclass, 
                //we need to downcast the DeclObject pointer to a Variable pointer
                string var;
                s >> var;
                string varType = runningProgram[var]->getItemtype(); // to get the datatype of var 
                if (varType == "integer")
                {
                    Variable<int> *vptr = static_cast<Variable<int>*>(runningProgram[var]);
                    cout << vptr->getValue() << endl;
                    //cout << vptr -> getDsName() << endl;
                }
                else if (varType == "real")
                {
                    Variable<double> *vptr = static_cast<Variable<double>*>(runningProgram[var]);
                    cout << vptr->getValue() <<endl;
                }
                else if (varType == "bool")
                {
                    Variable<bool> *vptr = static_cast<Variable<bool>*>(runningProgram[var]);
                    cout << boolalpha << vptr->getValue() << endl;
                }
                
            }

            //Will implement later:
            // if (commandType.compare("Delete") == 0)
            // {
            //     string dsName;
            //     s >> dsName;
            //     runningProgram.erase(v.dsName == dsName);
            // }
        }
    }

    //May be deleted later:
    // void print()
    // {
    //     for (auto c : commands)
    //     {
    //         cout << c << endl;
    //     }
    // }
};

int main()
{
    Program p;
    //p.print();
    p.parseCommands();
    p.deallocProgram();
    cout << "Program ended" << endl;
    
}