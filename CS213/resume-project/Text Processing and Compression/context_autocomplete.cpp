#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>

// TrieNode structure to represent each node in the Trie
class TrieNode {
public:
    std::unordered_map<char, TrieNode*> children;
    bool isEndOfWord;

    TrieNode() : isEndOfWord(false) {}
};

// Trie class with insertion, searching, and autocomplete capabilities
class Trie {
private:
    TrieNode* root;

    // Helper function to collect all words with a given prefix
    void collectWords(TrieNode* node, std::string prefix, std::vector<std::string>& results) {
        if (node->isEndOfWord) {
            results.push_back(prefix);
        }
        for (auto& child : node->children) {
            collectWords(child.second, prefix + child.first, results);
        }
    }

public:
    Trie() {
        root = new TrieNode();
    }

    // Insert a word into the Trie
    void insert(const std::string& word) {
        TrieNode* current = root;
        for (char ch : word) {
            if (current->children.find(ch) == current->children.end()) {
                current->children[ch] = new TrieNode();
            }
            current = current->children[ch];
        }
        current->isEndOfWord = true;
    }

    // Return words in the Trie with the given prefix
    std::vector<std::string> autocomplete(const std::string& prefix) {
        TrieNode* current = root;
        std::vector<std::string> results;

        for (char ch : prefix) {
            if (current->children.find(ch) == current->children.end()) {
                return results;  // No words with the given prefix
            }
            current = current->children[ch];
        }
        collectWords(current, prefix, results);
        return results;
    }
};

// Function to compute the Longest Prefix Suffix (LPS) array for KMP algorithm
std::vector<int> computeLPSArray(const std::string& pattern) {
    int length = 0;
    int i = 1;
    std::vector<int> lps(pattern.length(), 0);

    while (i < pattern.length()) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                length = lps[length - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

// KMP search algorithm for finding a pattern in a given text
bool KMPSearch(const std::string& pattern, const std::string& text) {
    std::vector<int> lps = computeLPSArray(pattern);
    int i = 0, j = 0;  // i - index for text, j - index for pattern

    while (i < text.length()) {
        if (pattern[j] == text[i]) {
            j++;
            i++;
        }

        if (j == pattern.length()) {
            return true;  // Pattern found
        } else if (i < text.length() && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    return false;
}

// Class to implement the context-aware autocomplete with Trie and KMP
class ContextAwareAutocomplete {
private:
    Trie trie;                   // Trie for word storage
    std::string textHistory;     // Text history to track user inputs

public:
    // Insert a word into the Trie and text history
    void insertWord(const std::string& word) {
        trie.insert(word);
        textHistory += (textHistory.empty() ? "" : " ") + word;  // Add to history with space
    }

    // Get autocomplete suggestions based on the current prefix and context
    std::vector<std::string> getSuggestions(const std::string& prefix) {
        std::vector<std::string> words = trie.autocomplete(prefix);
        std::vector<std::string> relevantSuggestions;

        // Use KMP to filter words that are contextually relevant based on text history
        for (const std::string& word : words) {
            if (KMPSearch(word, textHistory)) {
                relevantSuggestions.push_back(word);
            }
        }

        // Sort by relevance (words in text history appear first)
        std::sort(relevantSuggestions.begin(), relevantSuggestions.end());
        return relevantSuggestions;
    }
};

// Main function to test the autocomplete program
int main() {
    ContextAwareAutocomplete autoComplete;

    // Insert sample words
    autoComplete.insertWord("hello");
    autoComplete.insertWord("help");
    autoComplete.insertWord("helicopter");
    autoComplete.insertWord("healthy");
    autoComplete.insertWord("heap");

    // Simulate user typing
    std::string userPrefix;
    std::cout << "Enter a prefix for autocomplete suggestions: ";
    std::cin >> userPrefix;

    // Get and display suggestions
    std::vector<std::string> suggestions = autoComplete.getSuggestions(userPrefix);
    std::cout << "Suggestions: ";
    for (const std::string& suggestion : suggestions) {
        std::cout << suggestion << " ";
    }

    return 0;
}
