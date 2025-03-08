#include "dijkstras.h"
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.numVertices;
    vector<int> dist(n, INF);
    previous.assign(n, -1);
    vector<bool> visited(n, false);
    using Node = pair<int,int>; 
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    dist[source] = 0;
    pq.push({0, source});
    while (!pq.empty()) {
        auto [curDist, u] = pq.top();
        pq.pop();
        if (visited[u]) {continue};
        visited[u] = true;
        for (auto &edge : G[u]) {
            int v = edge.dst;
            int w = edge.weight;
            if (!visited[v] && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                previous[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}
