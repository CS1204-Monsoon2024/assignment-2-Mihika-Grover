#include <iostream>
using namespace std;

class HashTable {
private:
    int* table;           // array to store the keys
    bool* isDeleted;      // array check for deleted elements
    int size;             // no of numbers in table
    int capacity;         // max capacity of table
    float loadFactorThreshold = 0.8; //load factor as given in ques

    // defining hash function
    int hashFunction(int key) {
        return key % capacity;   //h(k) = k mod m
    }
    //function to check if a number is prime
    //needed to resize table to prime
    bool isPrime(int n) {
        int count = 0;
        else{
            // checking for no of divisors of that number
            for (int i = 1; i <= n; i++) {

            //if n is divisible by i then count of divisor = +1
            if (n % i == 0)
                count++;
        }
            if (count>2)
                return true;
            else
                return false;
        }
        return true;
    }

    // function to find the next prime number greater to resize to that
    int nextPrime(int n) {
        while (!isPrime(n)) {  //if the given is not prime
            n++;        //increment till you get a prime number
        }
        return n;
    }
    
    // resizing and rehashing when load factor > 0.8
    void resizeAndRehash() {
        int oldCapacity = capacity;
        capacity *= 2;  // doubling the capacity
        capacity = nextPrime(capacity);  //if new capacity not prime, will take the next largest prime
        int* oldTable = table;
        bool* oldIsDeleted = isDeleted;

        // creating new table and deleted with new doubled capacity
        table = new int[capacity];
        isDeleted = new bool[capacity];
        
        // Initialize new table with -1 (empty) and false for deleted marker as new table
        for (int i = 0; i < capacity; i++) {
            table[i] = -1;
            isDeleted[i] = false;
        }

        size = 0;  // reset size 0 as we will reinsert elements

        // rehashing elements from old table to new table
        for (int i = 0; i < oldCapacity; i++) {
            if (oldTable[i] != -1 && !oldIsDeleted[i]) {  //if was not deleted from old table
                insert(oldTable[i]);  // Reinsert the element into the new table
            }
        }

        

public:
    
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
        if (search(key) != -1) {  //check if key already exists
            cout << "Duplicate key insertion is not allowed" << endl; //same key cant be inserted
            return;
        }

        // resizing if load factor exceeds threshold
        if ((float)size / capacity >= loadFactorThreshold) { //if n/m greater than 0.8 resizing
            resizeAndRehash();
        }

        int index = hashFunction(key);  //index finding by hash function 
        int i = 0;

        // quadratic probing for handling the collisions in this hashing
        while (i < capacity) {
            int newIndex = (index + i * i) % capacity;  //h(x) = (h(x) + i^2) mod m
            if (table[newIndex] == -1 || isDeleted[newIndex]) {  //if it was deleted previously
                table[newIndex] = key;
                isDeleted[newIndex] = false;  // reset deleted marker
                size++;
                return;
            }
            i++;
        }

        // if probing limit exceeded 
        cout << "Max probing limit reached" << endl;
    }

    // search function returns the index if found or -1 if not found
    int search(int key) {
        int index = hashFunction(key);
        int i = 0;

        //  search according to quadratic probing
        while (i < capacity) {
            int newIndex = (index + i * i) % capacity;
            if (table[newIndex] == -1 && !isDeleted[newIndex]) {  //if it was deleted
                return -1;  // Key not found
            }
            if (table[newIndex] == key) {
                return newIndex;  // Key found at ne indexed from resized rehashed table
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
        isDeleted[index] = true;  // mark the slot as deleted - needed in searching
        size--;  //decrement size when deleted
    }

    // function to print table
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
