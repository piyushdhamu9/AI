#include <iostream>
#include <vector>
using namespace std;

#define V 4  // Number of vertices

// Check if it's safe to assign color c to vertex v
bool isSafe(int v, const vector<vector<int>>& graph, vector<int>& color, int c) {
    for (int i = 0; i < V; i++) {
        if (graph[v][i] && color[i] == c)
            return false;
    }
    return true;
}

// Recursive utility function for coloring
bool graphColoringUtil(const vector<vector<int>>& graph, int m, vector<int>& color, int v) {
    if (v == V)
        return true;  // All vertices are assigned a color

    for (int c = 1; c <= m; c++) {
        if (isSafe(v, graph, color, c)) {
            color[v] = c;  // Assign color c

            if (graphColoringUtil(graph, m, color, v + 1))
                return true;

            color[v] = 0;  // Backtrack
        }
    }

    return false;
}

// Main graph coloring function
bool graphColoring(const vector<vector<int>>& graph, int m) {
    vector<int> color(V, 0);

    if (!graphColoringUtil(graph, m, color, 0)) {
        cout << "\nNo solution exists for " << m << " colors.\n";
        return false;
    }

    // Solution found
    cout << "\nSolution Exists: Vertex -> Color assignment:\n";
    for (int i = 0; i < V; i++)
        cout << "Vertex " << i << " ---> Color " << color[i] << endl;

    return true;
}

int main() {
    vector<vector<int>> graph = {
        {0, 1, 1, 1},
        {1, 0, 1, 0},
        {1, 1, 0, 1},
        {1, 0, 1, 0}
    };

    int m = 3;  // Number of colors
    cout << "Graph Coloring Problem for " << m << " colors:\n";
    graphColoring(graph, m);

    return 0;
}
