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
    const int empty = -1;
    const int deleted = -2;

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
            cout << "Load factor exceeded 0.8, rehashing...\n";
            rehash();
        }
    }

public:
    HashTable(int size = 11) : current_size(size), num_elements(0) {
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
    bool search(int key) {
        int index = hash(key);
        int i = 0;

        // Quadratic probing to search
        while (table[(index + i * i) % current_size] != empty) {
            if (table[(index + i * i) % current_size] == key) {
                return true; // Key found
            }
            i++;
        }
        return false; // Key not found
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
        cout << "Key " << key << " not found in the table.\n";
    }

    // Function to print the current hash table
    void printTable() {
        cout << "Hash Table: \n";
        for (int i = 0; i < current_size; ++i) {
            if (table[i] == empty) {
                cout << i << ": empty\n";
            } else if (table[i] == deleted) {
                cout << i << ": deleted\n";
            } else {
                cout << i << ": " << table[i] << "\n";
            }
        }
        cout << "\n";
    }
};
