#ifndef SCC_HPP
#define SCC_HPP

#include "../graph.hpp"
#include <vector>
#include <stack>
#include <stdexcept>

using namespace std;

void dfs1(int node, Graph &g, vector<int> &visited, stack<int> &st) {
    visited[node] = 1;

    for (int i = 0; i < g.adj[node].size(); i++) {
        int neigh = g.adj[node][i].first;
        if (!visited[neigh]) {
            dfs1(neigh, g, visited, st);
        }
    }

    st.push(node);
}

void dfs2(int node, vector<vector<int>> &revAdj, vector<int> &visited, vector<int> &component) {
    visited[node] = 1;
    component.push_back(node);

    for (int i = 0; i < revAdj[node].size(); i++) {
        int neigh = revAdj[node][i];
        if (!visited[neigh]) {
            dfs2(neigh, revAdj, visited, component);
        }
    }
}

vector<vector<int>> kosaraju(Graph &g) {

    if (!g.isDirected) {
        throw runtime_error("SCC works only on directed graphs");
    }

    int V = g.V;

    stack<int> st;
    vector<int> visited(V, 0);

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            dfs1(i, g, visited, st);
        }
    }

    vector<vector<int>> revAdj(V);

    for (int u = 0; u < V; u++) {
        for (int i = 0; i < g.adj[u].size(); i++) {
            int v = g.adj[u][i].first;
            revAdj[v].push_back(u);
        }
    }

    vector<vector<int>> sccs;
    fill(visited.begin(), visited.end(), 0);

    while (!st.empty()) {
        int node = st.top();
        st.pop();

        if (!visited[node]) {
            vector<int> component;
            dfs2(node, revAdj, visited, component);
            sccs.push_back(component);
        }
    }

    return sccs;
}

#endif