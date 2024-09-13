#include "trie.h"
#include <iostream>

Trie::Trie()
{
	root = NULL;
}

// Returns new trie node (initialized to NULLs)
struct TrieNode* Trie::getNode(void)
{
	TrieNode* node = new TrieNode();
	for (int i = 0; i < ALPHABET_SIZE; i++)
	{
		node->children[i] = nullptr;
	}
	
	node->isWordEnd = 0;
	return node;
}

// If not present, inserts key into trie. If the
// key is prefix of trie node, just marks leaf node
void Trie::insert(struct TrieNode* root, const std::string key)
{
	TrieNode* node = root;
	if (node == nullptr) node = getNode(); root = node; 
	for (char i: key){
		if (node->children[CHAR_TO_INDEX(i)] == nullptr){
			node->children[CHAR_TO_INDEX(i)] = getNode();
		}
		node = node->children[CHAR_TO_INDEX(i)];
	}
	node->isWordEnd = 1;
}

bool Trie::search(struct TrieNode *root, std::string key)
{
	TrieNode* node = root;
	if (node == nullptr) root = getNode(); 
	for (char i: key){
		node = node->children[CHAR_TO_INDEX(i)];
		if (node == nullptr) return false;
	}
	if (node->isWordEnd) return true;
	else return false;
}

// Returns 0 if current node has a child
// If all children are NULL, return 1.
bool Trie::isLastNode(struct TrieNode* root)
{
	
}

// Recursive function to print auto-suggestions for given
// node.
void Trie::suggestionsRec(struct TrieNode* root,
					std::string currPrefix)
{
	// found a std::string in Trie with the given prefix
}

// print suggestions for given query prefix.
int Trie::printAutoSuggestions(TrieNode* root, const std::string query)
{
	
}
