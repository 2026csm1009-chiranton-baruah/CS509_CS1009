#ifndef FLOYD_WARSHALL_HPP
#define FLOYD_WARSHALL_HPP

#include <vector>
#include <cstdint>

using int64 = long long;

static const int64 FW_INF = (1LL << 60);

struct FloydWarshallResult {
    bool hasNegativeCycle;
    std::vector<std::vector<int64>> dist;
};

inline FloydWarshallResult floydWarshall(
    std::vector<std::vector<int64>> dist
) {
    int V = static_cast<int>(dist.size());

    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            if (dist[i][k] == FW_INF) continue;

            for (int j = 0; j < V; ++j) {
                if (dist[k][j] == FW_INF) continue;

                int64 throughK = dist[i][k] + dist[k][j];

                if (throughK < dist[i][j]) {
                    dist[i][j] = throughK;
                }
            }
        }
    }

    // Negative-cycle check
    for (int i = 0; i < V; ++i) {
        if (dist[i][i] < 0) {
            return {true, {}};
        }
    }

    return {false, dist};
}

#endif
