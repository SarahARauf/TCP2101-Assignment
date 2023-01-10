#include <iostream>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

// Idea, make finding datatype a separate function, and possible returing a pointer with the appropriate datatype

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

template <typename T> // Template, so that a variable can accept any datatype
struct operations
{
    map<string, DeclObject *> runningProgram;

    operations(map<string, DeclObject *> &runningProgram)
    {
        this->runningProgram = runningProgram;
    }

    void assg_commands(string var, string value) // op = operation, var = variable to assign value to, assg = value or variable to assign from
    {
        if (runningProgram.find(value) != runningProgram.end())
        {
            assignVariable(var, value);
        }
        else
        {
            assignValue(var, value);
        }
    }

    void print_command(string var)
    {
        Variable<T> *vptr = static_cast<Variable<T> *>(runningProgram[var]);
        string varType = runningProgram[var]->getItemtype();

        if (varType == "bool")
        {
            cout << boolalpha << vptr->getValue() << endl;
        }
        else
        {
            cout << vptr->getValue() << endl;
        }
    }

    void addition(string var, string value)
    {
        if (runningProgram.find(value) != runningProgram.end())
        {
            additionVariable(var, value);
        }
        else
        {
            additionValue(var, value);
        }
    }

    void subtraction(string var, string value)
    {
        if (runningProgram.find(value) != runningProgram.end())
        {
            subtractionVariable(var, value);
        }
        else
        {
            subtractionValue(var, value);
        }
    }

    void multiplication(string var, string value)
    {
        if (runningProgram.find(value) != runningProgram.end())
        {
            multiplicationVariable(var, value);
        }
        else
        {
            multiplicationValue(var, value);
        }
    }

    void division(string var, string value)
    {
        if (runningProgram.find(value) != runningProgram.end())
        {
            divisionVariable(var, value);
        }
        else
        {
            divisionValue(var, value);
        }
    }

    void mod(string var, string value)
    {
        if (runningProgram.find(value) != runningProgram.end())
        {
            modVariable(var, value);
        }
        else
        {
            modValue(var, value);
        }
    }

private:
    void assignValue(string var, string value)
    {
        T val;
        istringstream(value) >> val;
        Variable<T> *vptr = static_cast<Variable<T> *>(runningProgram[var]);
        vptr->setValue(val);

        // T val;
        // istringstream(value) >> val;
        // Variable<T> *vptr = runningProgram[var];
        // vptr->setValue(val);
    }

    void assignVariable(string var, string value)
    {
        Variable<T> *vptr = static_cast<Variable<T> *>(runningProgram[var]);
        Variable<T> *vptr2 = static_cast<Variable<T> *>(runningProgram[value]);
        vptr->setValue(*vptr2);
    }

    void additionVariable(string var, string value)
    {
        Variable<T> *vptr = static_cast<Variable<T> *>(runningProgram[var]);
        Variable<T> *vptr2 = static_cast<Variable<T> *>(runningProgram[value]);
        T addend1 = vptr->getValue();
        T addend2 = vptr2->getValue();
        T sum1 = addend1 + addend2;
        ostringstream oss;
        oss << sum1;
        string sum2 = oss.str();
        assignValue(var, sum2);
    }

    void additionValue(string var, string value)
    {
        T addend2;
        istringstream(value) >> addend2;
        Variable<T> *vptr = static_cast<Variable<T> *>(runningProgram[var]);
        T addend1 = vptr->getValue();
        T sum1 = addend1 + addend2;
        ostringstream oss;
        oss << sum1;
        string sum2 = oss.str();
        assignValue(var, sum2);
    }

    void subtractionVariable(string var, string value)
    {
        Variable<T> *vptr = static_cast<Variable<T> *>(runningProgram[var]);
        Variable<T> *vptr2 = static_cast<Variable<T> *>(runningProgram[value]);
        T minuend = vptr->getValue();
        T subtrahend = vptr2->getValue();
        T difference1 = minuend - subtrahend;
        ostringstream oss;
        oss << difference1;
        string difference2 = oss.str();
        assignValue(var, difference2);
    }

