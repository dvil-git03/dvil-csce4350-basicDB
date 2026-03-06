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

using std::vector, std::string;

// Unit of storage for each item in our database. Stores our key/value pair
// and a boolean value to check if a unit is empty or not.

struct Node
{
    string key;
    string val;
    bool occupied = false;
};

// Class for our Hash Table Index, we are creating our own hash table
// instead of using map(), the built in hash table function, we are
// creating one designed for this simple database.

class HashIndex
{
private:
    static const int SIZE = 1024; // Probably okay for this project, but not in a real database software.
    vector<Node> hashTable;
    int hashFunction(const string &key);

public:
    HashIndex();
    bool setKeyValue(string key, string value);
    string getValue(string key);
};

// Class for our K/V pair storage system, using our previous hash table
// index to help index and store data. This will be responsible for file
// operations, such as saving our log and loading our log, and handling
// user requests.

class KeyValueStorage
{
private:
    HashIndex index;
    string db;
    void saveLog(string key, string val);
    void loadLogFile();

public:
    KeyValueStorage();
    void setKeyVal(string key, string val);
    void getKeyVal(string key);
};

#endif