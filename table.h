#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

const int TABLE_SIZE = 50000;

struct Node {
    string genoma;
    int quantity;
    Node* next;
    
    Node(string g = "", int q = 0, Node* n = nullptr);
};

class table {
    private:
        Node* arr[TABLE_SIZE];

    public:
        table();
        int hash(string s);
        void insert(string s);
        void print(ofstream &output);
};

#endif