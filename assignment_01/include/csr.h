#ifndef CSR_H
#define CSR_H

#include <vector>
#include <string>

using namespace std;

// Edge representation
struct Edge
{
    int destination;
    int weight;

    Edge(int d, int w = 1)
    {
        destination = d;
        weight = w;
    }
};

// CSR Graph
struct CSRGraph
{
    int V;
    int E;

    vector<int> row_ptr;
    vector<int> col_idx;
    vector<int> values;
};

// Read adjacency-list graph from file
bool readAdjacencyList(
    const string& filename,
    vector<vector<Edge>>& adjacencyList,
    bool weighted,
    int& V,
    int& E);

// Convert adjacency list to CSR
CSRGraph convertToCSR(
    const vector<vector<Edge>>& adjacencyList,
    bool weighted);

// Print CSR arrays
void printCSR(const CSRGraph& graph,
              bool weighted);

#endif
