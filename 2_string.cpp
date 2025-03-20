#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

// Hash table class using separate chaining
class HashTable {
private:
    vector<list<string>> table;  // Vector of lists (buckets)

    // Hash function to map a string to an index
    int hashFunction(const string& word) {
        int hash = 0;
        int i =0;
        int n = word.size();
        for (char c : word) {
            hash = hash + int(c)*(pow(10,n-i-1));
            i++;
        }
        cout<<hash<<endl;
        return hash%10;
    }

public:
    // Constructor to initialize the table with a fixed size
    HashTable(int size) {
        table.resize(size);
    }

    // Insert a word into the hash table
    void insert(const string& word) {
        int index = hashFunction(word);
        table[index].push_back(word);  // Add word to the corresponding list
    }

    // Search for a word in the hash table
    bool search(const string& word) {
        int index = hashFunction(word);
        for (const string& w : table[index]) {
            if (w == word) {
                return true;  // Word found
            }
        }
        return false;  // Word not found
    }

    // Display the hash table
    void display() {
        for (int i = 0; i < table.size(); ++i) {
            cout << "Bucket " << i << ": ";
            for (const string& word : table[i]) {
                cout << word << " -> ";
            }
            cout << "NULL" << endl;
        }
    }
};

int main() {
    HashTable hashTable(10);  // Create hash table with 10 buckets

    string menu ="Enter your choice: \n1. Add\n2. Display\n3. Exit";
    int opt;
    string key;
    do
    {
        cout<<menu<<endl;
        cout<<"Your choice: ";
        cin>>opt;
        switch (opt)
        {
            case 1:
                cout<<"\nEnter the element: ";
                cin>>key;
                hashTable.insert(key);
                break;
            case 2:
                hashTable.display();
                break;
            case 3:
                exit(0);
            default:
                cout<<"\n Please enter a correct option"<< endl;
                break;
        }
    } while (true);
    return 0;
}