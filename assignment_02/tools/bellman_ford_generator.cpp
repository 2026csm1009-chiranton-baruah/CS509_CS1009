#include <iostream>
#include <vector>
#include <random>
#include <set>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Usage: " << argv[0]
             << " <V> <E> <output_file>\\n";
        return 1;
    }

    int V = stoi(argv[1]);
    int E = stoi(argv[2]);
    string outFile = argv[3];

    if (V <= 0 || E < 0) {
        cerr << "Invalid V or E\\n";
        return 1;
    }

    random_device rd;
    mt19937 rng(rd());

    uniform_int_distribution<int> vertexDist(0, V - 1);
    uniform_int_distribution<int> weightDist(-10, 20);

    vector<vector<pair<int,int>>> adj(V);
    set<pair<int,int>> used;

    while ((int)used.size() < E) {
        int u = vertexDist(rng);
        int v = vertexDist(rng);

        if (u == v) continue;
        if (used.count({u, v})) continue;

        used.insert({u, v});
        adj[u].push_back({v, weightDist(rng)});
    }

    ofstream fout(outFile);

    fout << V << " " << E << "\\n";

    for (int u = 0; u < V; ++u) {
        fout << u << " " << adj[u].size();

        for (auto [v, w] : adj[u]) {
            fout << " " << v << " " << w;
        }
        fout << "\\n";
    }

    fout << "SOURCE 0\\n";

    cout << "Generated " << outFile << " (V="
         << V << ", E=" << E << ")\\n";

    return 0;
}
