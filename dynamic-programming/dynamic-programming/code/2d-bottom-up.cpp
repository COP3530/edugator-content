/**
 * @file 2d-bottom-up.cpp
 * @author Matthew DeGuzman (matthew.deguzman0613@gmail.com)
 * @brief Bottom up implementation of the unique paths problem
 * @version 0.1
 * @date 2025-03-31
 *
 * @copyright Copyright (c) 2025
 *
 */
#include <vector>
#include <iostream>

using namespace std;

int uniquePaths(int m, int n)
{
    vector<vector<int>> memo(m + 1, vector<int>(n + 1, 0));
    memo[m - 1][n - 1] = 1;
    for (int i = m - 1; i >= 0; --i)
    {
        for (int j = n - 1; j >= 0; --j)
        {
            memo[i][j] += memo[i + 1][j] + memo[i][j + 1];
        }
    }
    return memo[0][0];
}

int main()
{
    int m = 3;
    int n = 7;
    int result = uniquePaths(m, n);
    cout << "Result: " << result << endl;
}