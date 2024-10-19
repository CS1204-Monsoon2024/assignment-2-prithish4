#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class HashTable {
private:
    vector<int> table;
    int current_size;
    int num_elements;
    float max_load_factor = 0.8;
    int empty = -1;
    int deleted = -2;

    // Hash function h(x) = x % m
    int hash(int key) {
        return key % current_size;
    }

    // Function to rehash the existing keys when table size doubles
    void rehash() {
        int old_size = current_size;
        current_size *= 2; // Double the size
        vector<int> old_table = table;
        table.assign(current_size, empty); // New table with the doubled size
        num_elements = 0; // Reset element count, as we are going to re-hash

        for (int key : old_table) {
            if (key != empty && key != deleted) {
                insert(key); 
            }
        }
    }

    // check the load factor
    void check_load_factor() {
        float load_factor = (float)num_elements / current_size;
        if (load_factor >= max_load_factor) {
            rehash();
        }
    }

public:
    HashTable(int size = 11) {
        num_elements = 0;
        current_size = size;
        table.assign(current_size, empty);
    }

    // Insert operation
    void insert(int key) {
        check_load_factor(); // Check if rehashing is needed based on load factor

        int index = hash(key);
        int i = 0;

        // Quadratic probing to resolve collision
        while (table[(index + i * i) % current_size] != empty && table[(index + i * i) % current_size] != deleted) {
            i++;
        }
        table[(index + i * i) % current_size] = key;
        num_elements++;
    }

    // Search operation
    int search(int key) {
        int index = hash(key);
        int i = 0;

        // Quadratic probing to search
        while (table[(index + i * i) % current_size] != empty) {
            if (table[(index + i * i) % current_size] == key) {
                return (index+i*i); // Key found
            }
            i++;
        }
        return -1; // Key not found
    }

    // Delete operation
    void remove(int key) {
        int index = hash(key);
        int i = 0;

        // Quadratic probing to find the key
        while (table[(index + i * i) % current_size] != empty) {
            if (table[(index + i * i) % current_size] == key) {
                table[(index + i * i) % current_size] = deleted; // Mark as deleted
                num_elements--;
                return;
            }
            i++;
        }
    }

    // Function to print the current hash table
    void printTable() {
        for (int i = 0; i < current_size; ++i) {
            if (table[i] == empty) {
                cout << "- ";
            } else if (table[i] == deleted) {
                cout << "- ";
            } else {
                cout << table[i] << " ";
            }
        }
        cout << "\n";
    }
};
