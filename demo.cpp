#include "Graph/graph.hpp"
#include <iostream>

using namespace std;

int main() {

    cout << "===== GRAPH 1: BFS, DFS, DIJKSTRA, MST =====\n";

    Graph g1(6, false, true);

    g1.addEdge(0, 1, 2);
    g1.addEdge(0, 2, 4);
    g1.addEdge(1, 2, 1);
    g1.addEdge(1, 3, 7);
    g1.addEdge(2, 4, 3);
    g1.addEdge(3, 5, 1);
    g1.addEdge(4, 5, 5);

    vector<int> bfs_order = bfs(g1, 0);
    cout << "BFS: ";
    for (int x : bfs_order) cout << x << " ";
    cout << endl;

    vector<int> dfs_order = dfs(g1, 0);
    cout << "DFS: ";
    for (int x : dfs_order) cout << x << " ";
    cout << endl;

    vector<vector<int>> comps = connected_components(g1);
    cout << "Connected Components:\n";
    for (int i = 0; i < comps.size(); i++) {
        for (int x : comps[i]) cout << x << " ";
        cout << endl;
    }

    vector<int> dist = dijkstra(g1, 0);
    cout << "Dijkstra distances:\n";
    for (int i = 0; i < dist.size(); i++) {
        cout << i << " -> " << dist[i] << endl;
    }

    auto kr = kruskal(g1);
    cout << "Kruskal MST Weight: " << kr.first << endl;

    auto pr = prim(g1);
    cout << "Prim MST Weight: " << pr.first << endl;

    cout << "\n===== GRAPH 2: SCC + TOPO =====\n";

    Graph g2(6, true, false);

    g2.addEdge(0, 1);
    g2.addEdge(1, 2);
    g2.addEdge(2, 0);
    g2.addEdge(2, 3);
    g2.addEdge(3, 4);
    g2.addEdge(4, 5);

    vector<vector<int>> sccs = kosaraju(g2);
    cout << "SCCs:\n";
    for (int i = 0; i < sccs.size(); i++) {
        for (int x : sccs[i]) cout << x << " ";
        cout << endl;
    }

    try {
        vector<int> topo = topo_sort_kahn(g2);
        cout << "Topo Sort (Kahn): ";
        for (int x : topo) cout << x << " ";
        cout << endl;
    } catch (...) {
        cout << "Topo not possible (cycle detected)\n";
    }

    cout << "\n===== GRAPH 3: TREE (LCA + SUBTREE) =====\n";

    Graph tree(7, false, false);

    tree.addEdge(0, 1);
    tree.addEdge(0, 2);
    tree.addEdge(1, 3);
    tree.addEdge(1, 4);
    tree.addEdge(2, 5);
    tree.addEdge(2, 6);

    LCA lca(tree, 0);

    cout << "LCA(3,4): " << lca.get_lca(3, 4) << endl;
    cout << "LCA(3,5): " << lca.get_lca(3, 5) << endl;

    Subtree st(tree, 0);

    cout << "Subtree size of node 1: " << st.subtree_size[1] << endl;

    cout << "tin/tout values:\n";
    for (int i = 0; i < 7; i++) {
        cout << "Node " << i << ": " << st.tin[i] << " " << st.tout[i] << endl;
    }

    return 0;
}