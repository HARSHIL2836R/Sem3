#include "graph.h" // needed

// you may or may not use this dfs function
// but the end result has to be stored in stack Graph::S
void Graph::dfs(int s) {
    for (auto nbr = nodes[s]->adj.begin(); nbr != nodes[s]->adj.end(); nbr++) {
        if (!nodes[nbr->first]->visited) {
            dfs(nbr->first);
        }
    }
    nodes[s]->visited = true;
    S.push(s);
}

// this function is to be implemented
void Graph::topoSort() {
    for (auto it = nodes.begin(); it != nodes.end(); it++) {
        if (!it->second->visited) {
            dfs(it->first);
        }
    }
}
