#ifndef GRAPH_H
#define GRAPH_H

#include "../algotoolkit.h"

class Graph {
public:
    int V;
    bool directed;
    vector<vector<pair<int,int>>> adj;
    vector<tuple<int,int,int>> edges;

    Graph(int V, bool directed = false) {
    this->V = V;
    this->directed = directed;
    adj.resize(V);
    }

    void addEdge(int u, int v, int w = 1) {
    adj[u].push_back({v, w});

    if(!directed) {
        adj[v].push_back({u, w});
    }
    }
};

#endif