#include "check-tree.h"

// PLEASE DO NOT ADD ANY EXTRA HEADERS

bool has_cycle(std::set<tuple<int, int, int>> ft){
    return false;
}

bool check_tree(unsigned n, vector<vector<int>> dist, vector<tuple<int, int, int>> &found_tree) {

    // YOUR CODE HERE
    std::set<tuple<int, int, int>> ft;
    for (int i=0;i<dist.size();i++){
        for (int k = 0; k<dist.size();k++){
            if ( i!= k) ft.insert({i,k,dist[i][k]});
        }
    }

    //Reduce the tree
    for (int src = 0; src < dist.size(); src++) // source
    {
        for (int dst = 0; dst<dist.size();dst++){ // destination
            if (src != dst){
                for (int i = 0; i<dist.size();i++){ // intermediate
                    if (dist[src][dst] == dist[src][i]+dist[i][dst]){
                        ft.erase(ft.find({src,dst,dist[src][dst]}));
                        break;
                    }
                }
            }
        }
    }
    
    if (has_cycle(ft)) return false;

    for(auto el: ft){
        found_tree.push_back(el);
    }
    return true;
}

