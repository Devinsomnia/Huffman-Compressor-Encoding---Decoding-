//
//  main.cpp
//  odevs
//
//  Created by Tuncay Cansız on 17.12.2017.
//  Copyright © 2017 Tuncay Cansız. All rights reserved.
//

#include "HuffmanTree.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdlib.h>
using namespace std;

int main() {
    int menu;
    // ifstream f("test.txt");
    // getline(f, line);

    char * buffer;
    int fsize = 0;
    ifstream f("test.txt", ios_base::binary);
    f.seekg(0, ios::end);
    fsize = f.tellg();
    f.seekg(0, ios::beg);
    buffer = new char [fsize];
    f.read(buffer,fsize);

    //cout << fsize << endl;
    //cout << buffer << endl;

    f.close();


    HuffmanTree* ht = new HuffmanTree(buffer);

    ht->buildTable();
    ht->buildHeap();


    do {
       // system("clear");
        cout << "1) Compress File"<<endl;
        cout << "2) Decompress File write to Screen"<<endl;
        cout << "3) Quit "<< endl;
        cout << "> ";
        cin >> menu;

        switch (menu) {
            case 1:
                ht->writeEncodedString();
                ht->writeDecodedString();
                ht->compressEncodedString();
                break;
            case 2:
                ht->decodeHuffman();
                ht->decompress();
                break;
            case 3:
                exit(0);
                return 0;
                break;
            default: NULL;
                break;
        }

    } while (menu != 3);

    delete ht;
}
