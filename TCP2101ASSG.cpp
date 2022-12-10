#include <iostream>
#include <vector>
#include <map>
#include <sstream>

// map --> {key:value, key:value, .....} collection of keys and values
// keys are unique, dsName are unique
using namespace std;

struct DeleteObject
{
    string dsName;
};

struct DeclObject // A struct to declare the syntax of our DSL command
{
    string varCommand;
    string dstype;
    string itemtype;
    string dsName;
    string value;
};

struct Variable
{
    string name;
    string value;
};

class Program
{
    vector<string> commands; //our DSL command
    // map<string, string> runningProgram;// string = DS name
    map<string, DeclObject> runningProgram; // string = DS name

public:
    Program()
    {
        string comm; 
        getline(cin, comm); //getting a command from the user
        while (comm.compare("#") != 0) //# = eoline
        {
            commands.push_back(comm); //pushing back the user's inputted command to the command vectpr
            getline(cin, comm); //A loop, asking user to input more until they input # (end of line)
        }
    }

    int countWords(string &str)
    {
        stringstream s(str); //breaks the user's command into individual words
        int counter = 0;
        string wrd; // to store individual words
        while (s >> wrd) //reads from the stringstream object
        {
            counter++; //for each word, increase the counter
        }
        return counter;
    }

    void parseCommands()
    {
        DeclObject obj;//declaring an object (so we can separate the users inputted commands)
        for (auto c : commands)//for each of the user's commands
        {
            stringstream s(c); //allows you to read a string as if it were a stream (like cin)

            int numOfWords = countWords(c); //count the number of words in a user's command
            if (numOfWords == 4) //manages 4 word declarations
            {
                s >> obj.varCommand; //stores the first word (command type) from the user's command to the object
                if (obj.varCommand.compare("Var") == 0) // need to differentiate between the 2 vars
                {
                    s >> obj.dstype; //stores the second word (the data structure type) from user's command to the object
                    s >> obj.itemtype; //stores the third word (the variable type) 
                    s >> obj.dsName;  //stores the fourth word (name given to the data structure)
                    runningProgram[obj.dsName] = obj; //add object to the runningProgram, key is dsName, therefore dsName should be unique
                    // cout << "item is added to the program (dynamic)" << endl;
                    // cout << runningProgram[obj.dsName].dsName << endl;
                }
            }
            else
            {
                // manage three words declaration
                s >> obj.varCommand;
                if (obj.varCommand.compare("Var") == 0) // need to differentiate between the 2 vars
                {
                    obj.dstype = "variable";
                    s >> obj.itemtype;
                    s >> obj.dsName;
                    runningProgram[obj.dsName] = obj;
                }
            }

            // obj.dstype = wrd;
            //  while(s>>wrd){
            //      runningProgram[wrd] =
            //      //cout << wrd << ":";
            //  }
            // cout << endl;
        }
    }

    void print()
    {
        for (auto c : commands)
        {
            cout << c << endl;
        }
    }

    void show()
    {
        cout << "Map contents :" << endl;
        for (auto m : runningProgram)
        {
            cout << runningProgram[m.first].dsName << "->";
            cout << runningProgram[m.first].dstype << "->";
            cout << runningProgram[m.first].itemtype << endl;
        }
    }
};

int main()
{
    Program p;
    p.print();
    p.parseCommands();
    p.show();
}

// template <typename T>
// class Var
// {
// private:
//     // T m_Array[];

// public:
//     int GetSize() const { return N; }
// };

// template <typename T>
// class Var
// {
// private:
//     T m_Variable;

// public:

// Var &operator=(const Var this, T wow){

//     }

// };

// class =
// {

// }

// int main()
// {
//     Var <int> array;
// }