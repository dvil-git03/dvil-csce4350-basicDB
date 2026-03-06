/*
    dbMainFunction.cpp by Diego Villela Morua
    -----------------------------------------
    The core logic to correctly run this simple database.

*/

#include "dbSetup.h"

using std::cout, std::endl, std::cin, std::getline, std::stringstream, std::cerr;

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

    // A input parser that takes in our STDIN and inputs it to our line string,
    // then using this in a stringstream to parse our inputs.

    while (getline(cin, line))
    {
        if (line.empty())
            continue;
        if (line == "EXIT" || line == "exit")
            break; // We exit the loop, thus closing the program.

        stringstream ss(line);
        string command, key, value; // For example, if we set a key/value pair, we would use SET example pair.
        ss >> command;

        if (command == "SET" || command == "set")
        {
            ss >> key >> value;
            if (!key.empty() && !value.empty()) // Ensuring that there is a key and a value in our input in the STDIN.
                database.setKeyVal(key, value);
            else
                cerr << "ERROR" << endl;
        }
        else if (command == "GET" || command == "get")
        {
            ss >> key;
            if (!key.empty()) // Same situation as previously, we are insuring our value is an input.
                database.getKeyVal(key);
            else
                cerr << "ERROR" << endl;
        }
    }

    return 0;
}