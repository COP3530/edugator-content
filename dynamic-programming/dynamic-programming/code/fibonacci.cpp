/**
 * @file fibonacci.cpp
 * @author Matthew DeGuzman (matthew.deguzman0613@gmail.com)
 * @brief Naive implementation of the fibonacci sequence
 * @version 0.1
 * @date 2025-03-31
 *
 * @copyright Copyright (c) 2025
 */
#include <iostream>

using namespace std;

int fib(int n, int &steps)
{
    steps++;
    if (n == 0)
        return 0;
    else if (n == 1)
        return 1;
    return fib(n - 1, steps) + fib(n - 2, steps);
}

int main()
{
    int steps = 0;
    int result = fib(40, steps);
    cout << "Result: " << result << endl;
    cout << "Steps: " << steps << endl;
}