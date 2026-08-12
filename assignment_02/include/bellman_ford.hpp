#ifndef BELLMAN_FORD_HPP
#define BELLMAN_FORD_HPP

#include <vector>
#include <cstdint>
#include "csr_graph.hpp"

using int64 = long long;

static const int64 BF_INF = (1LL << 60);

struct BellmanFordResult {
    bool hasNegativeCycle;
    std::vector<int64> dist;
};

inline BellmanFordResult bellmanFord(const CSRGraph& g, int source) {
    std::vector<int64> dist(g.V, BF_INF);
    dist[source] = 0;

    // Relax all edges V-1 times
    for (int i = 1; i <= g.V - 1; ++i) {
        bool changed = false;

        for (int u = 0; u < g.V; ++u) {
            if (dist[u] == BF_INF) continue;

            for (int e = g.row_ptr[u]; e < g.row_ptr[u + 1]; ++e) {
                int v = g.col_idx[e];
                int w = g.values[e];

                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    changed = true;
                }
            }
        }

        if (!changed) break;
    }

    // Extra pass for negative-cycle detection
    for (int u = 0; u < g.V; ++u) {
        if (dist[u] == BF_INF) continue;

        for (int e = g.row_ptr[u]; e < g.row_ptr[u + 1]; ++e) {
            int v = g.col_idx[e];
            int w = g.values[e];

            if (dist[u] + w < dist[v]) {
                return {true, {}};
            }
        }
    }

    return {false, dist};
}

#endif
