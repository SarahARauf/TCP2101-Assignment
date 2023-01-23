#include "Program.h"


Program::Program()
{
    string comm;
    getline(cin, comm);            // getting a command from the user
    while (comm.compare("#") != 0) // # = eoline
    {
        commands.push_back(comm); // pushing back the user's inputted command to the command vectpr
        getline(cin, comm);       // A loop, asking user to input more until they input # (end of line)
    }
}

Program :: ~Program()
{
    runningProgram.clear();


}

int Program::countWords(string &str)
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

// void Program::deallocProgram()
// {
//     // for (auto &item : runningProgram)
//     // {
//     //     delete item.second;
//     //     item.second = nullptr;
//     // }
// }

void Program::parseCommands()
{
    for (auto c : commands) // for each of the user's commands
    {
        stringstream s(c);              // allows you to read a string as if it were a stream (like cin)
        int numOfWords = countWords(c); // count the number of words in a user's command
        string commandType;
        s >> commandType;
        if (commandType.compare("Var") == 0)
        {
            if (numOfWords == 4) // for data structure Var <DS type> <Data type> <DS Name> (implement later)
            {
                // Datastruct v;
                string dsType;  // data structure type
                string varType; // variable type
                s >> dsType;    // stores the second word (the data structure type) from user's command to the object
                s >> varType;   // stores the third word (the variable type)

                if (varType == "integer")
                {
                    if (dsType == "Stack") //instead of creating individual pointers, use declObject to put the items into the map
                    {
                        Stack<int> *v = new Stack<int>;
                        v->cmd = commandType;
                        v->dstype = dsType;
                        v->itemtype = varType;
                        s >> v->dsName;
                        runningProgram[v->dsName] = v;
                    }
                    if (dsType == "Queue")
                    {
                        Queue<int> *v = new Queue<int>;
                        v->cmd = commandType;
                        v->dstype = dsType;
                        v->itemtype = varType;
                        s >> v->dsName;
                        runningProgram[v->dsName] = v;
                    }

                }
                if (varType == "real")
                {
                    if (dsType == "Stack") //instead of creating individual pointers, use declObject to put the items into the map
                    {
                        Stack<double> *v = new Stack<double>;
                        v->cmd = commandType;
                        v->dstype = dsType;
                        v->itemtype = varType;
                        s >> v->dsName;
                        runningProgram[v->dsName] = v;
                    }
                    if (dsType == "Queue")
                    {
                        Queue<double> *v = new Queue<double>;
                        v->cmd = commandType;
                        v->dstype = dsType;
                        v->itemtype = varType;
                        s >> v->dsName;
                        runningProgram[v->dsName] = v;
                    }

                }
            }
            else
            { // for variable Var <var type> <var name>
                string DStype = "Variable";
                string varType; // data type
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
            }
        }

        else if (commandType.compare("push") == 0 || commandType.compare("pop") == 0 || commandType.compare("top") == 0 || commandType.compare("isEmpty") == 0 || commandType.compare("isFull") == 0 || commandType.compare("clone") == 0 || commandType.compare("delete") == 0 || commandType.compare("search") == 0 )
        {
            string dsName;                                          // stores the data structure name
            string value;                                           // stores value or variable
            s >> dsName;                                            // getting the data structure name and storing to dsName
            s >> value;                                             // getting value that user wants to push and storing to value as string
            string varType = runningProgram[dsName]->getItemtype(); // GETTING THE VARIABLE TYPE OF THE DATA STRUCTURE
            string dsType = runningProgram[dsName]->getDsType();


            if (commandType.compare("push") == 0) // Push <ds Name> <value|var>
            {
                if (varType == "integer")                               // FOR NOW, ONLY INTEGER
                {
                    if (dsType == "Stack")
                    {

                        Stack<int> *v = static_cast<Stack<int> *>(runningProgram[dsName]); // runningProgram[dsName] is a declObject* pointer, must cast to its derived class Stack in order to access methods in Stack class (push, pop, etc)
                        if (runningProgram.find(value) != runningProgram.end())            // two ways to push number into stack, through a variable (push st x) or just with a singular number (push st 5), this will check whether the value to push is a Variable (x) or Number (5) by finding if its in runningprogram map
                        {
                            Variable<int> *vptr = static_cast<Variable<int> *>(runningProgram[value]); // if it is a variable, static cast the declObject* to a variable* in order to access methods of the variable class (getValue)
                            int value = vptr->getValue();
                            v->push(value); // push the value to stack
                        }
                        else // else, pushing just a number (push st 5)
                        {

                            v->push(stoi(value)); // turn string to int then push

                        }
                    }
                    if (dsType == "Queue")
                    {
                        Queue<int> *v = static_cast<Queue<int> *>(runningProgram[dsName]); // runningProgram[dsName] is a declObject* pointer, must cast to its derived class Stack in order to access methods in Stack class (push, pop, etc)
                        if (runningProgram.find(value) != runningProgram.end())            // two ways to push number into stack, through a variable (push st x) or just with a singular number (push st 5), this will check whether the value to push is a Variable (x) or Number (5) by finding if its in runningprogram map
                        {
                            Variable<int> *vptr = static_cast<Variable<int> *>(runningProgram[value]); // if it is a variable, static cast the declObject* to a variable* in order to access methods of the variable class (getValue)
                            int value = vptr->getValue();
                            v->push(value); // push the value to stack
                        }
                        else // else, pushing just a number (push st 5)
                        {
                            v->push(stoi(value)); // turn string to int then push
                        }
                    }

                }

                if (varType == "real")                            
                {
                    if (dsType == "Stack")
                    {
                        Stack<double> *v = static_cast<Stack<double> *>(runningProgram[dsName]); // runningProgram[dsName] is a declObject* pointer, must cast to its derived class Stack in order to access methods in Stack class (push, pop, etc)
                        if (runningProgram.find(value) != runningProgram.end())            // two ways to push number into stack, through a variable (push st x) or just with a singular number (push st 5), this will check whether the value to push is a Variable (x) or Number (5) by finding if its in runningprogram map
                        {
                            Variable<double> *vptr = static_cast<Variable<double> *>(runningProgram[value]); // if it is a variable, static cast the declObject* to a variable* in order to access methods of the variable class (getValue)
                            double value = vptr->getValue();
                            v->push(value); // push the value to stack
                        }
                        else // else, pushing just a number (push st 5)
                        {

                            v->push(stod(value)); // turn string to int then push

                        }
                    }
                    if (dsType == "Queue")
                    {
                        Queue<double> *v = static_cast<Queue<double> *>(runningProgram[dsName]); // runningProgram[dsName] is a declObject* pointer, must cast to its derived class Stack in order to access methods in Stack class (push, pop, etc)
                        if (runningProgram.find(value) != runningProgram.end())            // two ways to push number into stack, through a variable (push st x) or just with a singular number (push st 5), this will check whether the value to push is a Variable (x) or Number (5) by finding if its in runningprogram map
                        {
                            Variable<double> *vptr = static_cast<Variable<double> *>(runningProgram[value]); // if it is a variable, static cast the declObject* to a variable* in order to access methods of the variable class (getValue)
                            double value = vptr->getValue();
                            v->push(value); // push the value to stack
                        }
                        else // else, pushing just a number (push st 5)
                        {
                            v->push(stod(value)); // turn string to int then push
                        }
                    }

                }
            }

            else if (commandType.compare("pop") == 0) // pop <ds Name>
            {
                //cout << "in pop" << endl;

                // string dsName; // stores the data structure name
                // s >> dsName;   // getting the data structure name and storing to dsName
                // string varType = runningProgram[dsName]->getItemtype();
                if (varType == "integer")
                {
                    if (dsType == "Stack")
                    {
                        Stack<int> *v = static_cast<Stack<int> *>(runningProgram[dsName]);
                        v->pop();
                    }
                    if (dsType == "Queue")
                    {
                        Queue<int> *v = static_cast<Queue<int> *>(runningProgram[dsName]);
                        v->pop();

                    }
                }
                if (varType == "real")
                {
                    if (dsType == "Stack")
                    {
                        Stack<double> *v = static_cast<Stack<double> *>(runningProgram[dsName]);
                        v->pop();
                    }
                    if (dsType == "Queue")
                    {
                        Queue<double> *v = static_cast<Queue<double> *>(runningProgram[dsName]);
                        v->pop();

                    }
                }
            }

            else if (commandType.compare("top") == 0 || commandType.compare("front") == 0 || commandType.compare("back") == 0) //  top <dsName> <variable>
            {
                //cout << "in top" << endl;

                // string dsName;
                // string varName;
                // s >> dsName;
                // s >> varName;
                // string varType = runningProgram[dsName]->getItemtype();
                if (varType == "integer")
                {
                    if (dsType == "Stack")
                    {
                        Stack<int> *vptr = static_cast<Stack<int> *>(runningProgram[dsName]);
                        Variable<int> *vptr2 = static_cast<Variable<int> *>(runningProgram[value]);
                        int value = vptr->Top();
                        vptr2->setValue(value);
                    }
                    if (dsType == "Queue" && commandType.compare("front") == 0 )
                    {
                        Queue<int> *vptr = static_cast<Queue<int> *>(runningProgram[dsName]);
                        Variable<int> *vptr2 = static_cast<Variable<int> *>(runningProgram[value]);
                        int value = vptr->Front();
                        vptr2->setValue(value);
                    }
                    if (dsType == "Queue" && commandType.compare("back") == 0 )
                    {
                        Queue<int> *vptr = static_cast<Queue<int> *>(runningProgram[dsName]);
                        Variable<int> *vptr2 = static_cast<Variable<int> *>(runningProgram[value]);
                        int value = vptr->Back();
                        vptr2->setValue(value);
                        
                    }
                }
                if (varType == "real")
                {
                    if (dsType == "Stack")
                    {
                        Stack<double> *vptr = static_cast<Stack<double> *>(runningProgram[dsName]);
                        Variable<double> *vptr2 = static_cast<Variable<double> *>(runningProgram[value]);
                        int value = vptr->Top();
                        vptr2->setValue(value);
                    }
                    if (dsType == "Queue" && commandType.compare("front") == 0 )
                    {
                        Queue<double> *vptr = static_cast<Queue<double> *>(runningProgram[dsName]);
                        Variable<double> *vptr2 = static_cast<Variable<double> *>(runningProgram[value]);
                        int value = vptr->Front();
                        vptr2->setValue(value);
                    }
                    if (dsType == "Queue" && commandType.compare("back") == 0 )
                    {
                        Queue<double> *vptr = static_cast<Queue<double> *>(runningProgram[dsName]);
                        Variable<double> *vptr2 = static_cast<Variable<double> *>(runningProgram[value]);
                        int value = vptr->Back();
                        vptr2->setValue(value);
                        
                    }
                }
            }

            else if (commandType.compare("isEmpty") == 0) // isEmpty <dsName> <bool var>
            {
                //cout << "in empty" << endl;

                // string dsName;
                // string varName;
                // s >> dsName;
                // s >> varName;
                // string varType = runningProgram[dsName]->getItemtype();
                if (varType == "integer")
                {
                    if (dsType == "Stack")
                    {
                        Stack<int> *vptr = static_cast<Stack<int> *>(runningProgram[dsName]);
                        Variable<bool> *vptr2 = static_cast<Variable<bool> *>(runningProgram[value]);
                        if (vptr->isEmpty())
                        {
                            vptr2->setValue(1);
                        }
                        else
                        {
                            vptr2->setValue(0);
                        }

                    }
                    if (dsType == "Queue")
                    {
                        Queue<int> *vptr = static_cast<Queue<int> *>(runningProgram[dsName]);
                        Variable<bool> *vptr2 = static_cast<Variable<bool> *>(runningProgram[value]);
                        if (vptr->isEmpty())
                        {
                            vptr2->setValue(1);
                        }
                        else
                        {
                            vptr2->setValue(0);
                        } 
                    }
                }
            }

            else if (commandType.compare("isFull") == 0) // WILL IMPLEMENT LATER isFull <dsName> <bool var>
            {

                if (varType == "integer")
                {
                    if (dsType == "Stack")
                    {
                        Stack<int> *vptr = static_cast<Stack<int> *>(runningProgram[dsName]);
                        Variable<bool> *vptr2 = static_cast<Variable<bool> *>(runningProgram[value]);
                        if (vptr->isFull())
                        {
                            vptr2->setValue(1);
                        }
                        else
                        {
                            vptr2->setValue(0);
                        }

                    }
                    if (dsType == "Queue")
                    {
                        Queue<int> *vptr = static_cast<Queue<int> *>(runningProgram[dsName]);
                        Variable<bool> *vptr2 = static_cast<Variable<bool> *>(runningProgram[value]);
                        if (vptr->isFull())
                        {
                            vptr2->setValue(1);
                        }
                        else
                        {
                            vptr2->setValue(0);
                        } 
                    }
                }

                if (varType == "real")
                {
                    if (dsType == "Stack")
                    {
                        Stack<double> *vptr = static_cast<Stack<double> *>(runningProgram[dsName]);
                        Variable<bool> *vptr2 = static_cast<Variable<bool> *>(runningProgram[value]);
                        if (vptr->isFull())
                        {
                            vptr2->setValue(1);
                        }
                        else
                        {
                            vptr2->setValue(0);
                        }

                    }
                    if (dsType == "Queue")
                    {
                        Queue<double> *vptr = static_cast<Queue<double> *>(runningProgram[dsName]);
                        Variable<bool> *vptr2 = static_cast<Variable<bool> *>(runningProgram[value]);
                        if (vptr->isFull())
                        {
                            vptr2->setValue(1);
                        }
                        else
                        {
                            vptr2->setValue(0);
                        } 
                    }
                }
            }

            else if (commandType.compare("clone") == 0) 
            {
                //cout << "in clone" << endl;

                if (varType == "integer")
                {
                    if (dsType == "Stack")
                    {
                        // string dsName;
                        // string dsNameCopy;
                        // s >> dsName;
                        // string varType = runningProgram[dsName]->getItemtype();
                        Stack<int> *from = static_cast<Stack<int> *>(runningProgram[dsName]);
                        Stack<int> *to = new Stack<int>(*from);
                        // s >> value;
                        runningProgram[value] = to;
                        

                    }
                    if (dsType == "Queue")
                    {
                        Queue<int> *from = static_cast<Queue<int> *>(runningProgram[dsName]);
                        Queue<int> *to = new Queue<int>(*from);
                        runningProgram[value] = to;

                    }
                }
                
                if (varType == "real")
                {
                    if (dsType == "Stack")
                    {
                        // string dsName;
                        // string dsNameCopy;
                        // s >> dsName;
                        // string varType = runningProgram[dsName]->getItemtype();
                        Stack<double> *from = static_cast<Stack<double> *>(runningProgram[dsName]);
                        Stack<double> *to = new Stack<double>(*from);
                        // s >> value;
                        runningProgram[value] = to;
                        

                    }
                    if (dsType == "Queue")
                    {
                        Queue<double> *from = static_cast<Queue<double> *>(runningProgram[dsName]);
                        Queue<double> *to = new Queue<double>(*from);
                        runningProgram[value] = to;

                    }
                }

            }

            else if (commandType.compare("delete") == 0)
            {
                //cout << "delete" << endl;
                map<string, DeclObject*>::iterator itr = runningProgram.find(dsName);
                delete itr->second;
                runningProgram.erase(itr);
                cout << "successful delete" << endl;
            }

            else if (commandType.compare("search") == 0)
            {
                //cout << "in search" << endl;

                // string dsName;
                // s >> dsName;
                // string value;
                // s >> value;
                if (value.find('.') != string::npos)
                { // if value is a real
                    if (dsType == "Stack")
                    {
                        if (static_cast<Stack<double> *>(runningProgram[dsName])->searchDS(stod(value)))
                        {
                            cout << "True" << endl;
                        }
                        else
                        {
                            cout << "False" << endl;
                        }
                        // static casting the runningProgram value which is declObject to
                    }
                    if (dsType == "Queue")
                    {
                        if (static_cast<Queue<double> *>(runningProgram[dsName])->searchDS(stod(value)))
                        {
                            cout << "True" << endl;
                        }
                        else
                        {
                            cout << "False" << endl;
                        }
                        // static casting the runningProgram value which is declObject to
                    }
                }
                else
                { // if value if an integer
                    // if (static_cast<Stack<int> *>(runningProgram[dsName])->searchDS(stod(value)))
                    // {
                    //     cout << "True" << endl;
                    // }
                    // else
                    // {
                    //     cout << "False" << endl;
                    // }
                    if (dsType == "Stack")
                    {
                        if (static_cast<Stack<int> *>(runningProgram[dsName])->searchDS(stod(value)))
                        {
                            cout << "True" << endl;
                        }
                        else
                        {
                            cout << "False" << endl;
                        }
                        // static casting the runningProgram value which is declObject to
                    }
                    if (dsType == "Queue")
                    {
                        if (static_cast<Queue<int> *>(runningProgram[dsName])->searchDS(stod(value)))
                        {
                            cout << "True" << endl;
                        }
                        else
                        {
                            cout << "False" << endl;
                        }
                        // static casting the runningProgram value which is declObject to
                    }
                }
            }
        }

        else if (commandType.compare("sort")==0) //sort sortingmethod ascdesc dsName
        {
            string sortingMethod;
            s >> sortingMethod;
            string choice;
            s >> choice;
            string dsName;
            s >> dsName;
            string varType = runningProgram[dsName]->getItemtype(); // GETTING THE VARIABLE TYPE OF THE DATA STRUCTURE
            string dsType = runningProgram[dsName]->getDsType();
            try
            { 
                if (sortingMethod == "bubble")
                {
                    if (varType == "integer")
                    {
                        if (dsType == "Stack")
                        {
                            static_cast<Stack<int> *>(runningProgram[dsName])->sortDS(choice);
                        }
                        if (dsType == "Queue")
                        {
                            static_cast<Queue<int> *>(runningProgram[dsName])->sortDS(choice);
                        }
                    }
                    if (varType == "real")
                    {
                        if (dsType == "Stack")
                        {
                            static_cast<Stack<double> *>(runningProgram[dsName])->sortDS(choice);
                        }
                        if (dsType == "Queue")
                        {
                            static_cast<Queue<double> *>(runningProgram[dsName])->sortDS(choice);
                        }

                    }
                }
                else
                    throw(sortingMethod);
            }
            catch (string sortingMethod)
            {
                cout << sortingMethod << " is not a valid method. Available methods are: bubble" << endl;
            }

        }

        else if (commandType.compare("if") == 0)
        {
            //cout << "in if" << endl;
            string var; //bool var
            s >> var;
            string message; // message should be 
            //s >> message;
            message += s.str();

            if (static_cast<Variable<bool>*>(runningProgram[var])->getValue() != 0 || static_cast<Variable<bool>*>(runningProgram[var])->getValue() == true)
            {
                cout << message.substr(message.find('#') + 1, message.find('#', message.find('#') + 1) - message.find('#') - 1) << endl;
                // message.substr(first letter after the first #, length of string(by taking the index of the last hash, minus the index of first hash, minus 1 to exclude the last hash symbol))
            }

        }


        else if (commandType.compare("!if") == 0)
        {
            //cout << "in if" << endl;
            string var; //bool var
            s >> var;
            string message; // message should be 
            //s >> message;
            message += s.str();

            if (static_cast<Variable<bool>*>(runningProgram[var])->getValue() != 1 || static_cast<Variable<bool>*>(runningProgram[var])->getValue() == false)
            {
                cout << message.substr(message.find('#') + 1, message.find('#', message.find('#') + 1) - message.find('#') - 1) << endl;
                // message.substr(first letter after the first #, length of string(by taking the index of the last hash, minus the index of first hash, minus 1 to exclude the last hash symbol))
            }

        }

        else if (commandType.compare("=") == 0 || commandType.compare("+") == 0 || commandType.compare("-") == 0 || commandType.compare("*") == 0 || commandType.compare("/") == 0 || commandType.compare("%") == 0 || commandType.compare("print") == 0) // need to distinguish between print ds v print variable
        {
            //cout << "in print" << endl;

            string var; // variable name /ds name
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
                if (commandType.compare("print") == 0) //make sure to do for all
                {
                    string dstype = runningProgram[var]->getDsType(); // ds or variable
                    if (dstype.compare("Stack") == 0)                 // if stack, then use the printDs inside the stack function to print
                    {
                        static_cast<Stack<int> *>(runningProgram[var])->printDS();
                    }
                    else if (dstype.compare("Queue") == 0)
                    {
                        static_cast<Queue<int> *>(runningProgram[var])->printDS();
                    }
                    else // else, printing a variable (Var integer x, = x 5, print x)
                    {
                        o.print_command(var);
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
                    string dstype = runningProgram[var]->getDsType(); // ds or variable
                    if (dstype.compare("Stack") == 0)                 // if stack, then use the printDs inside the stack function to print
                    {
                        static_cast<Stack<double> *>(runningProgram[var])->printDS();
                    }
                    else if (dstype.compare("Queue") == 0)
                    {
                        static_cast<Queue<double> *>(runningProgram[var])->printDS();
                    }
                    else // else, printing a variable (Var integer x, = x 5, print x)
                    {
                        o.print_command(var);
                    }
                }
            }
            if (varType == "bool")
            {
                operations<bool> o(runningProgram);
                if (commandType.compare("=") == 0)
                {
                    string value;
                    s >> value;
                    if (value == "0" || value == "false")
                        o.assg_commands(var, "false");
                    else
                        o.assg_commands(var, "true");
                }
                if (commandType.compare("print") == 0)
                {
                    o.print_command(var);
                }
            }
        }

        // Will implement later:
        //  if (commandType.compare("Delete") == 0)
        //  {
        //      string dsName;
        //      s >> dsName;
        //      runningProgram.erase(v.dsName == dsName);
        //  }
        //cout << "END" << endl;
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