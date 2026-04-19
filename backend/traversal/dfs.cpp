#include "../graph/graph.h"

void dfsHelper(Graph &g, int u, vector<int> &vis) {
    vis[u] = 1;

    cout << "VISIT " << u << endl;

    for(auto &p : g.adj[u]) {
        int v = p.first;

        if(!vis[v]) {
            cout << "EDGE " << u << " " << v << endl;

            dfsHelper(g, v, vis);
        }
    }
}

void dfs(Graph &g, int start) {
    vector<int> vis(g.V, 0);

    dfsHelper(g, start, vis);

    cout << "DONE" << endl;
}