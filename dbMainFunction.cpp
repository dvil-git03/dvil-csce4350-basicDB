/*
    dbMainFunction.cpp by Diego Villela Morua
    -----------------------------------------
    The core logic to correctly run this simple database.

*/

#include "dbSetup.h"

using std::cout, std::endl, std::cin, std::getline, std::stringstream;

/*

    Main function to begin running our database, we initialze our database object,
    Then we create a input stream and string stream to process our inputs for the
    user to interact with. We run until we get an EXIT line.

*/

int main()
{
    KeyValueStorage database;
    string line;

    cout << "Simple Databse for Key / Value Pairs" << "\n";
    cout << "Please enter SET [key] [value], GET [key] or EXIT." << endl;
    while (getline(cin, line))
    {
        if (line == "EXIT" || line == "exit")
            break; // We exit the loop, thus closing the program.

        stringstream ss(line);
        string command, key, value;
        ss >> command;

        if (command == "SET" || command == "set")
        {
            ss >> key >> value;
            if (!key.empty() && !value.empty())
                database.setKeyVal(key, value);
        }
        else if (command == "GET" || command == "get")
        {
            ss >> key;
            if (!key.empty())
                database.getKeyVal(key);
        }
    }

    return 0;
}