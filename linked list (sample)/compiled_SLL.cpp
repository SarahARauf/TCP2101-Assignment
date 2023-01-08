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

template<typename T>
class SLL: public Datastruct
{
private:

    // Declare a structure for the list
    struct Node{
        T value;    // The value stored in this node
        Node *next; // To point to the next node
    };

    Node *head; // List head pointer
    int listSize; // Size of list

    void *getNew(T newValue){ // Creates a new node

        Node *newNode = new Node;     // Allocates memory for the new node
        newNode->value = newValue;    // Initializes the contents of the node
        newNode->next = nullptr;      // Sets the pointer field to nullptr

        return newNode;
    };

    void *movetoend(){
        Node *ptr = head;
        while(ptr->next != nullptr)
        ptr=ptr->next;
        return ptr;
    };

public:

    // Constructor
    SLL(){
        head = nullptr; 
        listSize = 0;
    }

    // Destructor
    ~SLL(){

        // To traverse the list in the while statement
        // Position nodePtr at the head of the list.
        Node *ptr = head; 
        Node *nextNode; // To point to the next node
    
        // While nodePtr is not at the end of the list...
        while (ptr != nullptr)
        {
            // Save a pointer to the next node.
            nextNode = ptr->next;
            
            // Delete the current node.
            delete ptr;

            // Position nodePtr at the next node.
            ptr = nextNode;
        }
    };

    // Operations

    // AddE = adds node to the end of the list.
    void push_back(T newValue){ 

        // Creates a new node
        Node *newNode = static_cast<Node*>(getNew(newValue));

        listSize++; // Increases the size of list since new node is created

        // If the head is empty (aka not pointing to anything), head will point to the new node
        if (head == nullptr) { 
            head = newNode;
        } 

        // Else, set the current last node to point to the new node
        // The new node will then point to 'nullptr'
        else {
            Node *ptr = static_cast<Node*> (movetoend()); //
            ptr->next = newNode;
            newNode->next = nullptr; 
        }
    };

    //AddF = adds node to the front of the list.
    void push_front(T newValue){ 

        // Creates a new node
        Node *newNode = static_cast<Node*>(getNew(newValue));
        
        listSize++; // Increases the size of list since new node is created

        // If the head is empty , head will point to the new node
        if(head == nullptr)
        {
            head = newNode;
        }
        // Else, set the head to point to the new node
        else
        {
            newNode->next = head;
            head = newNode;
        }
    };
    

    // DelF = Delete a node from the front
    void delete_front(){

        if(head == nullptr){
            cout << "Linked list is empty !" << endl;
            // return false;
        }

        Node *ptr = head;     // set a pointer to the contents of the head pointer
        head = head->next;    // points head to the next node i.e. second node
        
        cout << "First item is removed" << endl;

        delete ptr;
        listSize--;
    };


    // DelE = Delete a node from the end.
    void delete_back(){

        if(head == nullptr){
            cout<<"Linked list is empty !"<<endl;
            // return false;
        }

        // To traverse the list in the while statement
        Node *cur = head; 
        Node *prev = nullptr;

        while(cur->next)
        {
            prev = cur;             
            cur = cur->next;        // points current node ptr to the next node
        }
        
        prev->next = nullptr;       // points to the previous element (last second element)
                                    // Change next pointer to null

        cout << "Last item is removed" <<endl;
        
        delete cur;
        listSize--;
        };


    // AddA = Insert value AFTER a node (so nodeValue cannot be = 0, since nothing comes before the first element)
    void insert(int nodeValue, T newValue){

        if(nodeValue > listSize || nodeValue < 0){
            cout << "Node value is out of bound !" << endl;
            // return false;
        }

        // Creates a new node
        Node *newNode = static_cast<Node*>(getNew(newValue));

        listSize++; // Increases the size of list since new node is created

        // To traverse the list in the while statement
        Node *cur = head; // set a pointer to the contents of the head pointer

        int count = 0;

        // Note: have to redo this part.
        while(cur != nullptr && count < nodeValue){
            if(count == (nodeValue-1)){ 
                if(cur->next != nullptr){
                    newNode->next = cur->next; // Make next ptr of new node as next of cur
                }
                cur->next = newNode; // move the next of cur as newNode
                cout<<"New node is added at the node value " << nodeValue << " !" << endl;
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

    int getSize(){return listSize;} 
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

                    if (dsType == "SLL")
                    {
                        SLL<int> *v= new SLL<int>;
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
                string dsName; // stores the data structure name
                string value;  // stores value or variable
                s >> dsName; //getting the data structure name and storing to dsName
                s >> value; //getting value that user wants to push and storing to value as string
                string varType = runningProgram[dsName]->getItemtype();
                
                if (varType == "integer")//FOR NOW, ONLY INTEGER
                {
                    SLL<int> *v = static_cast<SLL<int> *>(runningProgram[dsName]); 
                    
                    if (commandType.compare("AddE") == 0) 
                    {
                        v->push_back(stoi(value)); //turn string to int then push
                    }
                    if (commandType.compare("AddF") == 0) 
                    {
                        v->push_front(stoi(value)); //turn string to int then push
                    }
                }

            }
            if(commandType.compare("DelE") == 0 || commandType.compare("DelF") == 0)
            {
                string dsName; // stores the data structure name
                s >> dsName; //getting the data structure name and storing to dsName
                string varType = runningProgram[dsName]->getItemtype();

                if (varType == "integer")//FOR NOW, ONLY INTEGER
                {
                    SLL<int> *v = static_cast<SLL<int> *>(runningProgram[dsName]);
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

                if (varType == "integer")//FOR NOW, ONLY INTEGER
                {
                    SLL<int> *v = static_cast<SLL<int> *>(runningProgram[dsName]);
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
                        if (dstype.compare("SLL")==0)
                        {
                            SLL<int> *v = static_cast<SLL<int> *>(runningProgram[var]);
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
