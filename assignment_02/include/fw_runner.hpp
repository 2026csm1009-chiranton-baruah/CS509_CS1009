#ifndef FW_RUNNER_HPP
#define FW_RUNNER_HPP

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <chrono>

#include "floyd_warshall.hpp"

inline void runFloydWarshall(const std::string& path) {
    using namespace std;

    ifstream fin(path);
    if (!fin) {
        cerr << "Cannot open " << path << '\\n';
        return;
    }

    int V;
    fin >> V;

    vector<vector<int64>> matrix(V, vector<int64>(V, FW_INF));

    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            string tok;
            fin >> tok;

            if (tok == "INF")
                matrix[i][j] = FW_INF;
            else
                matrix[i][j] = stoll(tok);
        }
    }

    auto start = chrono::high_resolution_clock::now();
    auto res = floydWarshall(matrix);
    auto end = chrono::high_resolution_clock::now();

    double ms = chrono::duration<double, milli>(end - start).count();

    cout << "\\n=== Floyd-Warshall : " << path << " ===\\n";

    if (res.hasNegativeCycle) {
        cout << "Negative cycle: true\\n";
    } else {
        cout << "Distance matrix:\\n";

        for (const auto& row : res.dist) {
            for (size_t j = 0; j < row.size(); ++j) {
                if (j) cout << ' ';

                if (row[j] == FW_INF)
                    cout << "INF";
                else
                    cout << row[j];
            }
            cout << '\\n';
        }

        cout << "Negative cycle: none\\n";
    }

    cout << fixed << setprecision(3);
    cout << "Execution time: " << ms << " ms\\n";
}

#endif
