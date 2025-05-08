#include <bits/stdc++.h>
using namespace std;
#define int long long

vector<vector<vector<int>>> ans;

bool check(vector<vector<int>> &v, int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < v[0].size(); j++)
        {
            if ((v[i][j] == 1 && col == j) ||
                (v[i][j] == 1 && (i - j == row - col || i + j == row + col)))
            {
                return false;
            }
        }
    }
    return true;
}

void solve(int n, vector<vector<int>> &v, int row)
{
    if (row == n)
    {
        ans.push_back(v);
        return;
    }
    for (int i = 0; i < n; i++)
    {
        if (check(v, row, i))
        {
            v[row][i] = 1;
            solve(n, v, row + 1);
            v[row][i] = 0;
        }
    }
}

void printSolutionBoards(int n)
{
    for (int idx = 0; idx < ans.size(); idx++)
    {
        cout << "Solution " << idx + 1 << ":\n";
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << (ans[idx][i][j] ? "Q " : ". ");
            }
            cout << "\n";
        }
        cout << "\n";
    }
    cout << "Total solutions: " << ans.size() << "\n";
}

signed main()
{
    int n;
    cout << "Enter the value of N: ";
    cin >> n;

    vector<vector<int>> board(n, vector<int>(n, 0));
    solve(n, board, 0);

    if (ans.empty())
    {
        cout << "No solution exists for N = " << n << "\n";
    }
    else
    {
        printSolutionBoards(n);
    }

    return 0;
}
