/*

    dbSetup.h by Diego Villela Morua
    --------------------------------
    To create the definitions of classes, functions and included libraries.

*/

#ifndef DBSETUP_H
#define DBSETUP_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <optional>

// Constant definition for our hash index's vector size.
constexpr int SIZE = 1024;

// Unit of storage for each item in our database. Stores our key/value pair
// and a boolean value to check if a unit is empty or not.

struct Node
{
    std::string key;
    std::string val;
    bool occupied = false;
};

// Class for our Hash Table Index, we are creating our own hash table
// instead of using map(), the built in hash table function, we are
// creating one designed for this simple database.

class HashIndex
{
private:
    std::vector<Node> hashTable;
    int hashFunction(const std::string &key);

public:
    HashIndex();
    void setKeyValue(const std::string &key, const std::string &value);
    std::optional<std::string> getValueFromKey(const std::string &key);
};

// Class for our K/V pair storage system, using our previous hash table
// index to help index and store data. This will be responsible for file
// operations, such as saving our log and loading our log, and handling
// user requests.

class KeyValueStorage
{
private:
    HashIndex index;
    std::string db;
    void saveLogFile(const std::string &key, const std::string &val);
    void loadLogFile();

public:
    KeyValueStorage();
    void setKeyValueDB(const std::string &key, const std::string &val);
    void getKeyValueDB(const std::string &key);
};

#endif