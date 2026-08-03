#include "../include/csr.h"

#include <iostream>

using namespace std;

CSRGraph convertToCSR(
        const vector<vector<Edge>>& adjacencyList,
        bool weighted)
{
    CSRGraph graph;

    graph.V = adjacencyList.size();
    graph.E = 0;

    graph.row_ptr.push_back(0);

    for (int i = 0; i < graph.V; i++)
    {
        for (const Edge& edge : adjacencyList[i])
        {
            graph.col_idx.push_back(edge.destination);

            if (weighted)
                graph.values.push_back(edge.weight);

            graph.E++;
        }

        graph.row_ptr.push_back(graph.col_idx.size());
    }

    return graph;
}

void printCSR(const CSRGraph& graph,
              bool weighted)
{
    cout << "\nCSR Representation\n";

    cout << "\nrow_ptr:\n";

    for (int x : graph.row_ptr)
        cout << x << " ";

    cout << "\n\ncol_idx:\n";

    for (int x : graph.col_idx)
        cout << x << " ";

    if (weighted)
    {
        cout << "\n\nvalues:\n";

        for (int x : graph.values)
            cout << x << " ";
    }

    cout << endl;
}
