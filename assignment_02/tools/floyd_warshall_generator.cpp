#include <iostream>
#include <fstream>
#include <random>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0]
             << " <V> <output_file>\\n";
        return 1;
    }

    int V = stoi(argv[1]);
    string outFile = argv[2];

    random_device rd;
    mt19937 rng(rd());

    uniform_int_distribution<int> weightDist(-5, 15);
    uniform_real_distribution<double> edgeProb(0.0, 1.0);

    ofstream fout(outFile);

    fout << V << "\\n";

    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (j) fout << " ";

            if (i == j) {
                fout << 0;
            } else if (edgeProb(rng) < 0.35) {
                fout << weightDist(rng);
            } else {
                fout << "INF";
            }
        }
        fout << "\\n";
    }

    cout << "Generated " << outFile
         << " (V=" << V << ")\\n";

    return 0;
}
