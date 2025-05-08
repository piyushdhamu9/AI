#include <iostream>
#include <vector>
using namespace std;

int n;
int solutionCount = 0;
vector<vector<int>> board;
vector<bool> col, diag1, diag2;

void printSolution()
{
    cout << "Solution " << ++solutionCount << ":\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << (board[i][j] ? "Q " : ". ");
        }
        cout << endl;
    }
    cout << endl;

}

void solve(int row)
{
    if (row == n)
    {
        printSolution();
        return;
    }

    for (int c = 0; c < n; c++)
    {
        if (!col[c] && !diag1[row - c + n - 1] && !diag2[row + c])
        {
            board[row][c] = 1;
            col[c] = diag1[row - c + n - 1] = diag2[row + c] = true;

            solve(row + 1);

            board[row][c] = 0;
            col[c] = diag1[row - c + n - 1] = diag2[row + c] = false;
        }
    }
}

int main()
{
    cout << "Enter the value of N: ";
    cin >> n;

    board = vector<vector<int>>(n, vector<int>(n, 0));
    col = vector<bool>(n, false);
    diag1 = vector<bool>(2 * n - 1, false);
    diag2 = vector<bool>(2 * n - 1, false);

    solve(0);

    if (solutionCount == 0)
    {
        cout << "No solution exists for N = " << n << endl;
    }
    else
    {
        cout << "Total solutions found: " << solutionCount << endl;
    }

    return 0;
}
