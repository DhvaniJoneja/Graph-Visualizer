#include "../graph/graph.h"

void dijkstra(Graph &g, int src) {
    vector<int> dist(g.V, INT_MAX);
    vector<int> parent(g.V, -1);  

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while(!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();

        if(d > dist[u]) continue;
        cout << "VISIT " << u << endl;

        for(auto &p : g.adj[u]) {
            int v = p.first;
            int w = p.second;

            if(dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                parent[v] = u;  

                cout << "EDGE " << u << " " << v << endl;
                cout << "DIST " << v << " " << dist[v] << endl;

                pq.push({dist[v], v});
            }
        }
    }

    for(int i = 0; i < g.V; i++) {
        if(dist[i] != INT_MAX)
            cout << "DIST " << i << " " << dist[i] << endl;
    }

    int target = g.V - 1;   
    vector<int> path;

    while(target != -1) {
        path.push_back(target);
        target = parent[target];
    }

    reverse(path.begin(), path.end());

    for(int i = 0; i < path.size(); i++) {
        cout << "RESULT_NODE " << path[i] << endl;

        if(i > 0) {
            cout << "RESULT_EDGE " << path[i-1] << " " << path[i] << endl;
        }
    }

    cout << "DONE" << endl;
}