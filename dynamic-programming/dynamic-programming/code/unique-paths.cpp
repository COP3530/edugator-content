/**
 * @file unique-paths.cpp
 * @author Matthew DeGuzman (matthew.deguzman0613@gmail.com)
 * @brief All implementations of the unique paths problem
 * @version 0.1
 * @date 2025-03-31
 *
 * @copyright Copyright (c) 2025
 *
 */
#include <iostream>
#include <vector>

using namespace std;

void bruteForce(int m, int n, int i, int j, int &total) {
  if (i == m - 1 && j == n - 1) {
    total++;
    return;
  }

  if (i >= m || j >= n)
    return;

  bruteForce(m, n, i + 1, j, total); // Explore down
  bruteForce(m, n, i, j + 1, total); // Explore right
}

int topDownHelper(int i, int j, int m, int n, vector<vector<int>> &memo) {
  if (i == m - 1 && j == n - 1)
    return 1;
  if (i >= m || j >= n)
    return 0;
  if (memo[i][j] != -1)
    return memo[i][j];

  return memo[i][j] = (topDownHelper(i + 1, j, m, n, memo) + // move down
                       topDownHelper(i, j + 1, m, n, memo)   // move right
         );
}

int topDown(int m, int n) {
  vector<vector<int>> memo(m, vector<int>(n, -1));
  return topDownHelper(0, 0, m, n, memo);
}

int bottomUp(int m, int n) {
  vector<vector<int>> memo(m + 1, vector<int>(n + 1, 0));
  memo[m - 1][n - 1] = 1;
  for (int i = m - 1; i >= 0; --i) {
    for (int j = n - 1; j >= 0; --j) {
      memo[i][j] += memo[i + 1][j] + memo[i][j + 1];
    }
  }
  return memo[0][0];
}

int main() {
  int m = 3;
  int n = 7;
  int result = bottomUp(m, n);
  cout << "Result: " << result << endl;
}