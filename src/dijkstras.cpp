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

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    if ((destination < 0) || (destination >= (int)distances.size()) || (distances[destination] == INF)) {return {};}
    vector<int> path;
    for (int v = destination; v != -1; v = previous[v]) {path.push_back(v);}
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& v, int total) {
    if (v.empty()) {
        cout << "No path" << endl;
        return;
    }
    for (size_t i = 0; i < v.size(); i++) {
        if (i > 0) cout << " ";
        cout << v[i];
    }
    cout << endl;
    cout << "Total cost: " << total << endl;
}
