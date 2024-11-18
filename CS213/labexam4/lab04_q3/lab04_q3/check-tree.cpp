#include "check-tree.h"

// UFDS Implementation from https://usaco.guide/gold/dsu?lang=cpp
class DisjointSets {
  private:
	vector<int> parents;
	vector<int> sizes;

  public:
	DisjointSets(int size) : parents(size), sizes(size, 1) {
		for (int i = 0; i < size; i++) { parents[i] = i; }
	}

	/** @return the "representative" node in x's component */
	int find(int x) { return parents[x] == x ? x : (parents[x] = find(parents[x])); }

	/** @return whether the merge changed connectivity */
	bool unite(int x, int y) {
		int x_root = find(x);
		int y_root = find(y);
		if (x_root == y_root) { return false; }

		if (sizes[x_root] < sizes[y_root]) { swap(x_root, y_root); }
		sizes[x_root] += sizes[y_root];
		parents[y_root] = x_root;
		return true;
	}

	/** @return whether x and y are in the same connected component */
	bool connected(int x, int y) { return find(x) == find(y); }
};


bool check_tree(unsigned n, vector<vector<int>> dist, vector<tuple<int, int, int>> &found_tree) {

    vector<pair<int, pair<int, int>>> edges;

    for(unsigned i = 0; i < n; i++){
        for(unsigned j = i + 1; j < n; j++){
            edges.push_back({dist[i][j], {i, j}});
        }
    }

    sort(edges.begin(), edges.end());

    int new_dist[n][n];
    for(unsigned i = 0; i < n; i++){
        for(unsigned j = 0; j < n; j++){
            new_dist[i][j] = 1e9;
        }
        new_dist[i][i] = 0;
    }

    DisjointSets ds(n);

    vector<tuple<int, int, int>> mst;

    // Kruskal's Algorithm
    for(auto &edge : edges){
        auto &[weight, nodes] = edge;
        auto &[u, v] = nodes;

        if(ds.unite(u, v)){
            if(weight) mst.push_back({u, v, weight});
            new_dist[u][v] = weight;
            new_dist[v][u] = weight;
        }
    }

    // Floyd-Warshall Algorithm. Any shortest path will work.
    for(unsigned k = 0; k < n; k++){
        for(unsigned i = 0; i < n; i++){
            for(unsigned j = 0; j < n; j++){
                new_dist[i][j] = min(new_dist[i][j], new_dist[i][k] + new_dist[k][j]);
            }
        }
    }

    // Check if the two matrices are equal
    for(unsigned i = 0; i < n; i++){
        for(unsigned j = 0; j < n; j++){
            if(new_dist[i][j] != dist[i][j]){
                return false;
            }
        }
    }

    if(mst.size() != n - 1) return false;

    found_tree = mst;

    return true;
}
