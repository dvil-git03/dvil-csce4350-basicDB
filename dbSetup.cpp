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

int HashIndex::hashFunction(const string &key) {
    int hash = 0;

    for (char c : key) {
        hash = (hash * 31) + c; 
    }
    return hash % SIZE;
}

HashIndex::HashIndex() : hashTable(SIZE) {}

bool HashIndex::set(string key, string value) {
    int index = hashFunction(key);
    int startIndex = index;

    do {
        if (hashTable[index].occupied == false) {
            hashTable[index].key = key;
            hashTable[index].val = value;
            hashTable[index].occupied = true;
            return true;
        }
        else if (hashTable[index].key == key) {
            cout << "ERROR: Pair has already been inserted." << endl;
            return false;
        }
        else {
            cout << "ERROR: Unknown error, Pair has not been inserted." << endl;
            return false;
        }
        index = (index + 1) % SIZE;
    } while (index != startIndex);
    return false;
}

string HashIndex::get(string key) {
    int index = hashFunction(key);
    int startIndex = index;

    do {
        if (hashTable[index].occupied == false) break;
        if (hashTable[index].key == key) return hashTable[index].val;

        index = (index + 1) % SIZE;
    } while (index != startIndex);
    return "ERROR: Key not found.";
}

