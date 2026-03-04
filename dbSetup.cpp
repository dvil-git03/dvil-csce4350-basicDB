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

// Constructor intializes the vector with our previously defined
// size in our header file.

HashIndex::HashIndex() : hashTable(SIZE) {}

// Set method that takes in a key and value to insert into our
// hash table index, so we can create a K/V pair in our database.

bool HashIndex::set(string key, string value) {
    int index = hashFunction(key);
    int startIndex = index;

    // We have a do-while loop that checks if the key is occupied or
    // the key we are giving this method will be overwritten, then we
    // set the Node struct in the table with the key and value, and 
    // mark the space as occupied.
    do {
        if (hashTable[index].occupied == false || hashTable[index].key == key) {
            hashTable[index].key = key;
            hashTable[index].val = value;
            hashTable[index].occupied = true;
            return true;
        }
        index = (index + 1) % SIZE; // Linear probing through the table, until we find an empty space if needed.
    } while (index != startIndex);
    return false;
}

// Method to retrieve a value from a key, takes in a key and does a
// similar method to the previous get method, but instead returns the
// value, in this case a string.

string HashIndex::get(string key) {
    int index = hashFunction(key);
    int startIndex = index;

    do {
        if (hashTable[index].occupied == false) break; // If the space is not occupied, we stop instantly and return an error.
        if (hashTable[index].key == key) return hashTable[index].val;

        index = (index + 1) % SIZE;
    } while (index != startIndex); // Linear probing through the table, until we find an empty space if needed.
    return "ERROR: Key not found.";
}


/*

    Key / Value Pair Storage System, for our database.
    This will use our previous index to store information
    into our database here, the index will allow us to search quickly,
    and this class will handle our requests to our index.

*/

KeyValueStorage::KeyValueStorage() {
    db = "data.db";
    loadLogFile();
}