#include "useful-extra-edges.h"

/**
 * You can define any helper functions here. NO new "#include"s allowed.
 * 
 * Note that "n", "src", "dest", "Edges" and "ExtraEdges" are member variables of the Testcase class.
 * 
 * Print the minimum possible weight of a path from "src" to "dest",
 * provided you can add a maximum of 1 'extra' edge to the graph.
 * If "dest" can't reached from "src", print -1.
 * 
 * Do not print anything else.
 */

const long long int INF = 1e18;

void dijkstra(int src, std::vector<std::vector<std::pair<int, int>>> &adj_list, std::vector<long long int> &dist) {
    std::priority_queue<std::pair<long long int, int>,
                        std::vector<std::pair<long long int, int>>,
                        std::greater<std::pair<long long int, int>>> pq;
    pq.push({0, src});
    dist[src] = 0;
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        for (auto &v : adj_list[u]) {
            if (dist[v.first] > dist[u] + v.second) {
                dist[v.first] = dist[u] + v.second;
                pq.push({dist[v.first], v.first});
            }
        }
    }
}

void Testcase::getMinWeight() {
    // TODO: Complete this function

    // Create adjacency list
    std::vector<std::vector<std::pair<int, int>>> adj_list(n+1);
    for (auto &edge : Edges) {
        adj_list[edge[0]].push_back({edge[1], edge[2]});
        if(edge[0] != edge[1]) {
            adj_list[edge[1]].push_back({edge[0], edge[2]});
        }
    }

    // Dijkstra from src and dest
    std::vector<long long int> dist_src(n+1, INF);
    dijkstra(src, adj_list, dist_src);
    std::vector<long long int> dist_dest(n+1, INF);
    dijkstra(dest, adj_list, dist_dest);

    // Find minimum weight
    /*
    Case 1: No extra edges. So ans = simple dijkstra distance from src to dest
    Case 2: We take one extra edge. we will go through each edge one by one.
    Say the edge is from a to b with weight c then min weight path with this edge in consideration is
    min( (dist of a from src + dist of b from dest + c) , (dist of b from src + dist of a from dest + c) )
    We take minimum of what we get from case 1 and 2.
    */
    long long int min_weight = dist_src[dest]; // Case 1
    // Case 2
    for (auto &extra_edge : ExtraEdges) {
        long long int weight = dist_src[extra_edge[0]] + extra_edge[2] + dist_dest[extra_edge[1]];
        min_weight = std::min(min_weight, weight);
        weight = dist_src[extra_edge[1]] + extra_edge[2] + dist_dest[extra_edge[0]];
        min_weight = std::min(min_weight, weight);
    }

    if (min_weight == INF) {
        std::cout << -1 << std::endl;
    } else {
        std::cout << min_weight << std::endl;
    }
}