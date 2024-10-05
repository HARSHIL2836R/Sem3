#include<unordered_map>
#include<vector>
#include<iostream>
#include<utility>
#include<queue>
using namespace std;

// Implement a node struct if you feel 

// Implement the graph class
class Graph //undirected graph
{
public:
    int no_of_vertices;
    vector<vector<int>> adj_list; // Adjacency List
    Graph(int no_of_vertices, vector<pair<int,int> > edges){
        adj_list = vector(no_of_vertices, vector<int>());
        this->no_of_vertices = no_of_vertices;
        for (pair<int,int> edge : edges){
            this->adj_list[edge.first].emplace_back(edge.second);
            this->adj_list[edge.second].emplace_back(edge.first);
        }
    };
};


void bfs(Graph g, int source,unordered_map<int, int>& parent)
{
    queue<int> Q;
    vector<int> visited(g.no_of_vertices,0);
    visited[source] = 1;
    Q.push(source);
    while (not Q.empty()){
        int v = Q.front();Q.pop();
        for (int neighbor : g.adj_list[v]){
            if (visited[neighbor] == 0){
                visited[neighbor] = 1;
                Q.push(neighbor);
                parent[neighbor] = v;
            }
        }
    }
    parent[source] = -1;
};

