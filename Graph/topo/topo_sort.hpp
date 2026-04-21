#ifndef TOPO_SORT_HPP
#define TOPO_SORT_HPP

#include "../graph_library.hpp"
#include <vector>
#include <queue>
#include <stack>
#include <stdexcept>

using namespace std;


vector<int> topo_sort_kahn(Graph &g) {

    if (!g.isDirected) {
        throw runtime_error("Topological sort requires a directed graph");
    }

    int V = g.V;

    vector<int> indegree(V, 0);

    for (int u = 0; u < V; u++) {
        for (int i = 0; i < g.adj[u].size(); i++) {
            int v = g.adj[u][i].first;
            indegree[v]++;
        }
    }

    queue<int> q;

    for (int i = 0; i < V; i++) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }

    vector<int> topo;

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        topo.push_back(node);

        for (int i = 0; i < g.adj[node].size(); i++) {
            int neigh = g.adj[node][i].first;

            indegree[neigh]--;
            if (indegree[neigh] == 0) {
                q.push(neigh);
            }
        }
    }
    if (topo.size() != V) {
        throw runtime_error("Graph contains a cycle, topo sort not possible");
    }

    return topo;
}



void dfs_topo(int node, Graph &g, vector<int> &visited, stack<int> &st) {
    visited[node] = 1;

    for (int i = 0; i < g.adj[node].size(); i++) {
        int neigh = g.adj[node][i].first;

        if (!visited[neigh]) {
            dfs_topo(neigh, g, visited, st);
        }
    }

    st.push(node);
}

vector<int> topo_sort_dfs(Graph &g) {
    if (!g.isDirected) {
        throw runtime_error("Topological sort requires a directed graph");
    }

    int V = g.V;

    vector<int> visited(V, 0);
    stack<int> st;

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            dfs_topo(i, g, visited, st);
        }
    }

    vector<int> topo;

    while (!st.empty()) {
        topo.push_back(st.top());
        st.pop();
    }

    return topo;
}

#endif