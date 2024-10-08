#include <bits/stdc++.h>
using namespace std;
#include <vector>
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

class Solution {
public:
    vector<Node*> deep_copy(vector<Node*> vec){
        vector<Node*> result;
        for (Node* el: vec){
            Node* new_node = new Node(el->val);
            result.push_back(new_node);
        }
        return result;
    }
    struct vector_hash
    {
        template <class T1, class T2>
        std::size_t operator () (std::pair<T1, T2> const &v) const
        {
            return std::hash<T1>()(v.first);    
        }
    };
    Node* BFSpanning(Node* node){
        Node* result = new Node;
        result->val = node->val;
        result->neighbors = deep_copy(node->neighbors);
        queue<pair<Node*,Node*>> q;
        q.push(pair(node,result));
        unordered_set<pair<Node*,Node*>, vector_hash> visited;
        visited.insert(pair(node,result));
        while (not q.empty()){
            Node* v = q.front().first;Node* newv = q.front().second;q.pop();
            for (int i=0; i<v->neighbors.size();i++){
                if (not visited.contains(pair(v->neighbors[i],newv->neighbors[i]))){
                    visited.insert(pair(v->neighbors[i],newv->neighbors[i]));
                    newv->neighbors = deep_copy(v->neighbors);
                    q.push(pair(v->neighbors[i],newv));
                }
            }
        }
        return result;
    }
    Node* cloneGraph(Node* node) {
        if (node == nullptr) return nullptr;
        Node* new_first;
        new_first = BFSpanning(node);
        return new_first;
    }
};