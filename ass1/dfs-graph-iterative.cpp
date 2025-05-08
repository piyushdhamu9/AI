#include <bits/stdc++.h>
using namespace std;

void dfsIterative(int x, vector<vector<int>> &adj, int n)
{
    vector<bool> visited(n, false);
    stack<int> st;

    st.push(x);

    while (!st.empty())
    {
        int node = st.top();
        st.pop();

        if (!visited[node])
        {
            visited[node] = true;
            cout << node << " ";
        }

        for (int i = adj[node].size() - 1; i >= 0; i--)
        {
            int ng = adj[node][i];
            if (!visited[ng])
            {
                st.push(ng);
            }
        }
    }
}

int main()
{
    int n = 5;

    vector<vector<int>> adj(n);

    // Add edges (undirected graph)
    adj[0] = {1, 2};
    adj[1] = {0, 3, 4};
    adj[2] = {0};
    adj[3] = {1};
    adj[4] = {1};

    cout << "DFS Iterative: ";
    dfsIterative(0, adj, n); // Start DFS from node 0

    return 0;
}