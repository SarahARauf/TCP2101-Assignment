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
    string varType;

    operations(map<string, DeclObject *> &runningProgram, string var)
    {
        this->runningProgram = runningProgram;
        string varType = runningProgram[var]->getItemtype();
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

template <class T>
class StackNode{
    public:
    int data;
    StackNode* next;
};

StackNode* newNode(int data) {
    StackNode* stackNode = new StackNode();
    stackNode->data = data;
    stackNode->next = NULL;
    return stackNode;
}

int isEmpty(StackNode *root) {
    return !root;
}

void push(StackNode** root, int new_data){
    StackNode* stackNode = newNode(new_data);
    stackNode->next = *root;
    *root = stackNode;
    cout << new_data << endl;
}

int pop(StackNode** root){
    if (isEmpty(*root))
    return -1;
    StackNode* temp = *root;
    *root = (*root)->next;
    int popped = temp->data;
    free(temp);

    return popped;
}
int peek(StackNode* root)
{
    if (isEmpty(root))
    return -1;
    return root-> data;
}

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

    void deallocProgram()
    {
        for (auto &item : runningProgram)
        {
            delete item.second;
            item.second = nullptr;
        }
        runningProgram.clear();
    }

    // void doOperations(string commandType, string var, stringstream &s, )
    // {
    //     if (commandType.compare("=") == 0)
    //     {
    //         string value;
    //         s >> value;
    //         o.assg_commands(var, value);
    //     }
    //     if (commandType.compare("+") == 0)
    //     {
    //         string value;
    //         s >> value;
    //         o.addition(var, value);
    //     }
    //     if (commandType.compare("-") == 0)
    //     {
    //         string value;
    //         s >> value;
    //         o.subtraction(var, value);
    //     }
    //     if (commandType.compare("*") == 0)
    //     {
    //         string value;
    //         s >> value;
    //         o.multiplication(var, value);
    //     }
    //     if (commandType.compare("/") == 0)
    //     {
    //         string value;
    //         s >> value;
    //         o.division(var, value);
    //     }
    //     if (commandType.compare("%") == 0)
    //     {
    //         string value;
    //         s >> value;
    //         o.mod(var, value);
    //     }
    //     if (commandType.compare("print") == 0)
    //     {
    //         o.print_command(var);
    //     }

    // };

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

            if (commandType.compare("=") == 0 || commandType.compare("+") == 0 || commandType.compare("-") == 0 || commandType.compare("*") == 0 || commandType.compare("/") == 0 || commandType.compare("%") == 0 || commandType.compare("print") == 0) // need to distinguish between print ds v print variable
            {
                string var;
                s >> var;
                string varType = runningProgram[var]->getItemtype();
                if (varType == "integer")
                {
                    operations<int> o(runningProgram, var);

                    //doOperations(commandType, )
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
                        o.print_command(var);
                    }
                }
                if (varType == "real")
                {
                    operations<double> s(runningProgram, var);
                }
                if (varType == "bool")
                {
                    operations<bool> s(runningProgram, var);
                }
                if (varType == "pointer")
                {
                    operations<void *> s(runningProgram, var);
                }


                // if (commandType.compare("=") == 0) //= <var> <value>, = <var> <var1>
                // {
                //     string var;
                //     s >> var;                                            // var name
                //     // string varType = runningProgram[var]->getItemtype(); // to get the datatype of var
                //     string value;                                        // either <value> or <var1>
                //     s >> value;
                //     operations s(runningProgram, var);
                //     s.assg_commands(var, value);

                // }

                // if (commandType.compare("+") == 0)
                // {
                //     string var;
                //     s >> var;
                //     //string varType = runningProgram[var]->getItemtype(); // to get the datatype of var
                //     string value;                                        // either <value> or <var1>
                //     s >> value;
                // }

                // if (commandType.compare("print") == 0)
                // {
                //     // prints the value according to the name of the variable

                //     // runningProgram[var] is a DeclObject pointer, which is the parent class to the Variable subclass,
                //     // hence, to access the methods (in this case, the getValue method, which resides in the Variable class) of the subclass,
                //     // we need to downcast the DeclObject pointer to a Variable pointer
                //     string var;
                //     s >> var;
                //     operations s(runningProgram, var);
                //     s.print_command(var);

                // }
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