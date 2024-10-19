#include <iostream>
using namespace std;

class HashTable {
private:
    int* table;           // Array for storing keys
    bool* isDeleted;      // Array to track deleted elements
    int size;             // no of numbers in table
    int capacity;         // max capacity of table
    float loadFactorThreshold = 0.8; //load factor as given in ques

    // defining hash function
    int hashFunction(int key) {
        return key % capacity;   //h(k) = k mod m
    }

    //function to check if number is prime
    //needed to resize table to prime number
    bool isPrime(int n) {
        if (n <= 1) return false;
        if (n == 2 || n == 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        for (int i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0)
                return false;
        }
        return true;
    }

    // function to find the next prime number greater to resize to that
    int nextPrime(int n) {
        while (!isPrime(n)) {
            n++;
        }
        return n;
    }

    // resizing and rehashing when load factor > 0.8
    void resizeAndRehash() {
        int oldCapacity = capacity;
        capacity *= 2;  // doubling the capacity
        capacity = nextPrime(capacity);
        int* oldTable = table;
        bool* oldIsDeleted = isDeleted;

        // creating new table and new deleted with new doubled capacity
        table = new int[capacity];
        isDeleted = new bool[capacity];

        // Initalizing new table with -1 (empty) and false for deleted marker
        for (int i = 0; i < capacity; i++) {
            table[i] = -1;
            isDeleted[i] = false;
        }

        size = 0;  // Reset size 0 as we will reinsert all the lements

        // Rehashing elements from old table into the new table
        for (int i = 0; i < oldCapacity; i++) {
            if (oldTable[i] != -1 && !oldIsDeleted[i]) {
                insert(oldTable[i]);  // Reinsert the element into the new table
            }
        }

        // deleting old table
        delete[] oldTable;
        delete[] oldIsDeleted;
    }

public:
    
    HashTable(int initialCapacity = 5) {
        capacity = initialCapacity;
        table = new int[capacity];
        isDeleted = new bool[capacity];

        // Initialize table slots as empty (-1) and nothing deleted for each mark (false)
        for (int i = 0; i < capacity; i++) {
            table[i] = -1;
            isDeleted[i] = false;
        }

        size = 0;  // No elements initially
    }



    // function to insert
    void insert(int key) {
        if (search(key) != -1) {  //if key already exists
            cout << "Duplicate key insertion is not allowed" << endl; //same key cant be inserted
            return;
        }

        // resizing if load factor exceeds threshold
        if ((float)size / capacity >= loadFactorThreshold) {  //if n/m greater than 0.8 resizing
            resizeAndRehash();
        }

        int index = hashFunction(key);
        int i = 0;

        // quadratic probing for handling the collisions in this hashing
        while (i < capacity) {
            int newIndex = (index + i * i) % capacity;
            if (table[newIndex] == -1 || isDeleted[newIndex]) {
                table[newIndex] = key;
                isDeleted[newIndex] = false;  // Reset deleted marker
                size++;
                return;
            }
            i++;
        }

        // If probing limit exceeded
        cout << "Max probing limit reached!" << endl;
    }

    // Search function will returns the index if found element or -1 if not found
    int search(int key) {
        int index = hashFunction(key);
        int i = 0;

        // search according to quadratic probing search
        while (i < capacity) {
            int newIndex = (index + i * i) % capacity;  //if it was deleted
            if (table[newIndex] == -1 && !isDeleted[newIndex]) {
                return -1;  // Key not found
            }
            if (table[newIndex] == key) {
                return newIndex;  // Key found at new indexed from resized rehashed table
            }
            i++;
        }

        return -1;  // Key not found after checking
    }

    // function to remove elements
    void remove(int key) {
        int index = search(key);  //using search funtion searching for key to be deleted
        if (index == -1) {
            cout << "Element not found" << endl;
            return;
        }

        table[index] = -1;
        isDeleted[index] = true;  // Mark the slot as deleted - needed in searching
        size--;
    }

    //  function to print table
    void printTable() {
        for (int i = 0; i < capacity; i++) {
            if (table[i] != -1 && !isDeleted[i]) {
                cout << table[i] << " ";  //if element exists print that
            } else {
                cout << "- ";  //otherwise print a - to show the space exists acc to sample output
            }
        }
        cout << endl;
    }
};
