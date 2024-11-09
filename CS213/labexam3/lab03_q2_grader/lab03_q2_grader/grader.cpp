// DO NOT MODIFY THIS FILE
#include "huffman.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>

using namespace std;

// Function to print Huffman codes
void printCodes(Node* root, string str, unordered_map<string, string>& huffmanCodes) {
    if (!root) return;

    // If it's a leaf node
    if (root->left == nullptr && root->right == nullptr) {
        huffmanCodes[root->hexValue] = str;
    }

    printCodes(root->left, str + "0", huffmanCodes);
    printCodes(root->right, str + "1", huffmanCodes);
}

// Custom function to insert a node into a list (to simulate min-heap behavior)
void insertNode(vector<Node*>& heap, Node* node) {
    heap.push_back(node);
    int i = heap.size() - 1;

    // Sort the vector based on the frequency of nodes (like a min-heap)
    while (i > 0 && heap[i]->freq < heap[i - 1]->freq) {
        swap(heap[i], heap[i - 1]);
        i--;
    }
}

// Custom function to extract the minimum node from the list
Node* extractMin(vector<Node*>& heap) {
    Node* minNode = heap.front();
    heap.erase(heap.begin());
    return minNode;
}


// Function to read matrix from input file in hexadecimal format
vector<vector<string>> readMatrixFromFile(const string& filename, int& rows, int& cols) {
    ifstream file(filename);
    vector<vector<string>> matrix;

    if (file.is_open()) {
        matrix.resize(rows, vector<string>(cols));

        string line;
        for (int i = 0; i < rows && getline(file, line); ++i) {
            istringstream iss(line);
            string hexValue;
            for (int j = 0; j < cols && iss >> hexValue; ++j) {
                matrix[i][j] = hexValue;  // Store the hex string directly
            }
        }

        file.close();
    } else {
        cout << "Unable to open the file!" << endl;
    }

    return matrix;
}

Node* buildHuffmanTreeCorrectly(const unordered_map<string, int>& freq, unordered_map<string, string>& huffmanCodes) {
    vector<Node*> minHeap;
    for (auto pair : freq) {
        insertNode(minHeap, new Node(pair.first, pair.second));
    }
    while(minHeap.size() > 1) {
        Node* left = extractMin(minHeap);
        Node* right = extractMin(minHeap);
        Node* parent = new Node(left->freq + right->freq);
        parent->left = left;
        parent->right = right;
        insertNode(minHeap, parent);
    }
    printCodes(minHeap[0], "", huffmanCodes);
    return minHeap[0];
}

string compressImageCorrectly(const vector<vector<string>>& image, unordered_map<string, string>& huffmanCodes) {
    string compressedData = "";
    for (auto row : image) {
        for (const string& pixel : row) {
            compressedData += huffmanCodes[pixel];
        }
    }
    return compressedData;
}


bool isMatrixEqual(const vector<vector<string>>& image1, const vector<vector<string>>& image2, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (image1[i][j] != image2[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool doesCompressCorrectly(vector<vector<string>> &image, unordered_map<string, string> &correctHuffmanCodes){

    string expected = compressImageCorrectly(image, correctHuffmanCodes);
    string compressed = compressImage(image, correctHuffmanCodes);

    return expected == compressed;
}

pair<int, int> run_testcase(int ts){
    pair<int, int> marks = {0, 0};

    int rows = 28, cols = 28;

    // Read matrix
    vector<vector<string>> image = readMatrixFromFile("testcases/input/"+to_string(ts)+".txt", rows, cols);

    // Calculate frequency of each pixel
    unordered_map<string, int> freq;
    for (auto row : image) {
        for (const string& pixel : row) {
            freq[pixel]++;
        }
    }

    // Generate sample correct huffman codes and compressed image
    unordered_map<string, string> correctHuffmanCodes;
    Node* correctRoot = buildHuffmanTreeCorrectly(freq, correctHuffmanCodes);
    string correctCompressedData = compressImageCorrectly(image, correctHuffmanCodes);

    // Step 1: Is compression function correct? (1 Mark)

    try{
        string studentCompressedData = compressImage(image, correctHuffmanCodes);
        if(studentCompressedData == correctCompressedData){
            cout << "Compression Function Correct" << endl;
            marks.first += 1;
        }
        else throw -1;
    }
    catch(...){
        cout << "Compression Function Wrong" << endl;
    }

    // Step 2: Is decompression function correct? (3 Marks)

    try{
        vector<vector<string>> studentImage = decompressImage(correctCompressedData, correctRoot, rows, cols, correctHuffmanCodes);
        if(isMatrixEqual(studentImage, image, rows, cols)){
            cout << "Decompression Function Correct" << endl;
            marks.first += 3;
        }
        else throw -1;
    }
    catch(...){
        cout << "Decompression Function Wrong" << endl;
    }

    // Step 3: Is encoding correct? (4 Marks)

    try{
        unordered_map<string, string> studentHuffmanCodes;
        buildHuffmanTree(freq, studentHuffmanCodes);

        // Check if Huffman Codes Obey Prefix Properties

        for(auto &[key, val] : studentHuffmanCodes){
            for(int i = 1; key.substr(0,i) != key; i++){
                if(studentHuffmanCodes.find(key.substr(0,i)) != studentHuffmanCodes.end()) throw -1;
            }
        }

        // Check if they are efficient 
        string studentCompressedData = compressImageCorrectly(image, studentHuffmanCodes);

        if(studentCompressedData.length() != correctCompressedData.length()) throw -1;

        cout << "Build Huffman Function Correct" << endl;
        marks.first += 4;

    }
    catch(...){
        cout << "Build Huffman Function Wrong" << endl;
    }

    try{
        unordered_map<string, string> studentHuffmanCodes;
        Node* studentRoot = buildHuffmanTree(freq, studentHuffmanCodes);
        string studentCompressedData = compressImage(image, studentHuffmanCodes);
        vector<vector<string>> studentImage = decompressImage(studentCompressedData, studentRoot, rows, cols, studentHuffmanCodes);

        if(isMatrixEqual(studentImage, image, rows, cols)){
            cout << "Testcase Passed" << endl;
            marks.second += 1;
        }
        else throw -1;
    }
    catch(...){
        cout << "Testcase Failed" << endl;
    }

    return marks;
}

int main() {
    pair<int, int> marks;

    int num_of_testcases = 10;

    for (int ts = 0; ts < num_of_testcases ; ++ts) {
        cout << "Running Testcase " << ts << endl;

        auto [partial, full] = run_testcase(ts);
        cout << partial << " " << full << endl;
        marks.first += partial;
        marks.second += full;
       
        cout << "Testcase " << ts << " completed" << endl;
    }

    cout << "Partial: " << marks.first/num_of_testcases << "/8" << endl;
    cout << "Combined: " << marks.second/num_of_testcases << "/1" << endl;
    
    return 0;
}
