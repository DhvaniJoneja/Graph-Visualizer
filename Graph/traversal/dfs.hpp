#ifndef DFS_HPP
#define DFS_HPP

#include "../graph_library.hpp"
#include <vector>

using namespace std;

void dfs_helper(int node, Graph &g, vector<int> &visited, vector<int> &order) {
    visited[node] = 1;
    order.push_back(node);

    for (int i = 0; i < g.adj[node].size(); i++) {
        int neigh = g.adj[node][i].first;

        if (!visited[neigh]) {
            dfs_helper(neigh, g, visited, order);
        }
    }
}

vector<int> dfs(Graph &g, int start) {
    vector<int> visited(g.V, 0);
    vector<int> order;

    dfs_helper(start, g, visited, order);

    return order;
}

#endif