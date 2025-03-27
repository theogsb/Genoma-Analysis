#include "table.h"
#include <iostream>

using namespace std;

Node::Node(string g, int q, Node* n) : genoma(g), quantity(q), next(n) {}

table::table() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        arr[i] = nullptr;
    }
}

// fold hash (mais simples porem com muitas colisões principalmente anagramas) ----------------------------------------------------------------------------
// int table::hash(string s)
// {
//     int hash = 0;
//     int key = 31;

//     for (char c : s) {
//         hash = hash * key + c;
//     }

//     return abs(hash) % TABLE_SIZE;
// }

// FNV-1a hash (pesquisei como a melhor escolha em casos de pequenas strings) ----------------------------------------------------
int table::hash(string s) 
{
    const int primo = 16777619;
    int hash = 2166136261;

    for ( char c : s ) {
        hash = (hash ^ c) * primo;
    }

    return abs(hash) % TABLE_SIZE;
}

// sfold hash (boa implementação no caso atual e eu lembrava) --------------------------------------------------------------------
// int table::hash(string s) {
//     long long hash = 0;
//     int len = s.length();

//     for (int i = 0; i < len; i++) {
//         hash ^= (hash << 5) + (hash >> 2) + s[i];
//     }

//     return hash % TABLE_SIZE;
// }

void table::insert(string s)
{
    int index = hash(s);

    Node* temp = arr[index];
    while (temp != nullptr) {
        if (temp->genoma == s){
            temp->quantity++;

            // Abre o arquivo "colisoes.txt" para registrar a colisão
            ofstream collisionFile("colisoes.txt", ios::app);
            if (!collisionFile) {
                cerr << "Não foi possível abrir o arquivo colisoes.txt" << endl;
                return;
            }

            // Escreve a colisão no arquivo
            collisionFile << "Colisão detectada para o genoma: " << s << endl;
            collisionFile.close();

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
