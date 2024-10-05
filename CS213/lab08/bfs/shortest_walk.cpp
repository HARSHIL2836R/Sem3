#include "graph.cpp"


void shortest_walk(Graph g,vector<int>&stations, vector<int>& path)
{
    vector<int>::iterator itr1,itr2;
    itr1 = stations.begin();
    itr2 = stations.begin() + 1;
    path.push_back(*itr1);
    while (itr2 != stations.end()){
        unordered_map<int, int> parent;
        bfs(g,*itr2,parent);
        int curr = *itr1;
        while (parent[curr]!=*itr2){
            path.push_back(parent[curr]);
            curr = parent[curr];
        }
        path.push_back(*itr2);
        itr1++;itr2++;
    }
}
