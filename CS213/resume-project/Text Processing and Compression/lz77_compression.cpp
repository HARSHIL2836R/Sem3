#include <iostream>
#include <string>
#include <vector>

// Structure to store LZ77 encoding tuples
struct LZ77Tuple {
    int offset;  // Distance to the start of the match
    int length;  // Length of the match
    char nextChar;  // Next character in the look-ahead buffer

    LZ77Tuple(int off, int len, char next) : offset(off), length(len), nextChar(next) {}
};

// LZ77 Compression Class
class LZ77Compressor {
private:
    int windowSize;  // Size of the sliding window

public:
    LZ77Compressor(int winSize = 20) : windowSize(winSize) {}

    // Compress the input string using LZ77
    std::vector<LZ77Tuple> compress(const std::string& input) {
        std::vector<LZ77Tuple> encodedData;
        int inputSize = input.size();
        int currentIndex = 0;

        while (currentIndex < inputSize) {
            int matchLength = 0;
            int matchOffset = 0;

            // Define the boundaries of the sliding window and look-ahead buffer
            int searchStart = std::max(0, currentIndex - windowSize);

            // Search for the longest match in the sliding window
            for (int i = searchStart; i < currentIndex; ++i) {
                int length = 0;
                while (length < inputSize - currentIndex && input[i + length] == input[currentIndex + length]) {
                    ++length;
                }
                // Update the longest match
                if (length > matchLength) {
                    matchLength = length;
                    matchOffset = currentIndex - i;
                }
            }

            // Next character after the match
            char nextChar = currentIndex + matchLength < inputSize ? input[currentIndex + matchLength] : '\0';

            // Encode the tuple and advance the index
            encodedData.push_back(LZ77Tuple(matchOffset, matchLength, nextChar));
            currentIndex += matchLength + 1;
        }
        return encodedData;
    }

    // Decompress a sequence of LZ77 tuples
    std::string decompress(const std::vector<LZ77Tuple>& encodedData) {
        std::string decompressed;

        for (const LZ77Tuple& tuple : encodedData) {
            if (tuple.offset == 0 && tuple.length == 0) {
                // No match found, just add the next character
                decompressed += tuple.nextChar;
            } else {
                // Replicate the match from the decompressed string
                int start = decompressed.size() - tuple.offset;
                for (int i = 0; i < tuple.length; ++i) {
                    decompressed += decompressed[start + i];
                }
                // Append the next character
                if (tuple.nextChar != '\0') {
                    decompressed += tuple.nextChar;
                }
            }
        }
        return decompressed;
    }
};

// Helper function to print the encoded LZ77 tuples
void printEncodedData(const std::vector<LZ77Tuple>& encodedData) {
    std::cout << "Compressed Data (LZ77 Tuples):\n";
    for (const LZ77Tuple& tuple : encodedData) {
        std::cout << "(" << tuple.offset << ", " << tuple.length << ", '" << tuple.nextChar << "') ";
    }
    std::cout << "\n";
}

int main() {
    std::string inputText;
    std::cout << "Enter text to compress: ";
    std::getline(std::cin, inputText);

    // Create a LZ77Compressor object with a default window size
    LZ77Compressor compressor;
    
    // Compress the input text
    std::vector<LZ77Tuple> compressedData = compressor.compress(inputText);
    printEncodedData(compressedData);

    // Decompress the compressed data
    std::string decompressedText = compressor.decompress(compressedData);
    std::cout << "Decompressed Text: " << decompressedText << "\n";

    return 0;
}
