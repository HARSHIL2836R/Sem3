#include "graph.h"

void Graph::alltopologicalSort() {

    // To indicate whether all topological are found
    // or not
    bool flag = false;

    for (int i = 0; i < V; i++)
    {
        //  If indegree is 0 and not yet visited then
        //  only choose that vertex
        if (indegree[i] == 0 && !visited[i])
        {
            //  reducing indegree of adjacent vertices
            list<int>:: iterator j;
            for (j = adj[i].begin(); j != adj[i].end(); j++)
                indegree[*j]--;

            //  including in result
            sorted.push_back(i);
            visited[i] = true;
            alltopologicalSort(//visited
                                        );

            // resetting visited, res and indegree for
            // backtracking
            visited[i] = false;
            sorted.erase(sorted.end() - 1);
            for (j = adj[i].begin(); j != adj[i].end(); j++)
                indegree[*j]++;

            flag = true;
        }
    }

    //  We reach here if all vertices are visited.
    //  So we print the solution here
    if (!flag)
    {
      if( sorted.size() == V ) {
        report_a_sorted_order();
      }else{
        report_failed_to_sort();
      }
    }
}
