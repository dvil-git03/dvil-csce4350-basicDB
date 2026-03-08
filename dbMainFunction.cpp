/*
    dbMainFunction.cpp by Diego Villela Morua
    -----------------------------------------
    The core logic to correctly run this simple database.

*/

#include "dbSetup.h"

/*

    Main function to begin running our database, we initialize our database object,
    Then we create a input stream and string stream to process our inputs for the
    user to interact with. We run until we get an EXIT line.

*/

int main()
{
    KeyValueStorage database;
    std::string line;

    // A input parser that takes in our STDIN and inputs it to our line string,
    // then using this in a stringstream to parse our inputs. This is done using
    // a while loop, and if our command variable matches an option, we call the
    // method in the database with the users arguments as the method's arguments.

    while (std::getline(std::cin, line))
    {
        if (line.empty())
            continue;

        std::stringstream ss(line);
        std::string command, key, value; // For example, if we set a key/value pair, we would use SET example pair.
        if (!(ss >> command))
            continue;

        if (command == "SET")
        {
            ss >> key >> value;
            if (!key.empty() && !value.empty()) // Ensuring that there is a key and a value in our input in the STDIN.
                database.setKeyValueDB(key, value);
        }
        else if (command == "GET")
        {
            ss >> key;
            if (!key.empty())
                database.getKeyValueDB(key);
        }
        else if (command == "EXIT") // EXIT means we leave the while loop, which terminates the program.
        {
            break;
        }
    }

    return 0;
}