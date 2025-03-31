/**
 * @file 1d-bottom-up.cpp
 * @author Matthew DeGuzman (matthew.deguzman0613@gmail.com)
 * @brief Bottom up implementation of the min cost climbing stairs problem
 * @version 0.1
 * @date 2025-03-31
 *
 * @copyright Copyright (c) 2025
 *
 */
#include <vector>
#include <iostream>

using namespace std;

int minCostClimbingStairs(vector<int> &cost)
{
    vector<int> memo(cost.size() + 2, 0);
    for (int i = cost.size() - 1; i >= 0; --i)
    {
        memo[i] = cost[i] + min(memo[i + 1], memo[i + 2]);
    }
    return min(memo[0], memo[1]);
}

int main()
{
    vector<int> cost = {10, 15, 20};
    int result = minCostClimbingStairs(cost);
    cout << "Result: " << result << endl;
}