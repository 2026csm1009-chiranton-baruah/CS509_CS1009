#include "../include/csr.h"

#include <fstream>
#include <iostream>

using namespace std;

bool readAdjacencyList(
        const string& filename,
        vector<vector<Edge>>& adjacencyList,
        bool weighted,
        int& V,
        int& E)
{
    ifstream fin(filename);

    if (!fin.is_open())
    {
        cout << "Unable to open file.\n";
        return false;
    }

    fin >> V >> E;

    adjacencyList.assign(V, vector<Edge>());

    for (int i = 0; i < V; i++)
    {
        int vertex;
        int degree;

        fin >> vertex >> degree;

        for (int j = 0; j < degree; j++)
        {
            if (weighted)
            {
                int neighbour;
                int weight;

                fin >> neighbour >> weight;

                adjacencyList[vertex].push_back(
                    Edge(neighbour, weight));
            }
            else
            {
                int neighbour;

                fin >> neighbour;

                adjacencyList[vertex].push_back(
                    Edge(neighbour));
            }
        }
    }

    fin.close();

    return true;
}
