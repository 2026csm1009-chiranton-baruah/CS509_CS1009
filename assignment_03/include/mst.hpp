#ifndef MST_HPP
#define MST_HPP

#include <vector>

#include "csr_graph.hpp"

struct MSTEdge {
    int u;
    int v;
    int weight;
};

struct MSTResult {
    std::vector<MSTEdge> edges;
    long long total_weight;
};

MSTResult kruskalMST(const CSRGraph& graph);

MSTResult primMST(const CSRGraph& graph);

#endif
