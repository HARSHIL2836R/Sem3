#include "huffman.h"

// Build Huffman Tree and generate codes
Node* buildHuffmanTree(const unordered_map<string, int>& freq, unordered_map<string, string>& huffmanCodes) {
    vector<Node*> minHeap;

    // Create leaf nodes for each pixel value with a frequency
    for (auto pair : freq) {
        insertNode(minHeap, new Node(pair.first, pair.second));
    }

    // Build the Huffman Tree
    while (minHeap.size() != 1) {
        Node* left = extractMin(minHeap);
        Node* right = extractMin(minHeap);

        int sum = left->freq + right->freq;
        Node* newNode = new Node("", sum);  // Internal node with no pixel value
        newNode->left = left;
        newNode->right = right;

        insertNode(minHeap, newNode);
    }

    // Generate Huffman codes from the tree
    printCodes(minHeap[0], "", huffmanCodes);

    // Return the root of the tree
    return minHeap[0];
}

// Compress the image using the Huffman codes
string compressImage(const vector<vector<string>>& image, unordered_map<string, string>& huffmanCodes) {
    string compressedData = "";
    for (auto row : image) {
        for (const string& pixel : row) {
            compressedData += huffmanCodes[pixel];
        }
    }
    return compressedData;
}

// Decompress the data using the Huffman Tree
vector<vector<string>> decompressImage(const string& compressedData, Node* root, int rows, int cols, unordered_map<string,string> huffmanCodes) {
    vector<vector<string>> reconstructedImage(rows, vector<string>(cols, ""));
    Node* currentNode = root;
    int idx = 0;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            while (currentNode->left || currentNode->right) {
                if (compressedData[idx++] == '0') {
                    currentNode = currentNode->left;
                } else {
                    currentNode = currentNode->right;
                }
            }
            reconstructedImage[i][j] = currentNode->hexValue;
            currentNode = root;
        }
    }
    return reconstructedImage;
}
