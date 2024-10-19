#include <iostream>
using namespace std;

class HashTable {
private:
    int* table;           // Array for storing keys
    bool* isDeleted;      // Array to track deleted elements
    int size;             // no of numbers in table
    int capacity;         // max capacity of table
    const float loadFactorThreshold = 0.8; //load factor as given in ques

    // defining hash function
    int hashFunction(int key) {
        return key % capacity;   //h(k) = k mod m
    }
    // Helper function to check if a number is prime
    /*
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

    // Helper function to find the next prime number greater than or equal to n
    int nextPrime(int n) {
        while (!isPrime(n)) {
            n++;
        }
        return n;
    }
    */
    // resizing and rehashing when load factor > 0.8
    void resizeAndRehash() {
        int oldCapacity = capacity;
        capacity *= 2;  // doubling the capacity
        //capacity = nextPrime(capacity);
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




int main() {
    int initialSize = 7; 
    HashTable ht(initialSize);

    // Example test case
    ht.insert(1);
    ht.printTable();
    ht.insert(6);
    ht.printTable();
    ht.insert(15);
    ht.printTable(); 
    ht.insert(25);
    ht.printTable();
    ht.remove(15);
    ht.printTable();
    ht.insert(29);  
    ht.printTable(); 
    
    ht.insert(35);  
    ht.printTable();
    ht.insert(42);  
    ht.printTable();
    ht.insert(11);  
    ht.printTable();
    ht.insert(2);  
    ht.printTable();

    int find = ht.search(22);
    std::cout << "Found at:" << find << std::endl;

    return 0;
}

