#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;


struct Edge
{
    int u;
    int v;
    int weight;
};


long long makeKey(int u, int v)
{
    if (u > v)
    {
        swap(u, v);
    }

    return (static_cast<long long>(u) << 32)
           | static_cast<unsigned int>(v);
}


vector<Edge> generateGraph(
    int V,
    int E,
    mt19937& rng)
{
    vector<Edge> edges;
    unordered_set<long long> usedEdges;

    edges.reserve(E);
    usedEdges.reserve(E * 2);


    /*
     * Step 1:
     * Generate a random spanning tree.
     *
     * This guarantees that the graph is connected.
     */
    for (int v = 1; v < V; ++v)
    {
        uniform_int_distribution<int> parentDist(0, v - 1);
        int u = parentDist(rng);

        uniform_int_distribution<int> weightDist(1, 1000);
        int weight = weightDist(rng);

        edges.push_back({u, v, weight});
        usedEdges.insert(makeKey(u, v));
    }


    /*
     * Step 2:
     * Add random edges until E is reached.
     */
    uniform_int_distribution<int> vertexDist(0, V - 1);
    uniform_int_distribution<int> weightDist(1, 1000);

    while (static_cast<int>(edges.size()) < E)
    {
        int u = vertexDist(rng);
        int v = vertexDist(rng);

        if (u == v)
        {
            continue;
        }

        long long key = makeKey(u, v);

        if (usedEdges.find(key) != usedEdges.end())
        {
            continue;
        }

        usedEdges.insert(key);

        edges.push_back(
            {
                u,
                v,
                weightDist(rng)
            }
        );
    }

    return edges;
}


void writeGraph(
    const string& filename,
    int V,
    const vector<Edge>& edges)
{
    vector<vector<pair<int, int>>> adjacency(V);

    /*
     * Insert every undirected edge into both
     * endpoint adjacency lists.
     */
    for (const Edge& edge : edges)
    {
        adjacency[edge.u].push_back(
            {edge.v, edge.weight}
        );

        adjacency[edge.v].push_back(
            {edge.u, edge.weight}
        );
    }


    /*
     * Sort adjacency lists by neighbour.
     * This makes generated files easier to inspect.
     */
    for (int u = 0; u < V; ++u)
    {
        sort(
            adjacency[u].begin(),
            adjacency[u].end()
        );
    }


    ofstream output(filename);

    if (!output.is_open())
    {
        cerr << "Error: Could not create "
             << filename << "\n";

        return;
    }


    /*
     * Header:
     *
     * V E
     *
     * E counts each undirected edge once.
     */
    output << V << " "
           << edges.size()
           << "\n";


    /*
     * Each vertex:
     *
     * u degree neighbour weight ...
     */
    for (int u = 0; u < V; ++u)
    {
        output << u << " "
               << adjacency[u].size();

        for (const auto& neighbour : adjacency[u])
        {
            output << " "
                   << neighbour.first
                   << " "
                   << neighbour.second;
        }

        output << "\n";
    }

    output.close();

    cout << "Generated "
         << filename
         << " (V = "
         << V
         << ", E = "
         << edges.size()
         << ")\n";
}


void generateTest(
    const string& filename,
    int V,
    int E,
    mt19937& rng)
{
    /*
     * A simple undirected graph can contain at most
     * V * (V - 1) / 2 unique edges.
     */
    long long maxEdges =
        static_cast<long long>(V)
        * (V - 1)
        / 2;

    if (E < V - 1)
    {
        cerr << "Error: E must be at least V - 1 "
             << "for a connected graph.\n";

        return;
    }

    if (static_cast<long long>(E) > maxEdges)
    {
        cerr << "Error: Too many edges for "
             << "a simple graph.\n";

        return;
    }

    vector<Edge> edges =
        generateGraph(V, E, rng);

    writeGraph(filename, V, edges);
}


int main()
{
    /*
     * Fixed seed makes the test cases reproducible.
     *
     * If you want different graphs every time,
     * replace this with:
     *
     * random_device rd;
     * mt19937 rng(rd());
     */
    mt19937 rng(509);


    /*
     * Required Assignment 3 MST test cases.
     *
     * The specification recommends keeping large
     * graphs sparse, approximately E = 2V to 4V.
     */

    generateTest(
        "mst_10.txt",
        10,
        20,
        rng
    );

    generateTest(
        "mst_100.txt",
        100,
        300,
        rng
    );

    generateTest(
        "mst_10000.txt",
        10000,
        30000,
        rng
    );

    generateTest(
        "mst_50000.txt",
        50000,
        150000,
        rng
    );

    generateTest(
        "mst_100000.txt",
        100000,
        300000,
        rng
    );


    cout << "\nAll MST test files generated.\n";

    return 0;
}
