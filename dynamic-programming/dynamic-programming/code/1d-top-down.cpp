/**
 * @file 1d-top-down.cpp
 * @author Matthew DeGuzman (matthew.deguzman0613@gmail.com)
 * @brief Top down implementation of the min cost climbing stairs problem
 * @version 0.1
 * @date 2025-03-31
 *
 * @copyright Copyright (c) 2025
 *
 */
#include <vector>
#include <iostream>

using namespace std;

int dp(vector<int> &cost, vector<int> &memo, int index)
{
    if (index >= cost.size())
        return 0;
    if (memo[index] != -1)
        return memo[index];
    return memo[index] = cost[index] + min(
                                           dp(cost, memo, index + 1),
                                           dp(cost, memo, index + 2));
}

int minCostClimbingStairs(vector<int> &cost)
{
    vector<int> memo(cost.size(), -1);
    return min(
        dp(cost, memo, 0),
        dp(cost, memo, 1));
}

int main()
{
    vector<int> cost = {10, 15, 20};
    int result = minCostClimbingStairs(cost);
    cout << "Result: " << result << endl;
}