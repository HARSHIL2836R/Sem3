#include "huffman.h"

// Build Huffman Tree and generate codes
Node* buildHuffmanTree(const unordered_map<string, int>& freq, unordered_map<string, string>& huffmanCodes) {
    vector<Node*> minHeap;

    // Create leaf nodes for each pixel value with a frequency
    for (auto pair : freq) {
        insertNode(minHeap, new Node(pair.first, pair.second));
    }

    // Build the Huffman Tree

    //***********************//
    while(! (minHeap.size() == 1)){
        Node* A = extractMin(minHeap);
        Node* B = extractMin(minHeap);

        Node* new_node = new Node(A->freq + B->freq);
        new_node->left = A;
        new_node->right = B;
        insertNode(minHeap, new_node);
    }
    //***********************//


    // DO NOT EDIT LINES BELOW

    // Generate Huffman codes from the tree and prints them
    printCodes(minHeap[0], "", huffmanCodes);

    // Return the root of the tree
    return minHeap[0];
}

// Compress the image using the Huffman codes
string compressImage(const vector<vector<string>>& image, unordered_map<string, string>& huffmanCodes) {
    string compressedData = "";

    //***********************//
    for (int j = 0; j<image[0].size();j++){
        for (int i = 0; i<image.size();i++){
            compressedData.append(huffmanCodes[image[j][i]]);
        }
    }
    //***********************//

    return compressedData;
}

// Decompress the data using the Huffman Tree
vector<vector<string>> decompressImage(const string& compressedData, Node* root, int rows, int cols, unordered_map<string, string> huffmanCodes) {
    vector<vector<string>> reconstructedImage(rows, vector<string>(cols, ""));

    //***********************//
    int i=0;int j=0;
    // std::cout<<"SIZE"<<reconstructedImage.size()<<std::endl;
    Node* curr = root;
    for (auto c: compressedData){
        if (c == '1') curr = curr->right;
        else if (c=='0') curr = curr->left;
        if (curr->hexValue != ""){
            if (j == cols) {i++;j=0;}
            // std::cout<<i<<" "<<j<<std::endl;
            reconstructedImage[i][j] = curr->hexValue;
            curr = root;
            j++;
        }
    }
    //***********************//

    return reconstructedImage;
}
