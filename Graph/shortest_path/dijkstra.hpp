#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include "../graph_library.hpp"
#include <vector>
#include <queue>
#include <stdexcept>
#include <limits>

using namespace std;

vector<int> dijkstra(Graph &g, int src) {

    if (!g.isWeighted) {
        throw runtime_error("Dijkstra requires a weighted graph");
    }

    int V = g.V;

    vector<int> dist(V, numeric_limits<int>::max());

    // {distance, node}
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        pair<int,int> top = pq.top();
        pq.pop();

        int d = top.first;
        int node = top.second;

        // Skip outdated entries
        if (d > dist[node]) continue;

        for (int i = 0; i < g.adj[node].size(); i++) {
            int neigh = g.adj[node][i].first;
            int weight = g.adj[node][i].second;

            if (dist[node] + weight < dist[neigh]) {
                dist[neigh] = dist[node] + weight;
                pq.push({dist[neigh], neigh});
            }
        }
    }

    return dist;
}

#endif