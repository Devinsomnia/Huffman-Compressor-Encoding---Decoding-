//
//  HuffmanNode.cpp
//  odevs
//
//  Created by Tuncay Cansız on 17.12.2017.
//  Copyright © 2017 Tuncay Cansız. All rights reserved.
//

#include "HuffmanNode.hpp"
using namespace std;

HuffmanNode::HuffmanNode()
{
    letter = ' ';
    frequency = 0;
    left = NULL;
    right = NULL;
}

HuffmanNode::HuffmanNode(char c, int i)
{
    letter = c;
    frequency = i;
    left = NULL;
    right = NULL;
}

HuffmanNode::HuffmanNode(HuffmanNode * l, HuffmanNode * r)
{
    left = l;
    right = r;
    frequency = left->getFrequency() + right->getFrequency();
    letter = ' ';
}

HuffmanNode::HuffmanNode(HuffmanNode * hn)
{
    if (hn->left != nullptr) {
        left = hn->left;
    }

    if (hn->right != nullptr) {
        right = hn->right;
    }

    letter = hn->letter;
    frequency = hn->frequency;

}

HuffmanNode::~HuffmanNode()
{
    if (left != NULL) delete left;
    if (right != NULL) delete right;
}

int HuffmanNode::getFrequency()
{
    return frequency;
}

char HuffmanNode::getLetter()
{
    return letter;
}
