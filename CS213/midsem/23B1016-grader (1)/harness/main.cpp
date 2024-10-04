#include "bst.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include "rdtsc.h"


// DONOT CHANGE ANYTHING IN THIS FILE

using namespace std;


Node::Node(int val) : data(val), left(nullptr), right(nullptr) {}

Node* insert(Node* root, int val) {
    if (root == nullptr) {
        return new Node(val);
    }
    if (val < root->data) {
        root->left = insert(root->left, val);
    }
    else if (val > root->data) {
        root->right = insert(root->right, val);
    }
    return root;
}

Node* createBST(const std::vector<int>& nums) {
    Node* root = nullptr;
    for (int num : nums) {
        root = insert(root, num);
    }
    return root;
}


// This function prints the HEAP using ASCII characters using the
// format:
//
//   root
//       |-- left child
//       \-- right child
//
// where the left and right heaps are printed recursively in
// the same format.
//
// You may use this for debugging purposes.
//
void printBST_rec( Node *node, std::string &prefix, bool isLeft)
{
    if (node != nullptr)
    {
        std::cout << prefix;

        std::cout << (isLeft ? "|-- " : "\\-- ");
        std::cout << node->data << std::endl;

        std::string childPrefix = prefix + (isLeft ? "|   " : "    ");

        printBST_rec(node->left, childPrefix, true);
        printBST_rec(node->right, childPrefix, false);
    }
}

void printBST(Node* root)
{
  string prefix = "";
  printBST_rec( root, prefix, true);
}


int main(int argc, char **argv) {
  std::string testcases_path = "testcases";
  std::string output_file = "output.txt";
  // std::string testcases_path = "tmp";
  if (argc > 2){
    testcases_path = argv[1];
    output_file = argv[2];
  }

    ifstream bstFile(testcases_path+"/input_tree.txt");
    ifstream kFile(testcases_path+"/input_k.txt");

    if (!bstFile.is_open() || !kFile.is_open()) {
        cerr << "Unable to open input files" << endl;
        return 1;
    }

    string bstLine, kLine;
    vector<string> results;

    // Read and process each line from both files
    while (getline(bstFile, bstLine) && getline(kFile, kLine)) {
        vector<int> bstValues;
        int kSmall, kLarge;

        // Parse BST values from the line
        istringstream bstStream(bstLine);
        int value;
        while (bstStream >> value) {
            bstValues.push_back(value);
        }

        // Parse k values from the line
        istringstream kStream(kLine);
        kStream >> kSmall >> kLarge;

        // Create BST from the read values
        Node* root = createBST(bstValues);
        // cout << "New tree"<<"\n";
        // printBST(root);
        
        int kthSmallest = 0;
        int kthLargest = 0;
        ClockCounter c;
        int bound = std::max(1,100000/kSmall);
        for (int i = 0; i < bound; i++ ) {
          // Find the k-th smallest and largest elements
          int kSmallTemp = kSmall;
          kthSmallest = findKthSmallest(root, kSmallTemp);
        }
        auto t = c.stop();
        cout << t/(kSmall*bound);

        int kLargeTemp = kLarge;
        kthLargest = findKthLargest(root, kLargeTemp);

        // Store the result for this test case
        results.push_back(to_string(kthSmallest) + '\n' + to_string(kthLargest));
    }

    // Write all results to a single output file
    ofstream outputFile(output_file);
    if (outputFile.is_open()) {
        for (const string& result : results) {
            outputFile << result << endl;
        }
        outputFile.close();
    }
    else {
      cerr << "Unable to open " << output_file << endl;
        return 1;
    }

    bstFile.close();
    kFile.close();

    // Compare the output with the expected output
    ifstream expectedOutputFile(testcases_path+"/expected_output.txt");
    ifstream actualOutputFile(output_file);

    if (!expectedOutputFile.is_open() || !actualOutputFile.is_open()) {
        cerr << "Error opening expected or actual output file." << endl;
        return 1;
    }

    string expectedLine, actualLine;
    bool differenceFound = false;

    while (getline(expectedOutputFile, expectedLine) && getline(actualOutputFile, actualLine)) {
        if (expectedLine != actualLine) {
            differenceFound = true;
            cout << "Difference found:" << endl;
            cout << "Expected: " << expectedLine << endl;
            cout << "Actual: " << actualLine << endl;
        }
    }

    // if (!differenceFound) {
    //     cout << "No differences found. Output matches the expected output." << endl;
    // }

    // Close expected and actual output files
    expectedOutputFile.close();
    actualOutputFile.close();

    return 0;
}
