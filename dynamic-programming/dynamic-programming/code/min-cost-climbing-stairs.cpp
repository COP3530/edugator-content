/**
 * @file min-cost-climbing-stairs.cpp
 * @author Matthew DeGuzman (matthew.deguzman0613@gmail.com)
 * @brief All implementations of the min cost climbing stairs problem
 * @version 0.1
 * @date 2025-03-31
 *
 * @copyright Copyright (c) 2025
 *
 */
#include <iostream>
#include <vector>

using namespace std;

int bruteForce(vector<int> &cost, int step) {
  if (step >= cost.size())
    return 0;
  return cost[step] + min(bruteForce(cost, step + 1), bruteForce(cost, step + 2));
}

int topDownHelper(vector<int> &cost, vector<int> &memo, int step) {
  if (step >= cost.size())
    return 0;

  // Previously calculated result
  if (memo[step] != -1)
    return memo[step];

  // Calculate cost
  return memo[step] =
             cost[step] + min(topDownHelper(cost, memo, step + 1), // Visit next step
                              topDownHelper(cost, memo, step + 2)  // Skip a step
                          );
}

int topDown(vector<int> &cost) {
  vector<int> memo(cost.size(), -1);
  return min(topDownHelper(cost, memo, 0), topDownHelper(cost, memo, 1));
}

int bottomUp(vector<int> &cost) {
  vector<int> memo(cost.size() + 2, 0);
  for (int i = cost.size() - 1; i >= 0; --i) {
    memo[i] = cost[i] + min(memo[i + 1], memo[i + 2]);
  }
  return min(memo[0], memo[1]);
}

int main() {
  vector<int> cost = {10, 15, 20};
  int result = bottomUp(cost);
  cout << "Result: " << result << endl;
}