    void subtractionValue(string var, string value)
    {
        T subtrahend;
        istringstream(value) >> subtrahend;
        Variable<T> *vptr = static_cast<Variable<T> *>(runningProgram[var]);
        T minuend = vptr->getValue();
        T difference1 = minuend - subtrahend;
        ostringstream oss;
        oss << difference1;
        string difference2 = oss.str();
        assignValue(var, difference2);
    }

    void multiplicationVariable(string var, string value)
    {
        Variable<T> *vptr = static_cast<Variable<T> *>(runningProgram[var]);
        Variable<T> *vptr2 = static_cast<Variable<T> *>(runningProgram[value]);
        T multiplicand = vptr->getValue();
        T multiplier = vptr2->getValue();
        T product1 = multiplicand * multiplier;
        ostringstream oss;
        oss << product1;
        string product2 = oss.str();
        assignValue(var, product2);
    }

    void multiplicationValue(string var, string value)
    {
        T multiplier;
        istringstream(value) >> multiplier;
        Variable<T> *vptr = static_cast<Variable<T> *>(runningProgram[var]);
        T multiplicand = vptr->getValue();
        T product1 = multiplicand * multiplier;
        ostringstream oss;
        oss << product1;
        string product2 = oss.str();
        assignValue(var, product2);
    }

    void divisionVariable(string var, string value)
    {
        Variable<T> *vptr = static_cast<Variable<T> *>(runningProgram[var]);
        Variable<T> *vptr2 = static_cast<Variable<T> *>(runningProgram[value]);
        T dividend = vptr->getValue();
        T divisor = vptr2->getValue();
        T quotient1 = dividend / divisor;
        ostringstream oss;
        oss << quotient1;
        string quotient2 = oss.str();
        assignValue(var, quotient2);

    }

    void divisionValue(string var, string value)
    {
        T divisor;
        istringstream(value) >> divisor;
        Variable<T> *vptr = static_cast<Variable<T> *>(runningProgram[var]);
        T dividend = vptr->getValue();
        T quotient1 = dividend / divisor;
        ostringstream oss;
        oss << quotient1;
        string quotient2 = oss.str();
        assignValue(var, quotient2);

    }

    void modVariable(string var, string value)
    {
        Variable<T> *vptr = static_cast<Variable<T> *>(runningProgram[var]);
        Variable<T> *vptr2 = static_cast<Variable<T> *>(runningProgram[value]);
        T dividend = vptr->getValue();
        T divisor = vptr2->getValue();
        T remainder1 = dividend % divisor;
        ostringstream oss;
        oss << remainder1;
        string remainder2 = oss.str();
        assignValue(var, remainder2);

    }

    void modValue(string var, string value)
    {
        T divisor;
        istringstream(value) >> divisor;
        Variable<T> *vptr = static_cast<Variable<T> *>(runningProgram[var]);
        T dividend = vptr->getValue();
        T remainder1 = dividend % divisor;
        ostringstream oss;
        oss << remainder1;
        string remainder2 = oss.str();
        assignValue(var, remainder2);

    }
};

// Ignore all this for now:
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
struct Stack : public Datastruct 
{
    T data[SIZE];
    int top;

    Stack()
    {
        top = -1;
    }

    void push(T V)
    {
        if (isFull())
        {
            cout << "Full" << endl;
            return;
        }
        top = top+1;
        data[top] = V;

    }

    void pop()
    {
        if (isEmpty()) //If the stack is empty:
        {
            cout << "Empty" << endl;
            return;
        }
        data[top] = 0;
        top = top-1;

    }

    T Top()
    {
        return data[top];

    }

    bool isFull()
    {
        return top == SIZE-1;

    }

    bool isEmpty()
    {
        return top == -1;
    }

