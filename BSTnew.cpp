#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <string>

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
    virtual void sortDS()=0;
    virtual void printDS()=0;
    virtual void deleteDS()=0;
    virtual void cloneDS()=0;

};

template <class T>
struct BinarySearchTree : public Datastruct {
private:
    struct node {
        T value;
        struct node* right;
        struct node* left;
    };
    struct node* root;
    vector<T>insert_order;
    int treeSize;
    void deleteTree(struct node* node) {
        if(node != NULL) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }
public:
    BinarySearchTree() {
        this->root = NULL;
        this->treeSize = 0;
    }
    ~BinarySearchTree() {
        deleteTree(this->root);
    };
    void insert(T V) {
        insert(&(this->root), V);
        insert_order.push_back(V);
    }
    void insert(struct node** node, T V) {
        if(*node == NULL) {
            struct node* tmp = new struct node;
            tmp->value = V;
            tmp->left=NULL;
            tmp->right = NULL;
            *node = tmp;
            this->treeSize++;
        } else {
            if(V > (*node)->value){
                insert(&(*node)->right, V);
            }else{
                insert(&(*node)->left, V);
            }
        }
    }
    void deleteNode(T V){
    deleteNode(V, &root);
}

    struct node* findMin(struct node **node) {
    if ((*node)->left == NULL) {
        return *node;
    }
    return findMin(&(*node)->left);
}
    void deleteNode(T V, struct node **node){
    if(*node == NULL){
        std::cout << V << " is not found on the tree" << std::endl;
        return;
    }
    if(V < (*node)->value){
        deleteNode(V, &(*node)->left);
    }else if(V > (*node)->value){
        deleteNode(V, &(*node)->right);
    }else{
        if((*node)->left == NULL && (*node)->right == NULL){
            struct node *tmp = *node;
            *node = NULL;
            delete tmp;
        }else if((*node)->left == NULL){
            struct node *tmp = *node;
            *node = (*node)->right;
            delete tmp;
        }else if((*node)->right == NULL){
            struct node *tmp = *node;
            *node = (*node)->left;
            delete tmp;
        }else{
            struct node *tmp = findMin(&(*node)->right);
            (*node)->value = tmp->value;
            deleteNode(tmp->value, &(*node)->right);
        }
        this->treeSize--;
        cout << V << endl;
    } 
    
}

    void printInOrder() {
        printInOrder(this->root);
        std::cout << std::endl;
    }
    void printInOrder(struct node* node) {
        if(node != NULL) {
            printInOrder(node->left);
            std::cout << node->value << ":";
            printInOrder(node->right);
        }
    }
    void printPreOrder() {
        printPreOrder(this->root);
        std::cout << std::endl;
    }
    void printPreOrder(struct node* node) {
        if(node != NULL) {
            std::cout << node->value << ":";
            printPreOrder(node->left);
            printPreOrder(node->right);
        }
    }
    void printPostOrder() {
        printPostOrder(this->root);
        std::cout << std::endl;
    }
    void printPostOrder(struct node* node) {
        if(node != NULL) {
            printPostOrder(node->left);
            printPostOrder(node->right);
            std::cout << node->value << ":";
        }
    }
    int size() {
        return this->treeSize;
    }
    
	T getRoot() { return root->value; };

	void printRoot(){
    cout <<getRoot()<<endl;
}
    void printDS() override {
        for(auto element : insert_order)
            cout << element << ":"; 
            cout << endl;
    }

    void deleteDS() override { 
        deleteTree(root);
        root = NULL;
        treeSize = 0;
        cout << endl;
        cout << "BST have been deleted" << endl;
    }
    bool searchDS(T V) {
        return searchDS(V, this->root);
    }
    
