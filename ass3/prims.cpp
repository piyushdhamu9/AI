#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

void primMST(vector<vector<pair<int, int>>> &graph)
{
    int V = graph.size();
    vector<int> key(V, INT_MAX), parent(V, -1);
    vector<bool> inMST(V, false);
    key[0] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, 0});

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        inMST[u] = true;

        for (auto x : graph[u])
        {
            int weight = x.second;
            int v = x.first;
            if (!inMST[v] && weight < key[v])
            {
                key[v] = weight;
                parent[v] = u;
                pq.push({key[v], v});
            }
        }
    }

    int totalWeight = 0;
    cout << "\nEdges included in the Minimum Spanning Tree:\n";
    cout << "--------------------------------------------\n";
    cout << " Edge\t\tWeight\n";
    cout << "------------------------\n";
    for (int i = 1; i < V; ++i)
    {
        cout << " " << parent[i] << " - " << i << "\t\t" << key[i] << "\n";
        totalWeight += key[i];
    }
    cout << "------------------------\n";
    cout << "Total weight of MST: " << totalWeight << "\n";
}

int main()
{
    cout << "Prim's Algorithm - Minimum Spanning Tree (MST)\n";
    cout << "==============================================\n";

    int V = 5;
    vector<vector<pair<int, int>>> graph(V);
    graph[0] = {{1, 2}, {3, 6}};
    graph[1] = {{0, 2}, {2, 3}, {3, 8}, {4, 5}};
    graph[2] = {{1, 3}, {4, 7}};
    graph[3] = {{0, 6}, {1, 8}};
    graph[4] = {{1, 5}, {2, 7}};

    primMST(graph);
    return 0;
}