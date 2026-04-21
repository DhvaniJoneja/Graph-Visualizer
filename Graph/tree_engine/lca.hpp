#ifndef LCA_HPP
#define LCA_HPP

#include "../graph_library.hpp"
#include <vector>

using namespace std;

class LCA {
public:
    int V, LOG;
    vector<vector<int>> up;
    vector<int> depth;

    LCA(Graph &g, int root = 0) {
        V = g.V;

        LOG = 0;
        while ((1 << LOG) <= V) LOG++;

        up.assign(V, vector<int>(LOG));
        depth.assign(V, 0);

        dfs(root, root, g);
    }

    void dfs(int node, int parent, Graph &g) {
        up[node][0] = parent;

        for (int i = 1; i < LOG; i++) {
            up[node][i] = up[up[node][i-1]][i-1];
        }

        for (int i = 0; i < g.adj[node].size(); i++) {
            int neigh = g.adj[node][i].first;

            if (neigh != parent) {
                depth[neigh] = depth[node] + 1;
                dfs(neigh, node, g);
            }
        }
    }

    int get_lca(int a, int b) {

        if (depth[a] < depth[b]) {
            int temp = a;
            a = b;
            b = temp;
        }

        int diff = depth[a] - depth[b];

        for (int i = LOG - 1; i >= 0; i--) {
            if (diff & (1 << i)) {
                a = up[a][i];
            }
        }

        if (a == b) return a;

        for (int i = LOG - 1; i >= 0; i--) {
            if (up[a][i] != up[b][i]) {
                a = up[a][i];
                b = up[b][i];
            }
        }

        return up[a][0];
    }
};

#endif