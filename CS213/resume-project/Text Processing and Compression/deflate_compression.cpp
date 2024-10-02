#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <string>
#include <algorithm>

// ---------------------- LZ77 Compression Implementation ----------------------

// Structure to store LZ77 encoding tuples
struct LZ77Tuple {
    int offset;
    int length;
    char nextChar;

    LZ77Tuple(int off, int len, char next) : offset(off), length(len), nextChar(next) {}
};

// LZ77 Compression Class
class LZ77Compressor {
private:
    int windowSize;

public:
    LZ77Compressor(int winSize = 20) : windowSize(winSize) {}

    std::vector<LZ77Tuple> compress(const std::string& input) {
        std::vector<LZ77Tuple> encodedData;
        int inputSize = input.size();
        int currentIndex = 0;

        while (currentIndex < inputSize) {
            int matchLength = 0;
            int matchOffset = 0;

            int searchStart = std::max(0, currentIndex - windowSize);
            for (int i = searchStart; i < currentIndex; ++i) {
                int length = 0;
                while (length < inputSize - currentIndex && input[i + length] == input[currentIndex + length]) {
                    ++length;
                }
                if (length > matchLength) {
                    matchLength = length;
                    matchOffset = currentIndex - i;
                }
            }
            char nextChar = currentIndex + matchLength < inputSize ? input[currentIndex + matchLength] : '\0';
            encodedData.push_back(LZ77Tuple(matchOffset, matchLength, nextChar));
            currentIndex += matchLength + 1;
        }
        return encodedData;
    }
};

// ---------------------- Huffman Coding Implementation ----------------------

// Structure to represent a Huffman Tree Node
struct HuffmanNode {
    char character;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char ch, int freq) : character(ch), frequency(freq), left(nullptr), right(nullptr) {}
};

// Comparator for priority queue (min-heap)
struct Compare {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->frequency > b->frequency;
    }
};

// Class for Huffman Tree
class HuffmanTree {
private:
    HuffmanNode* root;
    std::unordered_map<char, std::string> huffmanCodes;

    // Helper function to build the Huffman codes from the tree
    void buildHuffmanCodes(HuffmanNode* node, std::string code) {
        if (!node) return;
        if (!node->left && !node->right) {
            huffmanCodes[node->character] = code;
        }
        buildHuffmanCodes(node->left, code + "0");
        buildHuffmanCodes(node->right, code + "1");
    }

public:
    // Build the Huffman Tree based on character frequencies
    void buildTree(const std::unordered_map<char, int>& frequencyTable) {
        std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, Compare> minHeap;
        for (auto& entry : frequencyTable) {
            minHeap.push(new HuffmanNode(entry.first, entry.second));
        }

        while (minHeap.size() > 1) {
            HuffmanNode* left = minHeap.top(); minHeap.pop();
            HuffmanNode* right = minHeap.top(); minHeap.pop();
            HuffmanNode* sumNode = new HuffmanNode('\0', left->frequency + right->frequency);
            sumNode->left = left;
            sumNode->right = right;
            minHeap.push(sumNode);
        }

        root = minHeap.top();
        buildHuffmanCodes(root, "");
    }

    // Get the Huffman code for a character
    std::string getHuffmanCode(char ch) {
        return huffmanCodes[ch];
    }

    // Return the complete Huffman codes map
    std::unordered_map<char, std::string> getCodes() {
        return huffmanCodes;
    }
};

// ---------------------- Deflate Compression Implementation ----------------------

// Class to combine LZ77 and Huffman Coding for Deflate Compression
class DeflateCompressor {
private:
    LZ77Compressor lz77;
    HuffmanTree huffman;

public:
    DeflateCompressor(int winSize = 20) : lz77(winSize) {}

    std::string compress(const std::string& input) {
        std::vector<LZ77Tuple> lz77Encoded = lz77.compress(input);

        // Create a frequency table for Huffman coding
        std::unordered_map<char, int> frequencyTable;
        for (const auto& tuple : lz77Encoded) {
            frequencyTable[tuple.nextChar]++;
        }

        // Build the Huffman Tree
        huffman.buildTree(frequencyTable);

        // Encode the LZ77 tuples using Huffman codes
        std::string compressed;
        for (const auto& tuple : lz77Encoded) {
            compressed += huffman.getHuffmanCode(tuple.nextChar);
        }

        return compressed;
    }
};

// ---------------------- Main Function to Test Compression ----------------------
int main() {
    std::string inputText;
    std::cout << "Enter text to compress: ";
    std::getline(std::cin, inputText);

    // Create Deflate Compressor object
    DeflateCompressor deflate;

    // Compress the input text
    std::string compressedData = deflate.compress(inputText);
    std::cout << "Compressed Data: " << compressedData << "\n";

    return 0;
}
