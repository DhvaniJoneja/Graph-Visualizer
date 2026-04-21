#ifndef PRIM_HPP
#define PRIM_HPP

#include "../graph_library.hpp"
#include <vector>
#include <queue>
#include <stdexcept>

using namespace std;

pair<int, vector<vector<int>>> prim(Graph &g, int start = 0) {

    if (!g.isWeighted) {
        throw runtime_error("Prim requires a weighted graph");
    }

    vector<int> visited(g.V, 0);

    // {weight, node, parent}
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;

    pq.push({0, start, -1});

    int totalWeight = 0;
    vector<vector<int>> mst;

    while (!pq.empty()) {
        vector<int> top = pq.top();
        pq.pop();

        int w = top[0];
        int node = top[1];
        int parent = top[2];

        if (visited[node]) continue;

        visited[node] = 1;
        totalWeight += w;

        if (parent != -1) {
            mst.push_back({parent, node, w});
        }

        for (int i = 0; i < g.adj[node].size(); i++) {
            int neigh = g.adj[node][i].first;
            int weight = g.adj[node][i].second;

            if (!visited[neigh]) {
                pq.push({weight, neigh, node});
            }
        }
    }

    return {totalWeight, mst};
}

#endif