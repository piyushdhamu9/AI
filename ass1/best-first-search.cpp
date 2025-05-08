#include <bits/stdc++.h>
using namespace std;

vector<int> bfs(vector<vector<int>> &edgelist, int s, int d, int n)
{

    vector<vector<pair<int, int>>> adj(n);

    for (auto edge : edgelist)
    {
        int u = edge[0], v = edge[1], w = edge[2];

        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    priority_queue<pair<int, int>> pq;

    vector<bool> vis(n, false);
    vector<int> path;

    // {weight, node}
    pq.push({0, s});
    vis[s] = true;

    while (!pq.empty())
    {
        int node = pq.top().second;
        pq.pop();

        vis[node] = 1;
        path.push_back(node);

        if (node == d)
            break;

        for (auto ng : adj[node])
        {
            int nd = ng.first;
            int cost = ng.second;
            if (!vis[nd])
            {
                vis[nd] = 1;
                pq.push({-cost, nd});
            }
        }
    }

    return path;
}

int main()
{
    cout << "Best First Search\n";
    int n = 14;

    vector<vector<int>> edgelist = {
        {0, 1, 3}, {0, 2, 6}, {0, 3, 5}, {1, 4, 9}, {1, 5, 8}, {2, 6, 12}, {2, 7, 14}, {3, 8, 7}, {8, 9, 5}, {8, 10, 6}, {9, 11, 1}, {9, 12, 10}, {9, 13, 2}};

    int s = 0, d = 9;

    vector<int> path = bfs(edgelist, s, d, n);

    cout << "Path from node " << s << " to node " << d << ": ";
    for (int node : path)
    {
        cout << node << " ";
    }
    return 0;
}