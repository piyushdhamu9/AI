#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge
{
    int u, v, weight;
};

bool compare(Edge a, Edge b)
{
    return a.weight < b.weight;
}

int find(vector<int> &parent, int i)
{
    if (parent[i] != i)
        parent[i] = find(parent, parent[i]);
    return parent[i];
}

void unionSet(vector<int> &parent, vector<int> &rank, int x, int y)
{
    int xroot = find(parent, x);
    int yroot = find(parent, y);
    if (rank[xroot] < rank[yroot])
        parent[xroot] = yroot;
    else if (rank[xroot] > rank[yroot])
        parent[yroot] = xroot;
    else
    {
        parent[yroot] = xroot;
        rank[xroot]++;
    }
   
}

void kruskalMST(vector<Edge> &edges, int V)
{
    sort(edges.begin(), edges.end(), compare);

    vector<int> parent(V), rank(V, 0);
    
    for (int i = 0; i < V; ++i)
        parent[i] = i;

    vector<Edge> result;
    int totalWeight = 0;

    for (auto &edge : edges)
    {
        int u = find(parent, edge.u);
        int v = find(parent, edge.v);
        if (u != v)
        {
            result.push_back(edge);
            unionSet(parent, rank, u, v);
            totalWeight += edge.weight;
        }
    }

    cout << "\nEdges included in the Minimum Spanning Tree:\n";
    cout << "--------------------------------------------\n";
    cout << " Edge\t\tWeight\n";
    cout << "------------------------\n";
    for (auto &edge : result)
        cout << " " << edge.u << " - " << edge.v << "\t\t" << edge.weight << "\n";

    cout << "------------------------\n";
    cout << "Total weight of MST: " << totalWeight << "\n";
}

int main()
{
    cout << "Kruskal's Algorithm - Minimum Spanning Tree (MST)\n";
    cout << "=================================================\n";
    int V = 4;
    vector<Edge> edges = {
        {0, 1, 10}, {0, 2, 6}, {0, 3, 5}, {1, 3, 15}, {2, 3, 4}};
    kruskalMST(edges, V);
    return 0;
}