     bool searchDS(T V, struct node* node) {
        if (node == NULL) {
            cout << "FALSE" << endl;
            return false;
        }
        if (V == node->value) {
            cout << "TRUE" << endl;
            return true;
        }
        if (V < node->value) {
            return searchDS(V, node->left);
        }
        else {
            return searchDS(V, node->right);
        }
    }
     void sortDS() override {

    }

    
    void cloneDS() override {
        for(auto element : insert_order)
            cout << element << ":";
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

                    if (dsType == "BST")
                    {
                        BinarySearchTree<int> *v= new BinarySearchTree<int>;
                        v->cmd = commandType;
                        v->dstype = dsType;
                        v->itemtype = varType;
                        s >> v->dsName;
                        runningProgram[v->dsName] = v;
                    }
                }
            
            }

            if (commandType.compare("insert") == 0) 
            {
                string dsName; // stores the data structure name
                string value;  // stores value or variable
                s >> dsName; //getting the data structure name and storing to dsName
                s >> value; //getting value that user wants to insert and storing to value as string
                string varType = runningProgram[dsName]->getItemtype();
                
                if (varType == "integer")//FOR NOW, ONLY INTEGER
                {
                    BinarySearchTree<int> *v = static_cast<BinarySearchTree<int> *>(runningProgram[dsName]); 
                    
                    if (commandType.compare("insert") == 0) 
                    {
                        v->insert(stoi(value)); //turn string to int then insert
                    }
                }

            }
            if(commandType.compare("root") == 0) 
            {
                string dsName; // stores the data structure name
                s >> dsName; //getting the data structure name and storing to dsName
                string varType = runningProgram[dsName]->getItemtype();

                if (varType == "integer")//FOR NOW, ONLY INTEGER
                {
                    BinarySearchTree<int> *v = static_cast<BinarySearchTree<int> *>(runningProgram[dsName]);
                    if (commandType.compare("root") == 0) 
                    {
                        v->printRoot(); 
                    }                    
                }
            }
            if (commandType.compare("delete") == 0)
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
                    BinarySearchTree<int> *v = static_cast<BinarySearchTree<int> *>(runningProgram[dsName]);
                    if (commandType.compare("delete") == 0) 
                    {   int value_int = std::stoi(value);
                        v->deleteNode(stoi(value)); 
                    }
                }
            }
            if (commandType.compare("search") == 0)
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
                    BinarySearchTree<int> *v = static_cast<BinarySearchTree<int> *>(runningProgram[dsName]);
                    if (commandType.compare("search") == 0) 
                    {   int value_int = std::stoi(value);
                        cout<< v->searchDS(stoi(value)) << endl; 
                    }
                }
            }

            if (commandType.compare("inorder") == 0)
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
                    BinarySearchTree<int> *v = static_cast<BinarySearchTree<int> *>(runningProgram[dsName]);
                    if (commandType.compare("inorder") == 0) 
                    {   
                
                        v->printInOrder(); 
                    }
                }
            }

            if (commandType.compare("preorder") == 0)
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
                    BinarySearchTree<int> *v = static_cast<BinarySearchTree<int> *>(runningProgram[dsName]);
                    if (commandType.compare("preorder") == 0) 
                    {   
                        v->printPreOrder(); 
                    }
                }
            }

            if (commandType.compare("postorder") == 0)
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
                    BinarySearchTree<int> *v = static_cast<BinarySearchTree<int> *>(runningProgram[dsName]);
                    if (commandType.compare("postorder") == 0) 
                    {   
                        v->printPostOrder(); 
                    }
                }
            }


            if (commandType.compare("print") == 0)   // buat clone ceni 
            {
                string var; 
                s >> var;
                string varType = runningProgram[var]->getItemtype();

                if (varType == "integer")
                {
                    if (commandType.compare("print") == 0)
                    {
                        string dstype = runningProgram[var]->getDsType(); 
                        if (dstype.compare("BST")==0)
                        {
                            BinarySearchTree<int> *v = static_cast<BinarySearchTree<int> *>(runningProgram[var]);
                            v->printDS();
                        }
                    }
                }
                
            }
            if (commandType.compare("deleteBST") == 0)   // buat clone ceni 
            {
                string var; 
                s >> var;
                string varType = runningProgram[var]->getItemtype();

                if (varType == "integer")
                {
                    if (commandType.compare("deleteBST") == 0)
                    {
                        string dstype = runningProgram[var]->getDsType(); 
                        if (dstype.compare("BST")==0)
                        {
                            BinarySearchTree<int> *v = static_cast<BinarySearchTree<int> *>(runningProgram[var]);
                            v->deleteDS();
                        }
                    }
                }
                
            }
            if (commandType.compare("sort") == 0)   // buat clone ceni 
            {
                string var; 
                s >> var;
                string varType = runningProgram[var]->getItemtype();

                if (varType == "integer")
                {
                    if (commandType.compare("sort") == 0)
                    {
                        string dstype = runningProgram[var]->getDsType(); 
                        if (dstype.compare("BST")==0)
                        {
                            BinarySearchTree<int> *v = static_cast<BinarySearchTree<int> *>(runningProgram[var]);
                            v->sortDS();
                        }
                    }
                }
                
            }
            
       
            if (commandType.compare("clone") == 0)   // buat clone ceni 
            {
                string var; 
                s >> var;
                string varType = runningProgram[var]->getItemtype();

                if (varType == "integer")
                {
                    if (commandType.compare("clone") == 0)
                    {
                        string dstype = runningProgram[var]->getDsType(); 
                        if (dstype.compare("BST")==0)
                        {
                            BinarySearchTree<int> *v = static_cast<BinarySearchTree<int> *>(runningProgram[var]);
                            v->cloneDS();
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
