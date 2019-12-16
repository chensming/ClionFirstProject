//
// Created by Dell on 2019/12/16.
//

#include <iostream>

using namespace std;

#include <fstream>

int main() {
    string str[100];
    ifstream infile("./FirstProject/Chenhongy/HuffmanTree/Files/a.txt",ios::in);
    ofstream outfile("./FirstProject/Chenhongy/HuffmanTree/Files/b.txt", ios::out);
    if (!infile) {
        cerr << "open error when read file" << endl;
        exit(1);
    }
    if (!outfile) {
        cerr << "open error when write file" << endl;
        exit(1);
    }
    cout << "read from a.txt to b.txt..." << endl;
    for (auto & i : str) {
        infile >> i;
        outfile << i << " ";
    }
    outfile.close();
    cout << "successfully" << endl;
//    system("pause");
}