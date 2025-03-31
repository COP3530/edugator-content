/**
 * @file 2d-top-down.cpp
 * @author Matthew DeGuzman (matthew.deguzman0613@gmail.com)
 * @brief Top down implementation of the unique paths problem
 * @version 0.1
 * @date 2025-03-31
 *
 * @copyright Copyright (c) 2025
 *
 */
#include <vector>
#include <iostream>

using namespace std;

int bottomUpHelper(int i, int j, int m, int n, vector<vector<int>> &memo)
{
    if (i == m - 1 && j == n - 1)
        return 1;
    if (i >= m || j >= n)
        return 0;
    if (memo[i][j] != -1)
        return memo[i][j];

    return memo[i][j] = (bottomUpHelper(i + 1, j, m, n, memo) +
                         bottomUpHelper(i, j + 1, m, n, memo));
}

int uniquePaths(int m, int n)
{
    vector<vector<int>> memo(m, vector<int>(n, -1));
    return bottomUpHelper(0, 0, m, n, memo);
}

int main()
{
    int m = 3;
    int n = 7;
    int result = uniquePaths(m, n);
    cout << "Result: " << result << endl;
}