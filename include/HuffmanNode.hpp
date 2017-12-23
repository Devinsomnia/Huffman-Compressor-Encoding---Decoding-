//
//  HuffmanNode.hpp
//  odevs
//
//  Created by Tuncay Cansız on 17.12.2017.
//  Copyright © 2017 Tuncay Cansız. All rights reserved.
//

#ifndef HuffmanNode_hpp
#define HuffmanNode_hpp

#include <iostream>
#include <string>
using namespace std;

class HuffmanNode {

    friend class HuffmanTree;
    friend class Compare;

private:
    char letter;
    int frequency;
    string code;
    HuffmanNode* left;
    HuffmanNode* right;

public:
    HuffmanNode();
    HuffmanNode(char, int);
    HuffmanNode(HuffmanNode*, HuffmanNode*);
    HuffmanNode(HuffmanNode* hn);
    ~HuffmanNode();

    int getFrequency();
    char getLetter();

};


class Compare {
    friend class HuffmanTree;
public:
    bool operator()(HuffmanNode * hn1, HuffmanNode * hn2)
    {
        if (hn1->getFrequency() > hn2->getFrequency()) {
            return true;
        }
        else {
            return false;
        }
    }
};

#endif /* HuffmanNode_hpp */
