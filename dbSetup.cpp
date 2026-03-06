/*

    dbSetup.cpp by Diego Villela Morua
    ----------------------------------
    Includes the proper logic for the methods defined in the
    previous header file, dbSetup.h.

*/

#include "dbSetup.h"


// Iterate through the string provided, without modifying it,
// for our simple hash function which takes the hash value and
// multiplies by 31, a prime number and adds the ASCII value of
// the char in the string.

int HashIndex::hashFunction(const std::string &key)
{
    unsigned int hash = 0; // We use an unsigned int to prevent our hash function from generating a negative value which causes undefined behavior.

    for (char c : key)
    {
        hash = (hash * 31) + c;
    }
    return hash % SIZE;
}

// Constructor intializes the vector with our previously defined
// size in our header file.

HashIndex::HashIndex() : hashTable(SIZE) {}

// Set method that takes in a key and value to insert into our
// hash table index, so we can create a K/V pair in our database.

void HashIndex::setKeyValue(std::string key, std::string value)
{
    int index = hashFunction(key);
    int startIndex = index;

    // We have a do-while loop that checks if the key is occupied or
    // the key we are giving this method will be overwritten, then we
    // set the Node struct in the table with the key and value, and
    // mark the space as occupied.
    do
    {
        if (hashTable[index].occupied == false || hashTable[index].key == key)
        {
            hashTable[index].key = key;
            hashTable[index].val = value;
            hashTable[index].occupied = true;
            return;
        }
        index = (index + 1) % SIZE; // Linear probing through the table, until we find an empty space if needed.
    } while (index != startIndex);
    return;
}

// Method to retrieve a value from a key, takes in a key and does a
// similar method to the previous get method, but instead returns the
// value, in this case a string.

std::string HashIndex::getValue(std::string key)
{
    int index = hashFunction(key);
    int startIndex = index;

    do
    {
        if (hashTable[index].occupied == false)
            break; // If the space is not occupied, we stop instantly and return an error.
        if (hashTable[index].key == key)
            return hashTable[index].val;

        index = (index + 1) % SIZE;
    } while (index != startIndex); // Linear probing through the table, until we find an empty space if needed.
    return "NOT FOUND";
}

/*

    Key / Value Pair Storage System, for our database.
    This will use our previous index to store information
    into our database here, the index will allow us to search quickly,
    and this class will handle our requests to our index.

*/

// Constructor that sets the filename for the database,
// then loads the file, if it fails, we exit.

KeyValueStorage::KeyValueStorage()
{
    db = "data.db";
    loadLogFile();
}

// We load the file from disk, if we fail for any reason, we
// exit the program. The filestream inputs each key, value pair
// into memory exactly as previously loaded.

void KeyValueStorage::loadLogFile()
{
    std::ifstream fileLoad(db);
    if (!fileLoad.is_open())
        return;

    std::string key, value;

    while (fileLoad >> key >> value)
    {
        index.setKeyValue(key, value);
    }
}

// We save the file to disk, using our previously named db string,
// ensure we can open / create this file, then saving them in this
// way:

// KEY [SPACE] VALUE[NEWLINE]...

void KeyValueStorage::saveLog(std::string key, std::string val)
{
    std::ofstream saveFile(db, std::ios::app); // We use ios::app, as to set our I/O operations as append mode, as we don't want to overwrite data.
    if (saveFile.fail())
        return;
    else if (saveFile.is_open())
    {
        saveFile << key << " " << val << "\n"; // We use \n instead of endl, as endl flushes the cache and can be slow.
    }
    saveFile.flush(); // We flush to disk to ensure our changes are saved.
}

// To save our Key Values, we save to disk, then
// save our changes to memory. In case we have an
// error, we will still have our changes on disk.

void KeyValueStorage::setKeyVal(std::string key, std::string val)
{
    saveLog(key, val);
    index.setKeyValue(key, val);
    std::cout << "OK" << std::endl;
}

// Simple function to print out our result.
// If our key is empty, we print out a fail result.

void KeyValueStorage::getKeyVal(std::string key)
{
    std::cout << index.getValue(key) << std::endl;
}