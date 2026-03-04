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

using std::vector, std::string, std::cout, std::endl;

struct Node {
    string key;
    string val;
    bool occupied = false;
};

class HashIndex {
    private:
        static const int SIZE = 1024; // Probably okay for this project, but not in a real database software.
        vector<Node> hashTable;
        int hashFunction(const string &key);
    public:
        HashIndex();
        bool set(string key, string value);
        string get(string key);
};



#endif