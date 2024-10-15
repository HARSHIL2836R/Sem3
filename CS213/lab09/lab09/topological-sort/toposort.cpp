#include "graph.h" // needed

// you may or may not use this dfs function
// but the end result has to be stored in stack Graph::S
    static std::map<int,bool> onPath;

void Graph::dfs(int s) {
    if(nodes[s]->visited == 1) return;
    if(onPath[s] == 1) throw 100;
    onPath[s] = 1;
    for( auto x : nodes[s]->adj ){
        dfs(x.first);
    }
    onPath[s] = 0;
    nodes[s]->visited = 1;
    S.push(s);
}

// this function is to be implemented
void Graph::topoSort() {
    onPath.clear();
    try{
    for(auto i : nodes){
        if(i.second->visited == false) dfs(i.first);
    }
    }
    catch(int n){
        if(n==100){
            return;
        }
    }
}