    void printDS()
    {
        if (isEmpty()) //If the stack is empty:
        {
            cout << "Empty" << endl;
            return;
        }

        //int n = sizeof(data) / sizeof(data[0]);
        for (int i = top; i > -1; i--) {
            cout << data[i] << ":";
        }
        cout << endl;

    }

};

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
                cout << Front() << " ";
                Push(Front());
                Pop();
                }
                cout << endl;
        }      
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
                if (numOfWords == 4) // for data structure Var <DS type> <Data type> <DS Name> (implement later)
                {
                    //Datastruct v;
                    string dsType; //data structure type
                    string varType;//variable type
                    s >> dsType;                 // stores the second word (the data structure type) from user's command to the object
                    s >> varType;               // stores the third word (the variable type)
                    if (dsType == "Stack")
                    {
                        Stack<int> *v= new Stack<int>;
                        v->cmd = commandType;
                        v->dstype = dsType;
                        v->itemtype = varType;
                        s >> v->dsName;
                        runningProgram[v->dsName] = v;
                    }
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
                else
                { // for variable Var <var type> <var name>
                    string DStype = "Variable";
                    string varType; //data type
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
                        // cout << "Here, I'm creating var: " << &v << endl;
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

            //FOR SABRINA, STACK COMMANDS LINE 515-556
            if (commandType.compare("push") == 0) // Push <ds Name> <value|var>
            {
                string dsName; // stores the data structure name
                string value;  // stores value or variable
                s >> dsName; //getting the data structure name and storing to dsName
                s >> value; //getting value that user wants to push and storing to value as string
                string varType = runningProgram[dsName]->getItemtype();//GETTING THE VARIABLE TYPE OF THE DATA STRUCTURE
                if (varType == "integer")//FOR NOW, ONLY INTEGER
                {
                    Stack<int> *v = static_cast<Stack<int> *>(runningProgram[dsName]); //runningProgram[dsName] is a declObject* pointer, must cast to its derived class Stack in order to access methods in Stack class (push, pop, etc)
                    if (runningProgram.find(value) != runningProgram.end()) //two ways to push number into stack, through a variable (push st x) or just with a singular number (push st 5), this will check whether the value to push is a Variable (x) or Number (5) by finding if its in runningprogram map
                    {
                        Variable<int> *vptr = static_cast<Variable<int> *>(runningProgram[value]); //if it is a variable, static cast the declObject* to a variable* in order to access methods of the variable class (getValue)
                        int value = vptr->getValue();
                        v->push(value); //push the value to stack

                    }
                    else //else, pushing just a number (push st 5)
                    {
                        v->push(stoi(value)); //turn string to int then push
                    }
                }
            }

            if (commandType.compare("pop") == 0) // pop <ds Name>
            {
                string dsName; // stores the data structure name
                s >> dsName; //getting the data structure name and storing to dsName
                string varType = runningProgram[dsName]->getItemtype();
                if (varType == "integer")
                {
                    Stack<int> *v = static_cast<Stack<int> *>(runningProgram[dsName]);
                    v->pop();
                }
            }

            if (commandType.compare("top")==0)//WILL IMPLEMENT LATER
            {
                string dsName;
                string varName;
                s >> dsName;
                s >> varName;
                string varType = runningProgram[dsName]->getItemtype();
                if (varType == "integer")
                {
                    Stack<int> *vptr = static_cast<Stack<int> *>(runningProgram[dsName]);
                    Variable<int> *vptr2 = static_cast<Variable<int> *>(runningProgram[varName]);
                    int value = vptr->Top();
                    vptr2->setValue(value);
                }
            }

            if (commandType.compare("isEmpty")==0)//WILL IMPLEMENT LATER
            {
                string dsName;
                string varName;
                s >> dsName;
                s >> varName;
                string varType = runningProgram[dsName]->getItemtype();
                if (varType == "integer")
                {
                    Stack<int> *vptr = static_cast<Stack<int> *>(runningProgram[dsName]);
                    Variable<int> *vptr2 = static_cast<Variable<int> *>(runningProgram[varName]);
                    if(vptr->isEmpty())
                    {
                        vptr2->setValue(1);
                    }
                    else
                    {
                        vptr2->setValue(0);
                    }
                }
            }

            if (commandType.compare("isFull")==0)//WILL IMPLEMENT LATER
            {
                string dsName;
                string varName;
                s >> dsName;
                s >> varName;
                string varType = runningProgram[dsName]->getItemtype();
                if (varType == "integer")
                {
                    Stack<int> *vptr = static_cast<Stack<int> *>(runningProgram[dsName]);
                    Variable<int> *vptr2 = static_cast<Variable<int> *>(runningProgram[varName]);
                    if(vptr->isFull())
                    {
                        vptr2->setValue(1);
                    }
                    else
                    {
                        vptr2->setValue(0);
                    }
                }
            }
            //END OF STACK COMMANDS

            //Queue
            if (commandType.compare("Push") == 0) // Push <ds Name> <value|var>
            {
                string dsName; // stores the data structure name
                string value;  // stores value or variable
                s >> dsName; //getting the data structure name and storing to dsName
                s >> value; //getting value that user wants to push and storing to value as string
                string varType = runningProgram[dsName]->getItemtype();//GETTING THE VARIABLE TYPE OF THE DATA STRUCTURE
                if (varType == "integer")//FOR NOW, ONLY INTEGER
                {
                    Queue<int> *v = static_cast<Queue<int> *>(runningProgram[dsName]); //runningProgram[dsName] is a declObject* pointer, must cast to its derived class Stack in order to access methods in Stack class (push, pop, etc)
                    if (runningProgram.find(value) != runningProgram.end()) //two ways to push number into stack, through a variable (push st x) or just with a singular number (push st 5), this will check whether the value to push is a Variable (x) or Number (5) by finding if its in runningprogram map
                    {
                        Variable<int> *vptr = static_cast<Variable<int> *>(runningProgram[value]); //if it is a variable, static cast the declObject* to a variable* in order to access methods of the variable class (getValue)
                        int value = vptr->getValue();
                        v->Push(value); //push the value to queue

                    }
                    else //else, pushing just a number (push q 5)
                    {
                        v->Push(stoi(value)); //turn string to int then push
                    }
                }
            }

            if (commandType.compare("Pop") == 0) // pop <ds Name>
            {
                string dsName; // stores the data structure name
                s >> dsName; //getting the data structure name and storing to dsName
                string varType = runningProgram[dsName]->getItemtype();
                if (varType == "integer")
                {
                    Queue<int> *v = static_cast<Queue<int> *>(runningProgram[dsName]);
                    v->Pop();
                }
            }

            if (commandType.compare("Front")==0)
            {
                string dsName;
                string varName;
                s >> dsName;
                s >> varName;
                string varType = runningProgram[dsName]->getItemtype();
                if (varType == "integer")
                {
                    Queue<int> *vptr = static_cast<Queue<int> *>(runningProgram[dsName]);
                    Variable<int> *vptr2 = static_cast<Variable<int> *>(runningProgram[varName]);
                    int value = vptr->Front();
                    vptr2->setValue(value);
                }
            }

            if (commandType.compare("Back")==0)
            {
                string dsName;
                string varName;
                s >> dsName;
                s >> varName;
                string varType = runningProgram[dsName]->getItemtype();
                if (varType == "integer")
                {
                    Queue<int> *vptr = static_cast<Queue<int> *>(runningProgram[dsName]);
                    Variable<int> *vptr2 = static_cast<Variable<int> *>(runningProgram[varName]);
                    int value = vptr->Back();
                    vptr2->setValue(value);
                }
            }



            if (commandType.compare("IsEmpty")==0)
            {
                string dsName;
                string varName;
                s >> dsName;
                s >> varName;
                string varType = runningProgram[dsName]->getItemtype();
                if (varType == "integer")
                {
                    Queue<int> *vptr = static_cast<Queue<int> *>(runningProgram[dsName]);
                    Variable<int> *vptr2 = static_cast<Variable<int> *>(runningProgram[varName]);
                    if(vptr->Empty())
                    {
                        vptr2->setValue(1);
                    }
                    else
                    {
                        vptr2->setValue(0);
                    }
                }
            }

            if (commandType.compare("IsFull")==0)
            {
                string dsName;
                string varName;
                s >> dsName;
                s >> varName;
                string varType = runningProgram[dsName]->getItemtype();
                if (varType == "integer")
                {
                    Queue<int> *vptr = static_cast<Queue<int> *>(runningProgram[dsName]);
                    Variable<int> *vptr2 = static_cast<Variable<int> *>(runningProgram[varName]);
                    if(vptr->Full())
                    {
                        vptr2->setValue(1);
                    }
                    else
                    {
                        vptr2->setValue(0);
                    }
                }
            }
            //End of Queue


            if (commandType.compare("=") == 0 || commandType.compare("+") == 0 || commandType.compare("-") == 0 || commandType.compare("*") == 0 || commandType.compare("/") == 0 || commandType.compare("%") == 0 || commandType.compare("print") == 0) // need to distinguish between print ds v print variable
            {
                string var; //variable name /ds name
                s >> var;
                string varType = runningProgram[var]->getItemtype();

                if (varType == "integer")
                {
                    operations<int> o(runningProgram);
                    if (commandType.compare("=") == 0)
                    {
                        string value;
                        s >> value;
                        o.assg_commands(var, value);
                    }
                    if (commandType.compare("+") == 0)
                    {
                        string value;
                        s >> value;
                        o.addition(var, value);
                    }
                    if (commandType.compare("-") == 0)
                    {
                        string value;
                        s >> value;
                        o.subtraction(var, value);
                    }
                    if (commandType.compare("*") == 0)
                    {
                        string value;
                        s >> value;
                        o.multiplication(var, value);
                    }
                    if (commandType.compare("/") == 0)
                    {
                        string value;
                        s >> value;
                        o.division(var, value);
                    }
                    if (commandType.compare("%") == 0)
                    {
                        string value;
                        s >> value;
                        o.mod(var, value);
                    }
                    if (commandType.compare("print") == 0)
                    {
                        string dstype = runningProgram[var]->getDsType(); //ds or variable
                        if (dstype.compare("Stack")==0)//if stack, then use the printDs inside the stack function to print
                        {
                            Stack<int> *v = static_cast<Stack<int> *>(runningProgram[var]);
                            v->printDS();
                        }
                        else // else, printing a variable (Var integer x, = x 5, print x)
                        {
                            o.print_command(var);
                        }
                        if (dstype.compare("Queue")==0)//if queue, then use the printDs inside the queue function to print
                        {
                            Queue<int> *v = static_cast<Queue<int> *>(runningProgram[var]);
                            v->printDS();
                        }
                    }
                }
                if (varType == "real")
                {
                    operations<double> o(runningProgram);
                    if (commandType.compare("=") == 0)
                    {
                        string value;
                        s >> value;
                        o.assg_commands(var, value);
                    }
                    if (commandType.compare("+") == 0)
                    {
                        string value;
                        s >> value;
                        o.addition(var, value);
                    }
                    if (commandType.compare("-") == 0)
                    {
                        string value;
                        s >> value;
                        o.subtraction(var, value);
                    }
                    if (commandType.compare("*") == 0)
                    {
                        string value;
                        s >> value;
                        o.multiplication(var, value);
                    }
                    if (commandType.compare("/") == 0)
                    {
                        string value;
                        s >> value;
                        o.division(var, value);
                    }
                    if (commandType.compare("print") == 0)
                    {
                        o.print_command(var);
                    }
                }
                if (varType == "bool")
                {
                    operations<bool> o(runningProgram);
                    if (commandType.compare("=") == 0)
                    {
                        string value;
                        s >> value;
                        o.assg_commands(var, value);
                    }
                    if (commandType.compare("print") == 0)
                    {
                        o.print_command(var);
                    }
                }
                if (varType == "pointer")
                {
                    operations<void *> s(runningProgram);
                }
            }

            // Will implement later:
            //  if (commandType.compare("Delete") == 0)
            //  {
            //      string dsName;
            //      s >> dsName;
            //      runningProgram.erase(v.dsName == dsName);
            //  }
        }
    }

    // May be deleted later:
    //  void print()
    //  {
    //      for (auto c : commands)
    //      {
    //          cout << c << endl;
    //      }
    //  }
};

int main()
{
    Program p;
    // p.print();
    p.parseCommands();
    p.deallocProgram();
    cout << "Program ended" << endl;
}
