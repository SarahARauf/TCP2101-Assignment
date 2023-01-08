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

template <typename T>
class DLL : public Datastruct{
private:
    struct Node 
    {
        T value;
        Node* next;
        Node* prev;
        Node(T value) : value(value), next(nullptr), prev(nullptr) {}
    };

  Node* head;
  Node* tail;
  int listSize;

public:
    DLL() : head(nullptr), tail(nullptr), listSize(0) {}

    void push_front(T value) {
        Node* node = new Node(value);
        if (head == nullptr) {
        head = tail = node;
        } else {
        node->next = head;
        head->prev = node;
        head = node;
        }
        listSize++;
    }

    void push_back(T value) {
        Node* node = new Node(value);
        if (tail == nullptr) {
        head = tail = node;
        } else {
        tail->next = node;
        node->prev = tail;
        tail = node;
        }
        listSize++;
    }

    void delete_front() {
        if (head == nullptr) {return;}

        Node* cur = head;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        }
        delete cur;
        listSize--;
    }

    void delete_back() {
        if (tail == nullptr) {return;}
        Node* cur = tail;
        tail = tail->prev;
        if (tail != nullptr) {
        tail->next = nullptr;
        }
        delete cur;
        listSize--;
    }

    // AddA = Insert value AFTER a node (so nodeValue cannot be = 0, since nothing comes before the first element)
    void insert(int nodeValue, T value){

        if(nodeValue > listSize || nodeValue < 0){
            cout << "Node value out of bound !" << endl;
            // return false;
        }

        // Creates a new node
        Node* node = new Node(value);

        listSize++; // Increases the size of list since new node is created

        // To traverse the list in the while statement
        Node *cur = head; // set a pointer to the contents of the head pointer
        int count = 0;

        // Note: have to redo this part.
        while(cur != nullptr && count < nodeValue){
            if(count == (nodeValue-1)){ 
                if(cur->next != nullptr){
                    node->next = cur->next; // Make next ptr of new node as next of cur
                }
                node->prev = cur;
                cur->next = node;
                cout<<"~ New node added at the node value " << nodeValue << " !" << endl;
                // return true;
                break;
            }
            count++;
            cur = cur->next;
        }
    };


    void printDS(){
        
        // To move through the list in the while statement.
        Node *ptr = head; // Position ptr at the head of the list.
        
        // While ptr points to a node, traverse the list.
        while (ptr != nullptr)
        {
            cout << ptr->value << ":";
            ptr=ptr->next;
        }
        cout << endl;
    };

    // NOT NEEDED (?)
    // void print_back() 
    // {
    //     Node *ptr = tail;
    //     while (ptr!=nullptr){
    //         cout << ptr->value << ":";
    //         ptr=ptr->prev;
    //     }
    //     cout << endl;
    // }

  int getlistSize(){
    return listSize;
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
                if (numOfWords == 4) // for data structure Var <DS type> <Data type> <DS Name> (implement later)
                {
                    //Datastruct v;
                    string dsType;  //data structure type
                    string varType; //variable type
                    s >> dsType;    // stores the second word (the data structure type) from user's command to the object
                    s >> varType;    // stores the third word (the variable type)

                    if (dsType == "DLL")
                    {
                        DLL<int> *v= new DLL<int>;
                        v->cmd = commandType;
                        v->dstype = dsType;
                        v->itemtype = varType;
                        s >> v->dsName;
                        runningProgram[v->dsName] = v;
                    }
                }
            
            }

            if (commandType.compare("AddE") == 0 || commandType.compare("AddF") == 0)
            {
                string dsName; 
                string value;  
                s >> dsName; 
                s >> value; 
                string varType = runningProgram[dsName]->getItemtype();
                
                if (varType == "integer")//FOR NOW, ONLY INTEGER
                {
                    DLL<int> *v = static_cast<DLL<int> *>(runningProgram[dsName]); 
                    
                    if (commandType.compare("AddE") == 0) 
                    {
                        v->push_back(stoi(value)); 
                    if (commandType.compare("AddF") == 0) 
                    {
                        v->push_front(stoi(value)); 
                    }
                }

            }
            if(commandType.compare("DelE") == 0 || commandType.compare("DelF") == 0)
            {
                string dsName; 
                s >> dsName; 
                string varType = runningProgram[dsName]->getItemtype();

                if (varType == "integer")//FOR NOW, ONLY INTEGER
                {
                    DLL<int> *v = static_cast<DLL<int> *>(runningProgram[dsName]);
                    if (commandType.compare("DelE") == 0) 
                    {
                        v->delete_back(); 
                    }                    
                    if (commandType.compare("DelF") == 0) 
                    {
                        v->delete_front(); 
                    }
                }
            }

            if (commandType.compare("AddA") == 0)
            {
                string dsName;
                s >> dsName; 

                string nodeValue;
                s >> nodeValue;

                string value;  
                s >> value;
                string varType = runningProgram[dsName]->getItemtype();

                if (varType == "integer")
                    DLL<int> *v = static_cast<DLL<int> *>(runningProgram[dsName]);
                    if (commandType.compare("AddA") == 0) 
                    {   
                        v->insert(stoi(nodeValue), stoi(value)); 
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
                        if (dstype.compare("DLL")==0)
                        {
                            DLL<int> *v = static_cast<DLL<int> *>(runningProgram[var]);
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
