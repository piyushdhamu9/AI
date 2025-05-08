#include <bits/stdc++.h>
using namespace std;

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

// Heuristic: Count of misplaced tiles
int heuristic(vector<vector<int>> &a, vector<vector<int>> &goal)
{
    int mismatch = 0;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (a[i][j] != 0 && a[i][j] != goal[i][j])
                mismatch++;
    return mismatch;
}

bool isValid(int x, int y)
{
    return x >= 0 && x < 3 && y >= 0 && y < 3;
}

void printPuzzle(const vector<vector<int>> &puzzle, int heuristicValue, int level)
{
    cout << "Level: " << level << endl;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
            cout << puzzle[i][j] << " ";
        cout << endl;
    }
    cout << "Heuristic Value (h(n)): " << heuristicValue << endl;
    cout << "Total Cost (f(n) = g(n) + h(n)): " << heuristicValue + level << endl;
    cout << "------\n";
}

struct State
{
    vector<vector<int>> puzzle;
    int x, y, level, cost;
};

struct Compare
{
    bool operator()(const State &a, const State &b)
    {
        return a.cost > b.cost;
    }
};

// Check if a puzzle is solvable based on inversion count
bool isSolvable(const vector<vector<int>> &puzzle)
{
    vector<int> flattened;
    for (const auto &row : puzzle)
        for (int val : row)
            if (val != 0)
                flattened.push_back(val);

    int inversions = 0;
    for (int i = 0; i < flattened.size(); ++i)
        for (int j = i + 1; j < flattened.size(); ++j)
            if (flattened[i] > flattened[j])
                inversions++;

    return inversions % 2 == 0;
}

void aStarPuzzle(vector<vector<int>> start, vector<vector<int>> goal, int startX, int startY)
{
    priority_queue<State, vector<State>, Compare> pq;
    set<vector<vector<int>>> visitedStates;

    State initial = {start, startX, startY, 0, heuristic(start, goal)};
    pq.push(initial);

    while (!pq.empty())
    {
        State curr = pq.top();
        pq.pop();

        if (visitedStates.count(curr.puzzle))
            continue;

        visitedStates.insert(curr.puzzle);
        printPuzzle(curr.puzzle, curr.cost - curr.level, curr.level);

        if (curr.puzzle == goal)
        {
            cout << "Goal Reached in " << curr.level << " moves!\n";
            return;
        }

        for (int i = 0; i < 4; ++i)
        {
            int newX = curr.x + dx[i];
            int newY = curr.y + dy[i];

            if (isValid(newX, newY))
            {
                vector<vector<int>> newPuzzle = curr.puzzle;
                swap(newPuzzle[curr.x][curr.y], newPuzzle[newX][newY]);

                if (!visitedStates.count(newPuzzle))
                {
                    int newLevel = curr.level + 1;
                    int newCost = newLevel + heuristic(newPuzzle, goal);
                    pq.push({newPuzzle, newX, newY, newLevel, newCost});
                }
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
        cout << "This puzzle is not solvable.\n";
        return 0;
    }

    cout << "\nSolving 8-Puzzle using A* (Tile Replacement Heuristic):\n";
    aStarPuzzle(initial, goal, blankX, blankY);

    return 0;
}

// int main() {
//     vector<vector<int>> initial(3, vector<int>(3));
//     vector<vector<int>> goal(3, vector<int>(3));
//     int blankX, blankY;

//     cout << "\nEnter initial puzzle state (use 0 for blank):\n";
//     for (int i = 0; i < 3; ++i)
//         for (int j = 0; j < 3; ++j) {
//             cin >> initial[i][j];
//             if (initial[i][j] == 0) {
//                 blankX = i;
//                 blankY = j;
//             }
//         }

//     cout << "Enter goal puzzle state (use 0 for blank):\n";
//     for (int i = 0; i < 3; ++i)
//         for (int j = 0; j < 3; ++j)
//             cin >> goal[i][j];

//     if (!isSolvable(initial)) {
//         cout << "This puzzle is not solvable.\n";
//         return 0;
//     }

//     cout << "\nSolving 8-Puzzle using A* (Tile Replacement Heuristic):\n";
//     aStarPuzzle(initial, goal, blankX, blankY);

//     return 0;
// }
