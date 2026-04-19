#include "../graph/graph.h"

void bfs(Graph &g, int start) {
    vector<int> vis(g.V, 0);
    queue<int> q;

    q.push(start);
    vis[start] = 1;

    while(!q.empty()) {
        int u = q.front(); q.pop();

        cout << "VISIT " << u << endl;

        for(auto &p : g.adj[u]) {
            int v = p.first;

            if(!vis[v]) {
                vis[v] = 1;
                q.push(v);

                cout << "EDGE " << u << " " << v << endl;
            }
        }
    }

    cout << "DONE" << endl;
}