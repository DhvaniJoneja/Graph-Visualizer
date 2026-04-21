#ifndef SUBTREE_HPP
#define SUBTREE_HPP

#include "../graph_library.hpp"
#include <vector>

using namespace std;

class Subtree {
public:
    int timer;
    vector<int> tin, tout;
    vector<int> subtree_size;

    Subtree(Graph &g, int root = 0) {
        int V = g.V;

        timer = 0;
        tin.resize(V);
        tout.resize(V);
        subtree_size.resize(V);

        dfs(root, -1, g);
    }

    void dfs(int node, int parent, Graph &g) {
        tin[node] = timer++;
        subtree_size[node] = 1;

        for (int i = 0; i < g.adj[node].size(); i++) {
            int neigh = g.adj[node][i].first;

            if (neigh != parent) {
                dfs(neigh, node, g);
                subtree_size[node] += subtree_size[neigh];
            }
        }

        tout[node] = timer - 1;
    }

    bool is_ancestor(int u, int v) {
        return tin[u] <= tin[v] && tout[v] <= tout[u];
    }
};

#endif