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
    bool is_prime(int n) {
        if (n <= 1) return false;
        if (n == 2 || n == 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        for (int i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }
        return true;
    }

    // Function to find the next prime number >= n
    int find_next_prime(int n) {
        while (!is_prime(n)) {
            n++;
        }
        return n;
    }

    // Function to rehash the existing keys when table size doubles
    void rehash() {
        int old_size = current_size;
        current_size = find_next_prime(2*current_size); // Double the size
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
        if (load_factor > max_load_factor) {
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
	if (num_elements == current_size)
	{
		cout << "Max probing limit reached!" << endl;
		return;
	}
	if (search(key) != -1)
	{
		cout << "Duplicate key insertion is not allowed" << endl;
		return;
	}
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
	cout << "Element not found" << endl;
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
