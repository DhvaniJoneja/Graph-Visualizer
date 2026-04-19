#include "../graph/graph.h"

void prim(Graph &g) {
    vector<int> key(g.V, INT_MAX);
    vector<int> parent(g.V, -1);
    vector<bool> inMST(g.V, false);

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;

    key[0] = 0;
    pq.push({0, 0});

    while(!pq.empty()) {
        auto [w, u] = pq.top(); pq.pop();

        if(inMST[u]) continue;

        inMST[u] = true;

        cout << "VISIT " << u << endl;

        for(auto &p : g.adj[u]) {
            int v = p.first;
            int weight = p.second;

            if(!inMST[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;

                cout << "EDGE " << u << " " << v << endl;

                pq.push({key[v], v});
            }
        }
    }

    for(int i = 1; i < g.V; i++) {
        if(parent[i] != -1) {
            cout << "RESULT_EDGE " << parent[i] << " " << i << endl;
        }
    }

    cout << "DONE" << endl;
}