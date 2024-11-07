#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;

// A tree node for Huffman Encoding
struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;
    
    Node(char character, int frequency) {
        ch = character;
        freq = frequency;
        left = right = nullptr;
    }
};

// Comparison object for min-heap (priority_queue)
struct compare {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq;
    }
};

// Function to print the Huffman codes for each character
void printHuffmanCodes(Node* root, string str, unordered_map<char, string> &huffmanCode) {
    if (!root)
        return;

    // Found a leaf node
    if (root->ch != '#')  // '#' is used to represent internal nodes
        huffmanCode[root->ch] = str;

    printHuffmanCodes(root->left, str + "0", huffmanCode);
    printHuffmanCodes(root->right, str + "1", huffmanCode);
}

// Function to generate Huffman encoding using a greedy strategy
void huffmanEncoding(string text) {
    unordered_map<char, int> freqMap;

    // Count frequency of each character
    for (char ch : text) {
        freqMap[ch]++;
    }

    // Create a priority queue (min-heap) to store live nodes of the Huffman tree
    priority_queue<Node*, vector<Node*>, compare> pq;

    // Create a leaf node for each character and add it to the priority queue
    for (auto pair : freqMap) {
        pq.push(new Node(pair.first, pair.second));
    }

    // Iterate until there is more than one node in the queue
    while (pq.size() != 1) {
        // Remove the two nodes with the highest priority (lowest frequency)
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        // Create a new internal node with a frequency equal to the sum of the two nodes' frequencies
        // '#' is a special character to denote an internal node
        Node* internalNode = new Node('#', left->freq + right->freq);
        internalNode->left = left;
        internalNode->right = right;

        // Add the new node to the priority queue
        pq.push(internalNode);
    }

    // The root node contains the entire Huffman tree
    Node* root = pq.top();

    // Traverse the Huffman tree and store the Huffman codes in a map
    unordered_map<char, string> huffmanCode;
    printHuffmanCodes(root, "", huffmanCode);

    // Print the Huffman codes for each character
    cout << "Huffman Codes:\n";
    for (auto pair : huffmanCode) {
        cout << pair.first << " : " << pair.second << endl;
    }

    // Print the encoded string
    cout << "\nEncoded string is:\n";
    for (char ch : text) {
        cout << huffmanCode[ch];
    }
    cout << endl;
}

int main() {
    string text;
    cout << "Enter the string to encode using Huffman Encoding: ";
    getline(cin, text);

    huffmanEncoding(text);

    return 0;
}
