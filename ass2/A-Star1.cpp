#include <bits/stdc++.h>
using namespace std;

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

// Check if a puzzle is solvable
bool isSolvable(vector<vector<int>> &puzzle)
{
    vector<int> flat;
    for (auto &row : puzzle)
        for (int val : row)
            if (val != 0)
                flat.push_back(val);

    int inversions = 0;
    for (int i = 0; i < flat.size(); ++i)
        for (int j = i + 1; j < flat.size(); ++j)
            if (flat[i] > flat[j])
                inversions++;

    return inversions % 2 == 0;
}

// Heuristic function: Tile Replacement
int heuristic(vector<vector<int>> &a, vector<vector<int>> &goal)
{
    int mismatch = 0;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (a[i][j] != 0 && a[i][j] != goal[i][j])
                mismatch++;
        }
    }
    return mismatch;
}

// Check if the position is valid
bool isValid(int x, int y)
{
    return x >= 0 && x < 3 && y >= 0 && y < 3;
}

// Print puzzle state and heuristic value
void printPuzzle(const vector<vector<int>> &puzzle, int heuristicValue, int level)
{
    for (const auto &row : puzzle)
    {
        for (int val : row)
            cout << val << " ";
        cout << endl;
    }
    cout << "Heuristic Value (h(n)): " << heuristicValue << endl;
    cout << "Level (g(n)): " << level << endl;
    cout << "Total Cost (f(n) = g(n) + h(n)): " << heuristicValue + level << endl;
    cout << "------\n";
}

struct State
{
    vector<vector<int>> puzzle;
    int x, y, level, cost;
    shared_ptr<State> parent;

    State(vector<vector<int>> p, int x_, int y_, int l, int c, shared_ptr<State> par = nullptr)
        : puzzle(p), x(x_), y(y_), level(l), cost(c), parent(par) {}
};

struct Compare
{
    bool operator()(const shared_ptr<State> &a, const shared_ptr<State> &b)
    {
        return a->cost > b->cost;
    }
};

void printPath(shared_ptr<State> state)
{
    vector<shared_ptr<State>> path;
    while (state)
    {
        path.push_back(state);
        state = state->parent;
    }
    reverse(path.begin(), path.end());

    for (const auto &s : path)
    {
        printPuzzle(s->puzzle, s->cost - s->level, s->level);
    }
}

void aStarPuzzle(vector<vector<int>> start, vector<vector<int>> goal, int startX, int startY)
{
    priority_queue<shared_ptr<State>, vector<shared_ptr<State>>, Compare> pq;
    set<vector<vector<int>>> visitedStates;

    int h = heuristic(start, goal);
    auto initial = make_shared<State>(start, startX, startY, 0, h);
    pq.push(initial);

    while (!pq.empty())
    {
        auto curr = pq.top();
        pq.pop();

        if (curr->puzzle == goal)
        {
            cout << "Goal Reached!\n\n";
            printPath(curr);
            return;
        }

        visitedStates.insert(curr->puzzle);

        for (int i = 0; i < 4; ++i)
        {
            int newX = curr->x + dx[i];
            int newY = curr->y + dy[i];

            if (isValid(newX, newY))
            {
                vector<vector<int>> newPuzzle = curr->puzzle;
                swap(newPuzzle[curr->x][curr->y], newPuzzle[newX][newY]);

                if (visitedStates.count(newPuzzle))
                    continue;

                int newLevel = curr->level + 1;
                int newCost = newLevel + heuristic(newPuzzle, goal);
                auto newState = make_shared<State>(newPuzzle, newX, newY, newLevel, newCost, curr);
                pq.push(newState);
            }
        }
    }

    cout << "No solution found.\n";
}

int main()
{
    vector<vector<int>> initial = {
        {1, 2, 3},
        {5, 6, 0},
        {7, 8, 4}};

    vector<vector<int>> goal = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 0}};

    int blankX, blankY;
    // Find position of 0 (blank tile)
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (initial[i][j] == 0)
            {
                blankX = i;
                blankY = j;
            }
        }
    }

    if (!isSolvable(initial))
    {
        cout << "\nThe given puzzle is unsolvable.\n";
        return 0;
    }

    cout << "\nA* Algorithm (8 Puzzle using Tile Replacement Heuristic):\n";
    aStarPuzzle(initial, goal, blankX, blankY);

    return 0;
}
