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

void Dijkstra(std::vector<std::vector<int>> &Edges,std::vector<int> &sp,int n, int src){
    std::set<std::pair<int,int>,std::less<std::pair<int,int>>> rbt;
    std::vector<std::vector<std::pair<int,int>>> adj(n+1);
    for (auto& edge: Edges){
        adj[edge[0]].push_back({edge[1],edge[2]}); // {edge,wight}
        adj[edge[1]].push_back({edge[0],edge[2]});
    }
    sp[src] = 0;
    std::vector<bool> visited(n+2,false);
    for (int i = 1; i<n+1;i++){
        rbt.insert({sp[i],i});
    }
    while(!rbt.empty()){
        int v = (*rbt.begin()).second;
        rbt.erase(rbt.begin());
        for (auto& [w,k]: adj[v]){
            // std::cerr<<"BYE";
            if (!visited[w]){
                // std::cerr<<"HI";
                rbt.erase(rbt.find({sp[w],w}));
                rbt.insert({k+sp[v],w});
                sp[w] = std::min(sp[w],k+sp[v]);
            }
        }
        visited[v] = true;
    }
}

void Testcase::getMinWeight() {
    // TODO: Complete this function
    if (src==dest) {
        std::cout<<"0";
        return;
    }
    int min_dist = INT_MAX;
    std::vector sp(n+1,INT_MAX);
    Dijkstra(Edges,sp,n,src);
    if (min_dist == INT_MAX){
        for (auto& edge: ExtraEdges){
            std::vector sp(n+1,INT_MAX);
            Edges.insert(Edges.end(),edge);
            Dijkstra(Edges,sp,n,src);
            Edges.pop_back();
            if (sp[dest]<min_dist) min_dist = sp[dest];
        }
        if (min_dist == INT_MAX) std::cout<< "-1";
        else std::cout<< min_dist;
    }
    else std::cout<< min_dist;
}