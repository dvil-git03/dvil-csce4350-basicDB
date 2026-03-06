/*
    dbMainFunction.cpp by Diego Villela Morua
    -----------------------------------------
    The core logic to correctly run this simple database.

*/

#include "dbSetup.h"

/*

    Main function to begin running our database, we initialze our database object,
    Then we create a input stream and string stream to process our inputs for the
    user to interact with. We run until we get an EXIT line.

*/

int main()
{
    KeyValueStorage database;
    std::string line;

    std::cout << "Simple Databse for Key / Value Pairs" << std::endl;
    std::cout << "Please enter SET [key] [value], GET [key] or EXIT." << std::endl;

    // A input parser that takes in our STDIN and inputs it to our line string,
    // then using this in a stringstream to parse our inputs.

    while (std::getline(std::cin, line))
    {
        if (line.empty())
            continue;
        if (line == "EXIT" || line == "exit")
            break; // We exit the loop, thus closing the program.

        std::stringstream ss(line);
        std::string command, key, value; // For example, if we set a key/value pair, we would use SET example pair.
        ss >> command;

        if (command == "SET" || command == "set")
        {
            ss >> key >> value;
            if (!key.empty() && !value.empty()) // Ensuring that there is a key and a value in our input in the STDIN.
                database.setKeyVal(key, value);
            else
                std::cerr << "ERROR" << std::endl;
        }
        else if (command == "GET" || command == "get")
        {
            ss >> key;
            if (!key.empty()) // Same situation as previously, we are insuring our value is an input.
                database.getKeyVal(key);
            else
                std::cerr << "ERROR" << std::endl;
        }
    }

    return 0;
}