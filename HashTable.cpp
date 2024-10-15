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

    // resizing and rehashing when load factor > 0.8
    void resizeAndRehash() {
        int oldCapacity = capacity;
        capacity *= 2;  // doubling the capacity
        int* oldTable = table;
        bool* oldIsDeleted = isDeleted;

        // creating new table and deleted with new doubled capacity
        table = new int[capacity];
        isDeleted = new bool[capacity];
        
        // Initialize new table with -1 (empty) and false for deleted marker
        for (int i = 0; i < capacity; i++) {
            table[i] = -1;
            isDeleted[i] = false;
        }

        size = 0;  // Reset size since we're re-inserting all elements

        // Rehash all elements from old table into the new table
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
    // Constructor
    HashTable(int initialCapacity = 5) {
        capacity = initialCapacity;
        table = new int[capacity];
        isDeleted = new bool[capacity];
        
        // Initialize table slots as empty (-1) and no deleted markers (false)
        for (int i = 0; i < capacity; i++) {
            table[i] = -1;
            isDeleted[i] = false;
        }
        
        size = 0;  // No elements initially
    }

    

    // function to insert
    void insert(int key) {
        if (search(key) != -1) {  //if key already exists
            cout << "Duplicate key insertion is not allowed" << endl;
            return;
        }

        // resizing if load factor exceeds threshold
        if ((float)size / capacity >= loadFactorThreshold) {
            resizeAndRehash();
        }

        int index = hashFunction(key);
        int i = 0;

        // Quadratic probing for hashing
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

    // Search function: returns the index or -1 if not found
    int search(int key) {
        int index = hashFunction(key);
        int i = 0;

        // Quadratic probing search
        while (i < capacity) {
            int newIndex = (index + i * i) % capacity;
            if (table[newIndex] == -1 && !isDeleted[newIndex]) {
                return -1;  // Key not found
            }
            if (table[newIndex] == key) {
                return newIndex;  // Key found at newIndex
            }
            i++;
        }

        return -1;  // Key not found after full probing
    }

    // Remove function
    void remove(int key) {
        int index = search(key);
        if (index == -1) {
            cout << "Element not found" << endl;
            return;
        }

        table[index] = -1;
        isDeleted[index] = true;  // Mark the slot as deleted
        size--;
    }

    // Print table function
    void printTable() {
        for (int i = 0; i < capacity; i++) {
            if (table[i] != -1 && !isDeleted[i]) {
                cout << table[i] << " ";
            } else {
                cout << "- ";
            }
        }
        cout << endl;
    }
};

