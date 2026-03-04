#include "dbSetup.h"

int main() {
    HashIndex test;
    test.set("10", "Testing");
    test.set("Hello", "World!");

    cout << "Hello " << test.get("Hello") << endl;
    return 0;
}