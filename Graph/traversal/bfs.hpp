#ifndef BFS_HPP
#define BFS_HPP

#include "../graph_library.hpp"
#include <vector>
#include <queue>

using namespace std;

vector<int> bfs(Graph &g, int start) {

    vector<int> visited(g.V, 0);
    vector<int> order;

    queue<int> q;
    q.push(start);
    visited[start] = 1;

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        order.push_back(node);

        for (int i = 0; i < g.adj[node].size(); i++) {
            int neigh = g.adj[node][i].first;

            if (!visited[neigh]) {
                visited[neigh] = 1;
                q.push(neigh);
            }
        }
    }

    return order;
}

#endif