#include "table.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    vector<string> genoma_lines;
    vector<string> genomas;

    ifstream input("input.txt");

    string line;
    while (getline(input, line)) {
        if (line.length() == 60) { 
            genoma_lines.push_back(line);
        } else {
            cout << "Linha descartada (não tem 60 caracteres): " << line << endl;
        }
    }
    input.close();

    for (string line : genoma_lines) {
        for (int j = 0; j < 10; j++) {
            string genome = line.substr(j * 6, 6);
            genomas.push_back(genome);
        }
    }

    table GENOME_TABLE;

    for (string s : genomas) {
        GENOME_TABLE.insert(s);
    }

    ofstream output("output.txt");

    GENOME_TABLE.print(output);
    output.close(); 

    cout << "Análise concluída. Resultado salvo em output.txt." << endl;

    return 0;
}
