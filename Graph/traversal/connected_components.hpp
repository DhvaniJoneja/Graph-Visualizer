#ifndef CONNECTED_COMPONENTS_HPP
#define CONNECTED_COMPONENTS_HPP

#include "../graph_library.hpp"
#include <vector>

using namespace std;

void dfs_cc(int node, Graph &g, vector<int> &visited, vector<int> &component) {
    visited[node] = 1;
    component.push_back(node);

    for (int i = 0; i < g.adj[node].size(); i++) {
        int neigh = g.adj[node][i].first;

        if (!visited[neigh]) {
            dfs_cc(neigh, g, visited, component);
        }
    }
}

vector<vector<int>> connected_components(Graph &g) {

    int V = g.V;
    vector<int> visited(V, 0);
    vector<vector<int>> components;

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            vector<int> component;
            dfs_cc(i, g, visited, component);
            components.push_back(component);
        }
    }

    return components;
}

#endif