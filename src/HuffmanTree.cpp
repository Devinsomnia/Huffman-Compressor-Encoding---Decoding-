//
//  HuffmanTree.cpp
//  odevs
//
//  Created by Tuncay Cansız on 17.12.2017.
//  Copyright © 2017 Tuncay Cansız. All rights reserved.
//

#include "HuffmanTree.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <bitset>
#include <algorithm>
using namespace std;

HuffmanTree::HuffmanTree(string s) {
    message = s;
}

void HuffmanTree::buildTable()
{
    for (size_t i = 0; i < message.length(); i++) {
        char c = message.at(i);
        if (freqTable.find(message.at(i)) == freqTable.end()) {
            freqTable.insert(pair<char, int>(c, 1));
        }
        else {
            freqTable[c]++;
        }
    }
}

void HuffmanTree::buildHeap()
{
    for (freqItr = freqTable.begin(); freqItr != freqTable.end(); freqItr++) {
        heap.push(new HuffmanNode(freqItr->first, freqItr->second));
    }

    while (heap.size() != 1) {
        HuffmanNode* l = new HuffmanNode(heap.top());
        heap.pop();

        HuffmanNode* r = new HuffmanNode(heap.top());
        heap.pop();

        HuffmanNode* combo = new HuffmanNode(l, r);
        heap.push(combo);
    }

    root = heap.top();
    encodeHuffman(root, " ");
    heap.pop();
}

void HuffmanTree::encodeHuffman(HuffmanNode* root, string code)
{
    if (root->left == NULL) {
        root->code = code;
        huffTable.insert(pair<char, string>(root->getLetter(), code));
        return;
    }
    else {
        encodeHuffman(root->left, code + "0");
        encodeHuffman(root->right, code + "1");
    }
}

void HuffmanTree::writeEncodedString()
{
    for (size_t i = 0; i < message.length(); i++) {
        encodedMessage += huffTable[message.at(i)];
    }

    encodedMessage.erase(std::remove(encodedMessage.begin(), encodedMessage.end(), ' '), encodedMessage.end());
    cout << "\nencoded message: " << encodedMessage << "\n";

    ofstream o("bit.dat");
    o << encodedMessage;
    o.close();
}

void HuffmanTree::decodeHuffman()
{
    HuffmanNode* temp = root;

    string line;
    ifstream reader("bit.dat");
    if (reader.is_open()) {
        while (reader.good()) {
            getline(reader, line);
            encodedFile += line;
        }
    }

    for (size_t i = 0; i < encodedFile.length(); i++) {
        if (encodedFile[i] == '0') {
            temp = temp->left;
        }
        if (encodedFile[i] == '1') {
            temp = temp->right;
        }
        if (temp->left == nullptr && temp->right == nullptr)
        {
            decodedMessage += temp->letter;
            temp = root;
        }
    }
    cout << "\ndecoded message: " << decodedMessage << "\n";
}

void HuffmanTree::writeDecodedString()
{
    ofstream o("decodedBit.txt");
    o << decodedMessage;
    o.close();
}

void HuffmanTree::displayFreqTable()
{

    cout << "Frequency Table \n";
    ofstream frequencyTable;
    frequencyTable.open("frequencyTable.txt");
    frequencyTable << " Karakter" << "\t" << "Karakter Frekansı\n";
    for (freqItr = freqTable.begin(); freqItr != freqTable.end(); freqItr++) {
        frequencyTable <<"\t" <<freqItr->first << "\t\t\t\t" << freqItr->second << "\n";
    }
}

void HuffmanTree::displayHuffTable()
{
    // iterate through huffTable and output
  //  cout << "\n";
    cout << "Huffman Table \n";

    ofstream huffmanTable;
    huffmanTable.open ("huffmanTable.txt");
    huffmanTable << " Karakter" << "\t" << "Bit Karşılığı\n";

    for (huffItr = huffTable.begin(); huffItr != huffTable.end(); huffItr++) {
        huffmanTable <<"\t" <<huffItr->first << "\t\t\t" << huffItr->second << "\n";
    }
    huffmanTable.close();
    cout << "\n";
}

void HuffmanTree::compressEncodedString()
{
    for (size_t i = 0; i < encodedMessage.length(); i++) {
        if (bitMessage.size() == 8) {
            stringstream sstream(bitMessage);
            while (sstream.good())
            {
                bitset<8> bits;
                sstream >> bits;
                char c = char(bits.to_ulong());
                compressedMessage += c;
            }
            bitMessage = "";
        }
        bitMessage += encodedMessage[i];
    }

    if (bitMessage.size() != 8) {
        for (size_t i = 0; i < ((8 - bitMessage.size()) + 1); i++) {
            bitMessage += "0";
        }
    }

    stringstream sstream(bitMessage);
    while (sstream.good())
    {
        bitset<8> bits;
        sstream >> bits;
        char c = char(bits.to_ulong());
        compressedMessage += c;
    }

    bitMessage = "";

    compressedMessage.erase(std::remove(compressedMessage.begin(), compressedMessage.end(), NULL), compressedMessage.end());
    cout << "compressed message: " << compressedMessage << "\n\n";
    ofstream o("bitCompressed.dat");
    o << compressedMessage;
    o.close();
}

void HuffmanTree::decompress()
{

    string line;
    ifstream reader("bitCompressed.dat");
    if (reader.is_open()) {
        while (reader.good()) {
            getline(reader, line);
            compresedFile += line;
        }
    }

    for (size_t i = 0; i < compresedFile.length(); i++) {
        decompressedMessage += bitset<8>(compresedFile[i]).to_string();
    }

    decompressedMessage.erase(std::remove(decompressedMessage.begin(), decompressedMessage.end(), NULL), decompressedMessage.end());
    cout << "decompressed message: " << decompressedMessage << "\n\n";

    ofstream o("bitDecompressed.txt");
    o << decompressedMessage;
    o.close();
}



