#ifndef KRUSKAL_HPP
#define KRUSKAL_HPP

#include "../graph_library.hpp"
#include <vector>
#include <algorithm>
#include <stdexcept>

using namespace std;

class DSU {
public:
    vector<int> parent, rank;

    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void unite(int x, int y) {
        int px = find(x);
        int py = find(y);

        if (px == py) return;

        if (rank[px] < rank[py]) parent[px] = py;
        else if (rank[px] > rank[py]) parent[py] = px;
        else {
            parent[py] = px;
            rank[px]++;
        }
    }
};

pair<int, vector<vector<int>>> kruskal(Graph &g) {

    if (!g.isWeighted) {
        throw runtime_error("Kruskal requires a weighted graph");
    }

    vector<vector<int>> edges = g.edges;

    sort(edges.begin(), edges.end(), [](vector<int>& a, vector<int>& b) {
        return a[2] < b[2];
    });

    DSU dsu(g.V);

    int totalWeight = 0;
    vector<vector<int>> mst;

    for (int i = 0; i < edges.size(); i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int w = edges[i][2];

        if (dsu.find(u) != dsu.find(v)) {
            dsu.unite(u, v);
            totalWeight += w;
            mst.push_back({u, v, w});
        }
    }

    return {totalWeight, mst};
}

#endif