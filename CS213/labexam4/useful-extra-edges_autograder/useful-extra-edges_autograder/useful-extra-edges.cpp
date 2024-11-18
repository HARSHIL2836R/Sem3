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

#define ll long long

void Dijkstra(std::vector<std::vector<std::pair<int,int>>>& adj, std::vector<ll>& dist,
 std::priority_queue<std::pair<ll, int>>& pq, std::vector<bool>& visited)
{
	while(!pq.empty())
	{
		auto p = pq.top();
		pq.pop();
		if(visited[p.second])
			continue;
		int min_node = p.second;
		ll min_dist = -1 * p.first;

		for(auto e : adj[min_node])
		{
			if(! visited[e.first])
			{
				ll new_dist = min_dist + e.second;
				if(new_dist < dist[e.first])
				{
					pq.push({-new_dist, e.first});
					dist[e.first] = new_dist;
				}
			}
		}	
		visited[min_node] = true;
	}
}


void Testcase::getMinWeight() {
	// TODO: Complete this function

	// std::cout<<n<<std::endl;
	std::vector<std::vector<std::pair<int, int>>> adj(n+1, std::vector<std::pair<int,int>>());
	for(auto e : Edges)
	{
		// std::cout<<e[0]<<" "<<e[1]<<"\n";
		adj[e[0]].push_back({e[1],e[2]});
		adj[e[1]].push_back({e[0],e[2]});
	}


	// std::vector<std::vector<std::pair<int, int>>> adj_extra;
	// for(auto e : ExtraEdges)
	// {
	// 	adj_extra[e[0]].push_back({e[1],e[2]});
	// 	adj_extra[e[1]].push_back({e[0],e[2]});
	// }


	std::priority_queue<std::pair<ll,int>> pq;
	std::vector<ll> dist(n+1, LLONG_MAX);
	std::vector<bool> visited(n+1, false);

	dist[src] = 0;
	pq.push({0,src});

	Dijkstra(adj, dist, pq, visited);

	std::vector<ll> new_dist = dist;

	for(auto e : ExtraEdges)
	{
		int u = e[0];
		int v = e[1];
		int k = e[2];
		if(dist[u] == dist[v])
			continue;
		if(dist[u] > dist[v])
			std::swap(u,v);
		//dist[u] < dist[v]
		if(new_dist[v] <= dist[u] + k)
			continue;
		new_dist[v] = dist[u] + k;
		pq.push({-new_dist[v], v});
	}

	visited = std::vector<bool>(n, false);
	// visited[src] = true;
	Dijkstra(adj, new_dist, pq, visited);

	if(new_dist[dest] == LLONG_MAX)
		std::cout<<-1<<"\n";
	else
		std::cout<<new_dist[dest]<<"\n";
	

}