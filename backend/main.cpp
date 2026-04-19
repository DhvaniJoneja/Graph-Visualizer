#include <iostream>
#include <vector>
#include <queue>
#include <limits>

#include "graph/graph.h"
#include "traversal/bfs.cpp"
#include "traversal/dfs.cpp"
#include "shortest_path/dijkstra.cpp"
#include "mst/prim.cpp"
#include "mst/kruskal.cpp"
#include "topo/topo.cpp"

using namespace std;

int main() {
    int V, E;
    int directed, weighted;

    cin >> V >> E >> directed >> weighted;

    Graph g(V, directed); 

    for(int i = 0; i < E; i++) {
        int u, v, w = 1;
        cin >> u >> v;

        if(weighted) cin >> w;

        g.addEdge(u, v, w);
    }

    int choice, source;
    cin >> choice >> source;

    if(choice == 1) bfs(g, source);
    else if(choice == 3) dijkstra(g, source);
    else if(choice == 4) prim(g);
    else if(choice == 2) dfs(g, source);
    else if(choice == 5) kruskal(g);
    else if(choice == 6) topo(g);
    return 0;
}