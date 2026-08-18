#include "../include/mst.hpp"

#include <algorithm>
#include <functional>
#include <limits>
#include <queue>
#include <vector>

using namespace std;


/*
 * Disjoint Set Union / Union-Find
 * Used by Kruskal's algorithm to detect cycles.
 */
class DSU
{
private:
    vector<int> parent;
    vector<int> rank;

public:
    DSU(int n)
    {
        parent.resize(n);
        rank.assign(n, 0);

        for (int i = 0; i < n; ++i)
        {
            parent[i] = i;
        }
    }

    int find(int x)
    {
        if (parent[x] != x)
        {
            parent[x] = find(parent[x]);
        }

        return parent[x];
    }

    bool unite(int a, int b)
    {
        int root_a = find(a);
        int root_b = find(b);

        if (root_a == root_b)
        {
            return false;
        }

        if (rank[root_a] < rank[root_b])
        {
            parent[root_a] = root_b;
        }
        else if (rank[root_a] > rank[root_b])
        {
            parent[root_b] = root_a;
        }
        else
        {
            parent[root_b] = root_a;
            ++rank[root_a];
        }

        return true;
    }
};


/*
 * Extract each undirected edge exactly once.
 *
 * The MST input stores every undirected edge twice:
 *
 *     u -> v
 *     v -> u
 *
 * Therefore, only keep edges where u < v.
 *
 * This extraction and sorting are intentionally inside
 * Kruskal's algorithm because Assignment 3 requires them
 * to be included in Kruskal's measured execution time.
 */
static vector<MSTEdge> extractEdges(const CSRGraph& graph)
{
    vector<MSTEdge> edges;

    for (int u = 0; u < graph.V; ++u)
    {
        for (int i = graph.row_ptr[u];
             i < graph.row_ptr[u + 1];
             ++i)
        {
            int v = graph.col_idx[i];
            int weight = graph.values[i];

            if (u < v)
            {
                edges.push_back({u, v, weight});
            }
        }
    }

    return edges;
}


/*
 * Kruskal's Minimum Spanning Tree algorithm.
 */
MSTResult kruskalMST(const CSRGraph& graph)
{
    MSTResult result;
    result.total_weight = 0;

    vector<MSTEdge> edges = extractEdges(graph);

    sort(
        edges.begin(),
        edges.end(),
        [](const MSTEdge& a, const MSTEdge& b)
        {
            if (a.weight != b.weight)
            {
                return a.weight < b.weight;
            }

            if (a.u != b.u)
            {
                return a.u < b.u;
            }

            return a.v < b.v;
        }
    );

    DSU dsu(graph.V);

    for (const MSTEdge& edge : edges)
    {
        if (dsu.unite(edge.u, edge.v))
        {
            result.edges.push_back(edge);
            result.total_weight += edge.weight;

            if (
                static_cast<int>(result.edges.size())
                == graph.V - 1
            )
            {
                break;
            }
        }
    }

    return result;
}


/*
 * Prim's Minimum Spanning Tree algorithm.
 *
 * Assignment 3 recommends starting from vertex 0.
 */
MSTResult primMST(const CSRGraph& graph)
{
    MSTResult result;
    result.total_weight = 0;

    if (graph.V == 0)
    {
        return result;
    }

    const int INF = numeric_limits<int>::max();

    vector<int> key(graph.V, INF);
    vector<int> parent(graph.V, -1);
    vector<bool> in_mst(graph.V, false);

    using QueueEntry = pair<int, int>;

    priority_queue<
        QueueEntry,
        vector<QueueEntry>,
        greater<QueueEntry>
    > min_heap;

    key[0] = 0;

    min_heap.push({0, 0});

    while (!min_heap.empty())
    {
        int weight = min_heap.top().first;
        int u = min_heap.top().second;

        min_heap.pop();

        if (in_mst[u])
        {
            continue;
        }

        in_mst[u] = true;

        if (parent[u] != -1)
        {
            result.edges.push_back(
                {
                    parent[u],
                    u,
                    weight
                }
            );

            result.total_weight += weight;
        }

        for (int i = graph.row_ptr[u];
             i < graph.row_ptr[u + 1];
             ++i)
        {
            int v = graph.col_idx[i];
            int edge_weight = graph.values[i];

            if (
                !in_mst[v]
                && edge_weight < key[v]
            )
            {
                key[v] = edge_weight;
                parent[v] = u;

                min_heap.push(
                    {
                        edge_weight,
                        v
                    }
                );
            }
        }
    }

    return result;
}
