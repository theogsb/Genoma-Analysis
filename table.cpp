#include "table.h"
#include <iostream>

using namespace std;

Node::Node(string g, int q, Node* n) : genoma(g), quantity(q), next(n) {}

table::table() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        arr[i] = nullptr;
    }
}

int table::hash(string s) {
    const int primo = 16777619;
    int hash = 2166136261;

    for (char c : s) {
        hash = (hash ^ c) * primo;
    }

    return abs(hash) % TABLE_SIZE;
}

void table::insert(string s) {
    int index = hash(s);

    Node* temp = arr[index];
    while (temp != nullptr) {
        if (temp->genoma == s) {
            temp->quantity++;
            return;
        }
        temp = temp->next;
    }

    Node* newNode = new Node(s, 1);
    newNode->next = arr[index];
    arr[index] = newNode;
}

void table::print(ofstream &output) {
    output << "   GENOMA  " << " QUANTIDADE" << endl;
    output << "-------------------------------" << endl;
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* temp = arr[i];
        while (temp != nullptr) {
            output << "   " << temp->genoma << "       " << temp->quantity << '\n';
            temp = temp->next;
        }
    }
}