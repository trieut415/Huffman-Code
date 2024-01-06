#include "Huffman.h"

//Node Constructor
Node::Node(char data, unsigned freq) {
    left = right = nullptr;
    this->data = data;
    this->freq = freq;
}

//custom operator to handle node comparison
bool Compare::operator()(Node* left, Node* right) {
    return (left->freq > right->freq);
}

//Huffman Constructor init 
Huffman::Huffman() {
    root = nullptr; 
}

//helper function to create huffman codes by recursively concatenating 1/0 depending on traversal
void Huffman::makeHuffmanCodes(Node* root, string code, unordered_map<char, string>& codes) {
    if (root == nullptr) {
        return;
    }

    if (!root->right && !root->left) { //keep traversing until reached leaf node
        codes[root->data] = code;
    }
    makeHuffmanCodes(root->left, code + "0", codes); //call with left child and new code
    makeHuffmanCodes(root->right, code + "1", codes); //call with right child and new code
}

//sorts and prints codes in digit order, from smallest to greatest, ensures correct printing and order
void Huffman::printCodes() {
    vector<pair<char, string>> sorted; //make a vector pair with the code and its corresponding key/value


    for (const auto& pair : codes) {
        sorted.push_back(make_pair(pair.first, pair.second));
    }
    sort(sorted.begin(), sorted.end(), [](const pair<char, string>& a, const pair<char, string>& b) {
        return a.second.length() < b.second.length();
    });
    for (const auto& pair : sorted) {
        cout << pair.first << " " << pair.second << '\n';
    }
    cout << endl;
}


//Builds a huffman tree using a minHeap priority queue, want to assign left/right pointers then push them out of the queue, keep parent
void Huffman::buildHuffmanTree(char characters[], int freq[], int size) {
    Node *left, *right, *top;
    priority_queue<Node*, vector<Node*>, Compare> minHeap;

    for (int i = 0; i < size; ++i) {
        minHeap.push(new Node(characters[i], freq[i]));
    }

    while (minHeap.size() != 1) {
        left = minHeap.top();
        minHeap.pop();

        right = minHeap.top();
        minHeap.pop();

        top = new Node('$', left->freq + right->freq);

        top->left = left;
        top->right = right;

        minHeap.push(top);
    }
    root = minHeap.top();                       // assign root to top of minHeap
    makeHuffmanCodes(root, "",codes);           //call print to assign codes to class member in huffman
}

//decode a text file via tree traversal using the unordered map "codes"
void Huffman::decodeText(const char* inputFile) {
    ifstream inFile(inputFile);
    if (!inFile.is_open()) {
        cout << "Unable to open file" << endl;
        return;
    }

    string encodedNum, line;
    while (getline(inFile, line)) {
        encodedNum += line;
    }
    inFile.close();

    Node* current = root;
    for (char num : encodedNum) {
        if (num == '0') {
            current = current->left;
        } else if (num == '1') {
            current = current->right;
        }
        if (current->left == nullptr && current->right == nullptr) { //reached leaf
            cout << current->data;
            current = root;
        }
    }
}