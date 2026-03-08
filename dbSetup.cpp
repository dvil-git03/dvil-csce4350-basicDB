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
    unsigned int hash = 0; // We use an unsigned int to prevent our hash function from generating a negative value which may cause undefined behavior.

    for (char c : key)
    {
        hash = (hash * 31) + static_cast<unsigned char>(c); // We also convert our character into an unsigned character to prevent negative values which may cause undefined behavior.
    }
    return hash % SIZE; // Previously, we defined SIZE as 1024.
}

// Constructor initializes the vector with our previously defined
// size in our header file. This was done using define as

HashIndex::HashIndex() : hashTable(SIZE) {}

// Set method that takes in a key and value to insert into our
// hash table index, so we can create a K/V pair in our database.

void HashIndex::setKeyValue(const std::string &key, const std::string &val)
{
    int index = hashFunction(key);
    int visited = 0;

    while (visited < SIZE)
    {
        if (hashTable[index].occupied == false || hashTable[index].key == key) // If we find an empty spot OR we wish to overwrite an entry, we insert our data into the table.
        {
            hashTable[index].key = key;
            hashTable[index].val = val;
            hashTable[index].occupied = true;
            return;
        }
        index = (index + 1) % SIZE; // Linear probing through the table, until we find an empty space, this is only if a hash function makes a match.
        visited++;
    }
    return;
}

// Method to retrieve a value from a key, takes in a key and does a
// similar method to the previous get method, but instead returns the
// value, in this case a string.

std::optional<std::string> HashIndex::getValueFromKey(const std::string &key)
{
    int index = hashFunction(key);
    int visited = 0;

    while (visited < SIZE)
    {
        if (hashTable[index].occupied && hashTable[index].key == key)
            return hashTable[index].val;
        index = (index + 1) % SIZE; // Linear probing through the table, until we find an empty space, this is only if a hash function makes a match.
        visited++;
    }
    return std::nullopt; // We return a nullopt, which means that our search did not result in a value being found from a key.
}

/*

    Key / Value Pair Storage System for our database.
    This will use our previous index to store information
    into our database here, the index will allow us to search quickly,
    and this class will handle our requests to our index.

*/

// Constructor that sets the filename for the database,
// then loads the file, if it fails, we exit.

KeyValueStorage::KeyValueStorage()
{
    db = "data.db";
    std::ofstream touch(db, std::ios::app); // We run this to create our file and immediately close.
    touch.close();

    loadLogFile();
}

// We load the file from disk, if we fail for any reason, we
// exit the program. The filestream inputs each key, value pair
// into memory exactly as previously loaded.

void KeyValueStorage::loadLogFile()
{
    std::ifstream fileLoad(db);
    if (!fileLoad.is_open())
    {
        std::cerr << "ERROR: Unable to load file." << std::endl;
        exit(1);
    }
    std::string line;

    // We use a getline function to load our file, and a stringstream to parse our inputs,
    // we ensure we also do not have empty inputs, then run our setKeyValue method to
    // save our values into memory.

    while (std::getline(fileLoad, line))
    {
        if (line.empty())
            continue;

        std::stringstream ss(line);
        std::string key, value;

        ss >> key >> value;

        if (!key.empty() && !value.empty())
            index.setKeyValue(key, value);
    }

    fileLoad.close();
    return;
}

// We save the file to disk, using our previously named db string,
// ensure we can open / create this file, then saving them in this
// way:

// KEY [SPACE] VALUE[NEWLINE]...

void KeyValueStorage::saveLogFile(const std::string &key, const std::string &val)
{
    std::ofstream saveFile(db, std::ios::app); // We use ios::app, as to set our I/O operations as append mode, as we don't want to overwrite data.
    if (saveFile.fail())
    {
        std::cerr << "ERROR: Failed to save database." << std::endl;
        exit(1);
    }
    else if (saveFile.is_open())
    {
        saveFile << key << " " << val << std::endl;
    }
    saveFile.flush(); // We flush to disk to ensure our changes are saved.
    saveFile.close();
    return;
}

// To save our Key Values, we save to disk, then
// save our changes to memory. In case we have an
// error, we will still have our changes on disk.

void KeyValueStorage::setKeyValueDB(const std::string &key, const std::string &val)
{
    saveLogFile(key, val);
    index.setKeyValue(key, val);
    return;
}

// Simple function to print out our result.
// If our key is empty, we print out a fail result.

void KeyValueStorage::getKeyValueDB(const std::string &key)
{
    std::optional<std::string> result = index.getValueFromKey(key);
    if (result)
    {
        std::cout << *result << std::endl;
    }
    return;
}