#ifndef GRAPH_ENGINE_HPP
#define GRAPH_ENGINE_HPP

#include "graph_library.hpp"

// traversal
#include "traversal/bfs.hpp"
#include "traversal/dfs.hpp"
#include "traversal/connected_components.hpp"

// shortest path
#include "shortest_path/dijkstra.hpp"

// mst
#include "mst/kruskal.hpp"
#include "mst/prim.hpp"

// scc
#include "scc/scc.hpp"   // make sure filename matches

// topo
#include "topo/topo_sort.hpp"

// tree
#include "tree_engine/lca.hpp"
#include "tree_engine/subtree.hpp"

#endif