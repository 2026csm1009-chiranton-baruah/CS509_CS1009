#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "../include/csr_graph.hpp"
#include "../include/mst.hpp"

using namespace std;
using namespace chrono;


/*
 * Read a weighted undirected adjacency-list graph.
 */
bool readGraph(
    const string& filename,
    int& V,
    int& E,
    vector<vector<pair<int, int>>>& adj
)
{
    ifstream input(filename);

    if (!input.is_open())
    {
        cerr << "Error: Unable to open input file.\n";
        return false;
    }

    input >> V >> E;

    if (!input || V <= 0 || E < 0)
    {
        cerr << "Error: Invalid graph header.\n";
        return false;
    }

    adj.resize(V);

    for (int i = 0; i < V; ++i)
    {
        int u;
        int degree;

        input >> u >> degree;

        if (
            !input
            || u < 0
            || u >= V
            || degree < 0
        )
        {
            cerr << "Error: Invalid adjacency-list entry.\n";
            return false;
        }

        for (int j = 0; j < degree; ++j)
        {
            int v;
            int weight;

            input >> v >> weight;

            if (
                !input
                || v < 0
                || v >= V
            )
            {
                cerr << "Error: Invalid edge.\n";
                return false;
            }

            adj[u].push_back({v, weight});
        }
    }

    return true;
}


/*
 * Print the result produced by an MST algorithm.
 */
void printResult(
    const string& algorithm,
    const MSTResult& result,
    double execution_time
)
{
    cout << "\nAlgorithm: "
         << algorithm << "\n";

    cout << "MST edges:\n";

    for (const MSTEdge& edge : result.edges)
    {
        cout << edge.u << " "
             << edge.v << " "
             << edge.weight << "\n";
    }

    cout << "Total MST weight: "
         << result.total_weight << "\n";

    cout << "Execution time: "
         << execution_time
         << " ms\n";
}


int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        cerr << "Usage: "
             << argv[0]
             << " <input_file>\n";

        return 1;
    }

    string filename = argv[1];

    int V;
    int E;

    vector<vector<pair<int, int>>> adj;

    /*
     * Input reading occurs before timing.
     */
    if (!readGraph(filename, V, E, adj))
    {
        return 1;
    }


    /*
     * CSR conversion is preprocessing.
     *
     * Therefore, it occurs BEFORE either timer starts.
     */
    CSRGraph graph = convertToCSR(adj);


    /*
     * Run Kruskal.
     */
    auto start_kruskal =
        high_resolution_clock::now();

    MSTResult kruskal_result =
        kruskalMST(graph);

    auto end_kruskal =
        high_resolution_clock::now();

    double kruskal_time =
        duration<double, milli>(
            end_kruskal - start_kruskal
        ).count();


    /*
     * Run Prim.
     */
    auto start_prim =
        high_resolution_clock::now();

    MSTResult prim_result =
        primMST(graph);

    auto end_prim =
        high_resolution_clock::now();

    double prim_time =
        duration<double, milli>(
            end_prim - start_prim
        ).count();


    /*
     * Output is produced AFTER timing.
     */
    printResult(
        "Kruskal's MST",
        kruskal_result,
        kruskal_time
    );

    printResult(
        "Prim's MST",
        prim_result,
        prim_time
    );


    /*
     * Both algorithms must produce the same
     * minimum total weight.
     */
    if (
        kruskal_result.total_weight
        == prim_result.total_weight
    )
    {
        cout << "\nMST weight comparison: MATCH\n";
    }
    else
    {
        cout << "\nMST weight comparison: MISMATCH\n";
    }

    return 0;
}
