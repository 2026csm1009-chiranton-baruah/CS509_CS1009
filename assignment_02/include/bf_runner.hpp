#ifndef BF_RUNNER_HPP
#define BF_RUNNER_HPP

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <chrono>

#include "csr_graph.hpp"
#include "bellman_ford.hpp"

inline void runBellmanFord(const std::string& path) {
    using namespace std;

    ifstream fin(path);
    if (!fin) {
        cerr << "Cannot open " << path << '\\n';
        return;
    }

    int V, E;
    fin >> V >> E;

    vector<vector<pair<int,int>>> adj(V);

    for (int i = 0; i < V; ++i) {
        int u, d;
        fin >> u >> d;

        for (int j = 0; j < d; ++j) {
            int v, w;
            fin >> v >> w;
            adj[u].push_back({v, w});
        }
    }

    string label;
    int source;
    fin >> label >> source;

    CSRGraph g = convertToCSR(adj);

    auto start = chrono::high_resolution_clock::now();
    auto res = bellmanFord(g, source);
    auto end = chrono::high_resolution_clock::now();

    double ms = chrono::duration<double, milli>(end - start).count();

    cout << "\\n=== Bellman-Ford : " << path << " ===\\n";

    if (res.hasNegativeCycle) {
        cout << "Negative cycle: true\\n";
    } else {
        cout << "Vertex Distance\\n";

        for (int i = 0; i < V; ++i) {
            cout << i << " ";

            if (res.dist[i] == BF_INF)
                cout << "INF\\n";
            else
                cout << res.dist[i] << '\\n';
        }

        cout << "Negative cycle: none\\n";
    }

    cout << fixed << setprecision(3);
    cout << "Execution time: " << ms << " ms\\n";
}

#endif
