#ifndef DSU_H
#define DSU_H

#include "../algotoolkit.h"

class DSU {
public:
    vector<int> parent, rank;

    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for(int i=0;i<n;i++) parent[i]=i;
    }

    int find(int x) {
        if(parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if(a != b) {
            if(rank[a] < rank[b]) swap(a,b);
            parent[b] = a;
            if(rank[a] == rank[b]) rank[a]++;
        }
    }
};

#endif