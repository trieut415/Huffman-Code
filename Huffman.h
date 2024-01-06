#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <algorithm>
#include <unordered_map>
using namespace std;


//node class pair with a character and frequency value.
class Node {
public:
    char data;
    unsigned freq;
    Node *left, *right;

    Node(char data, unsigned freq);
};

//helper class to perform comparison between node*
class Compare {
public:
    bool operator()(Node* left, Node* right);
};


//Huffman class with private root and all functions
class Huffman {
private:
    Node* root; 

public:
	unordered_map<char, string> codes;

    Huffman(); // Constructor to initialize root as nullptr
    void printCodes();
    void buildHuffmanTree(char characters[], int freq[], int size);
    void makeHuffmanCodes(Node* root, string code, unordered_map<char, string>& codes);
    void decodeText(const char* inputFile);

};

#endif // HUFFMAN_H