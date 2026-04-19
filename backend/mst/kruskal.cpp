#include "../graph/graph.h"
#include "dsu.h"

void kruskal(Graph &g) {
    vector<tuple<int,int,int>> edges;

    for(int u = 0; u < g.V; u++) {
        for(auto &p : g.adj[u]) {
            int v = p.first;
            int w = p.second;

            if(u < v) edges.push_back({w, u, v});
        }
    }

    sort(edges.begin(), edges.end());

    DSU dsu(g.V);

    for(auto &[w, u, v] : edges) {
        cout << "EDGE " << u << " " << v << endl;

        if(dsu.find(u) != dsu.find(v)) {
            dsu.unite(u, v);

            cout << "RESULT_EDGE " << u << " " << v << endl;
        }
    }

    cout << "DONE" << endl;
}