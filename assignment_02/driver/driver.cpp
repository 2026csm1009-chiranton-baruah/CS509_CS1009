#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <filesystem>
#include <algorithm>

#include "../include/csr_graph.hpp"
#include "../include/bellman_ford.hpp"
#include "../include/floyd_warshall.hpp"

using namespace std;
namespace fs = std::filesystem;

// =====================================================
// Bellman-Ford
// =====================================================

bool readBF(const string& path,
            vector<vector<pair<int,int>>>& adj,
            int& V, int& E, int& source) {
    ifstream fin(path);
    if (!fin) return false;

    fin >> V >> E;
    if (!fin || V <= 0 || E < 0) return false;

    adj.assign(V, {});

    for (int i = 0; i < V; ++i) {
        int u, degree;
        fin >> u >> degree;

        if (!fin || u < 0 || u >= V || degree < 0)
            return false;

        for (int j = 0; j < degree; ++j) {
            int v, w;
            fin >> v >> w;

            if (!fin || v < 0 || v >= V)
                return false;

            adj[u].push_back({v, w});
        }
    }

    string label;
    fin >> label >> source;

    return fin && label == "SOURCE" && source >= 0 && source < V;
}

void runBellmanFord(const string& path) {
    vector<vector<pair<int,int>>> adj;
    int V, E, source;

    if (!readBF(path, adj, V, E, source)) {
        cerr << "Error reading " << path << "\\n";
        return;
    }

    // Preprocessing (NOT timed)
    CSRGraph g = convertToCSR(adj);

    // Timed region
    auto start = chrono::high_resolution_clock::now();
    BellmanFordResult res = bellmanFord(g, source);
    auto end = chrono::high_resolution_clock::now();

    double ms = chrono::duration<double, milli>(end - start).count();

    cout << "\\n=== Bellman-Ford : " << path << " ===\\n";
    cout << "Source: " << source << "\\n";

    if (res.hasNegativeCycle) {
        cout << "Negative cycle: true\\n";
    } else {
        cout << "Vertex Distance\\n";

        for (int i = 0; i < V; ++i) {
            cout << i << " ";

            if (res.dist[i] == BF_INF)
                cout << "INF\\n";
            else
                cout << res.dist[i] << "\\n";
        }

        cout << "Negative cycle: none\\n";
    }

    cout << fixed << setprecision(3);
    cout << "Execution time: " << ms << " ms\\n";
}

// =====================================================
// Floyd-Warshall
// =====================================================

bool readFW(const string& path,
            vector<vector<int64>>& matrix,
            int& V) {
    ifstream fin(path);
    if (!fin) return false;

    fin >> V;
    if (!fin || V <= 0) return false;

    matrix.assign(V, vector<int64>(V, FW_INF));

    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            string tok;
            fin >> tok;

            if (!fin) return false;

            if (tok == "INF")
                matrix[i][j] = FW_INF;
            else
                matrix[i][j] = stoll(tok);
        }
    }

    return true;
}

void runFloydWarshall(const string& path) {
    vector<vector<int64>> matrix;
    int V;

    if (!readFW(path, matrix, V)) {
        cerr << "Error reading " << path << "\\n";
        return;
    }

    auto start = chrono::high_resolution_clock::now();
    FloydWarshallResult res = floydWarshall(matrix);
    auto end = chrono::high_resolution_clock::now();

    double ms = chrono::duration<double, milli>(end - start).count();

    cout << "\\n=== Floyd-Warshall : " << path << " ===\\n";

    if (res.hasNegativeCycle) {
        cout << "Negative cycle: true\\n";
    } else {
        cout << "Distance matrix:\\n";

        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                if (j) cout << ' ';

                if (res.dist[i][j] == FW_INF)
                    cout << "INF";
                else
                    cout << res.dist[i][j];
            }
            cout << '\\n';
        }

        cout << "Negative cycle: none\\n";
    }

    cout << fixed << setprecision(3);
    cout << "Execution time: " << ms << " ms\\n";
}

// =====================================================
// Test discovery
// =====================================================

vector<string> collectTests(const string& dir) {
    vector<string> files;

    if (!fs::exists(dir)) return files;

    for (const auto& entry : fs::directory_iterator(dir)) {
        if (entry.is_regular_file()) {
            files.push_back(entry.path().string());
        }
    }

    sort(files.begin(), files.end());
    return files;
}

void runAllBF() {
    auto files = collectTests("tests/bellman_ford");

    if (files.empty()) {
        cout << "No Bellman-Ford test files found.\\n";
        return;
    }

    for (const auto& f : files)
        runBellmanFord(f);
}

void runAllFW() {
    auto files = collectTests("tests/floyd_warshall");

    if (files.empty()) {
        cout << "No Floyd-Warshall test files found.\\n";
        return;
    }

    for (const auto& f : files)
        runFloydWarshall(f);
}

// =====================================================
// Menu
// =====================================================

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (true) {
        cout << "\\n===== Assignment 02 Driver =====\\n";
        cout << "1. Run Bellman-Ford (one file)\\n";
        cout << "2. Run Floyd-Warshall (one file)\\n";
        cout << "3. Run all Bellman-Ford tests\\n";
        cout << "4. Run all Floyd-Warshall tests\\n";
        cout << "0. Exit\\n";
        cout << "Choice: ";

        int choice;
        if (!(cin >> choice)) break;

        if (choice == 0) break;

        if (choice == 1) {
            string path;
            cout << "Enter Bellman-Ford test file path: ";
            cin >> path;
            runBellmanFord(path);
        }
        else if (choice == 2) {
            string path;
            cout << "Enter Floyd-Warshall test file path: ";
            cin >> path;
            runFloydWarshall(path);
        }
        else if (choice == 3) {
            runAllBF();
        }
        else if (choice == 4) {
            runAllFW();
        }
        else {
            cout << "Invalid choice\\n";
        }
    }

    return 0;
}
