#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
using namespace std;

class Graph {
public:
    int V;
    bool isDirected;
    bool isWeighted;
    vector<vector<pair<int,int>>> adj;

    vector<vector<int>> edges; // {u, v, w}

    Graph(int n, bool directed = false, bool weighted = false) {
        V = n;
        isDirected = directed;
        isWeighted = weighted;
        adj.resize(n);
    }

    void addEdge(int u, int v, int w = 1) {
        if (isWeighted == false) w = 1;

        adj[u].push_back({v, w});
        edges.push_back({u, v, w});

        if (!isDirected) {
            adj[v].push_back({u, w});
        }
    }
};

#endif