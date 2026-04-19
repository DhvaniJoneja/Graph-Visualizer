#include "../graph/graph.h"

void topo(Graph &g) {
    vector<int> indegree(g.V, 0);

    for(int u = 0; u < g.V; u++) {
        for(auto &p : g.adj[u]) {
            int v = p.first;
            indegree[v]++;
        }
    }

    queue<int> q;

    for(int i = 0; i < g.V; i++) {
        if(indegree[i] == 0) {
            q.push(i);
        }
    }

    vector<int> order;

    while(!q.empty()) {
        int u = q.front(); q.pop();

        cout << "VISIT " << u << endl;
        order.push_back(u);

        for(auto &p : g.adj[u]) {
            int v = p.first;

            cout << "EDGE " << u << " " << v << endl;

            indegree[v]--;

            if(indegree[v] == 0) {
                q.push(v);
            }
        }
    }

    if(order.size() != g.V) {
        cout << "CYCLE" << endl;
        return;
    }

    for(int x : order) {
        cout << "RESULT_NODE " << x << endl;
    }

    cout << "DONE" << endl;
}