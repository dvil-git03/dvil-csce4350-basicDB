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

    for (int i = 0; key.length(); i++) {
        hash = (hash * 31) + key[i]; 
    }
    return hash % SIZE;
}

HashIndex::HashIndex() {
    //hashTable(SIZE);
}

bool HashIndex::set(string key, string value) {

}