#include <iostream>
#include <vector>
#include <map>
#include <sstream>

// map --> {key:value, key:value, .....} collection of keys and values
// keys are unique, dsName are unique
using namespace std;

struct DeclObject
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
    vector<string> commands;
    // map<string, string> runningProgram;// string = DS name
    map<string, DeclObject> runningProgram; // string = DS name

public:
    Program()
    {
        string comm;
        getline(cin, comm);
        while (comm.compare("#") != 0)
        { //# = eoline
            commands.push_back(comm);
            getline(cin, comm);
        }
    }

    int countWords(string &str)
    {
        stringstream s(str);
        int counter = 0;
        string wrd;
        while (s >> wrd)
        {
            counter++;
        }
        return counter;
    }

    void parseCommands()
    {
        DeclObject obj;
        for (auto c : commands)
        {
            stringstream s(c);

            int numOfWords = countWords(c);
            if (numOfWords == 4)
            {
                s >> obj.varCommand;
                if (obj.varCommand.compare("Var") == 0) // need to differentiate between the 2 vars
                {
                    s >> obj.dstype;
                    s >> obj.itemtype;
                    s >> obj.dsName;
                    runningProgram[obj.dsName] = obj;
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