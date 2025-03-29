# Greedy Algorithms

**Author:** *Brian Magnuson*

In this lesson, we will be discussing greedy algorithms, an algorithmic paradigm that solves problems by using the locally optimal choice at each stage with hope of finding the global optimum. To help illustrate this concept, we will explore several classic problems where a greedy approach is applicable.

We will be covering the following:
- Introduction to greedy algorithms
- Coin change problem
- Activity selection problem
- Huffman coding
- Bin packing problem

# Introduction to Greedy Algorithms

Imagine you are in a cave. The cave has multiple branching paths, and each path has some amount of money at the end. You want to maximize the amount of money you can collect, but you only have enough time to take one path at each fork.

![Diagram of a person at the root of a tree. The left path has $2 and the right path has $5. All other nodes are hidden.](image.png)

Since you are *greedy*, you decide to take the path that will give you the most money at each fork. You hope that by taking the path with the most money at each fork, you will end up with the most money overall.

![Diagram of a person taking the right path. Two more nodes are revealed: the left path has $4 and the right path has $3.](image-1.png)

A **greedy algorithm** is any algorithm that makes the locally optimal choice at each stage with the hope of finding the global optimum. In this case, you are making the locally optimal choice by taking the path with the most money at each fork.

![Diagram of a person taking the left path. They have finished their run with $9.](image-2.png)

Greedy algorithms have a few characteristics:
- They make a series of choices, each of which looks best at the moment.
- They do not look ahead to see if the current choice will lead to a better solution in the future.
- They do not backtrack to try other options if the current choice does not lead to the best solution.
- They tend to run faster than other algorithms because they do not explore all possible solutions.

As you may have guessed, the greedy approach does not always lead to the optimal solution. In our cave example, if we had more time to explore the paths, we might have found a path that led to more money overall.

![Diagram showing an alternative path in the tree that yields $12.](image-3.png)

The "greedy solution" may not always be optimal, but for certain problems, it can be a good approximation. Additionally, as mentioned before, greedy algorithms tend to run faster than other algorithms because they do not explore all possible solutions.

In the next sections, we will explore several classic problems where a greedy approach is applicable and see how they can be solved using this algorithmic paradigm.

# Coin Change Problem

The coin change problem is a classic example of a problem where the greedy approach usually leads to an optimal solution. It's a simple problem with which most people are familiar:

- Given a set of coin denominations and a target amount, find the minimum number of coins needed to make that amount.

For example, suppose we have the following coin denominations:

![4 coins, each with a certain value: 1 cent, 5 cents, 10 cents, and 25 cents, respectively.](image-4.png)

And suppose we want to make 68 cents. Think about how you would do this in real life. You would likely start with the largest denomination (the quarter) and work your way down to the smallest denomination (the penny).

To be more explicit, you would follow these steps:
1. Start with the largest denomination.
2. If the denomination is less than the remaining amount, move on to the next largest denomination.
3. Otherwise, subtract the denomination from the remaining amount and add it to your total count of coins.
4. Repeat from step 2 until the remaining amount is zero.
5. Return the total count of coins.

![Animation of USD coins being used to make 68 cents.](images-ppt.gif)

This approach is greedy, because at each iteration, we choose the largest denomination that "fits" into the remaining amount, hoping that we can minimize the total number of coins needed.

In the above example, we use the following coins to make 68 cents:
- 2 quarters (50 cents)
- 1 dime (10 cents)
- 1 nickel (5 cents)
- 3 pennies (3 cents)

This gives us a total of 7 coins.

For this example, the greedy solution happens to also be the optimal solution. You can try different combinations of coins, but you will find that no other combination will have fewer than 7 coins.

In fact, for this particular set of coin denominations, the greedy approach will *always* yield the optimal solution for *any* target amount. This is due to a special property of the set of coins.

A currency system is said to be **canonical** if the greedy algorithm always produces an optimal solution for any target amount. The above example was based on the US currency system, which is canonical. Most modern currency systems in the world are canonical.

Let's consider an example where the greedy approach does not yield the optimal solution:

![Coin change problem with 3 coins: 1 cent, 7 cents, and 10 cents. The target is 14 cents. The greedy solution uses 5 coins, but the optimal solution uses only 2 coins.](image-6.png)

In the above example, we use a set of coins with denominations of 1 cent, 7 cents, and 10 cents. The target amount is 14 cents. If we apply the greedy approach, we would first take a 10-cent coin (1 coin), then a 4-cent coin (4 coins), for a total of 5 coins.

However, the optimal solution is to take 2 coins: two 7-cent coins. This shows that the greedy approach does not always yield the optimal solution.

The set of coins is not canonical, because there are target amounts for which the greedy algorithm does not yield the optimal solution.

# Activity Selection Problem

In this next problem, we'll see how a greedy algorithm can lead to an optimal solution, but the algorithm may not be obvious at first glance.

The activity selection problem is a classic optimization problem that can be solved using a greedy approach. The problem is as follows:
- Given a set of activities, each with a start time and an end time, select the maximum number of activities that can be performed by a single person, assuming that a person can only work on one activity at a time.

Let's use an example with the following set of activities:
- A: (0, 4)
- B: (3, 6)
- C: (9, 11)
- D: (5, 8)
- E: (10, 12)
- F: (8, 10)
- G: (4, 10)

We can visualize these activities on a timeline:
![Diagram showing the above activities in a timeline. Some of the activities are overlapping.](image-7.png)

As you can see, some of these activities overlap with each other. The goal is to select the maximum number of non-overlapping activities.

There are a few different greedy approaches to solving this problem:
- At each iteration, select the activity with the shortest *duration* that does not overlap with the previously selected activities.
- At each iteration, select the activity that *starts the earliest* and does not overlap with the previously selected activities.
- At each iteration, select the activity that *ends the earliest* and does not overlap with the previously selected activities.

Let's explore each approach one at a time.

**Shortest Duration Approach**

The intuition behind this approach is that by selecting the shortest activity first, we leave more room for other activities to fit in.

When we order the activities by their duration, we get the following list:
- C: (9, 11) (length 2)
- E: (10, 12) (length 2)
- F: (8, 10) (length 2)
- B: (3, 6) (length 3)
- D: (5, 8) (length 3)
- A: (0, 4) (length 4)
- G: (4, 10) (length 6)

![Diagram showing the above tasks with the shortest tasks on top and the longest tasks on the bottom.](image-8.png)

When using this approach, we end up selecting C and B, which gives us a total of 2 activities. But this obviously isn't the optimal solution. As seen in the diagram, we can select E and F instead of C, giving us an extra activity.

**Earliest Start Approach**

The intuition behind this approach is that by selecting the activity that starts the earliest, we minimize any gaps that might occur between activities, allowing more activities to fit in.

When we order the activities by their start time, we get the following list:
- A: (0, 4)
- B: (3, 6)
- G: (4, 10)
- D: (5, 8)
- F: (8, 10)
- C: (9, 11)
- E: (10, 12)

![Diagram showing the above tasks ordered by their start times.](image-9.png)

When using this approach, we end up selecting A, G, and E, which gives us a total of 3 activities. This leaves no gaps in our schedule. However, we can still do better; we can select D and F instead of G, giving us an extra activity.

**Earliest End Approach**

When we order the activities by their end time, we get the following list:
- A: (0, 4)
- B: (3, 6)
- D: (5, 8)
- F: (8, 10)
- G: (4, 10)
- C: (9, 11)
- E: (10, 12)

![Diagram showing the above tasks ordered by their end times.](image-10.png)

When we use this approach, we end up selecting A, D, F, and E, which gives us a total of 4 activities. This is the optimal solution!

Indeed, the earliest end approach is the correct greedy strategy for solving the activity selection problem. By always selecting the activity that ends the earliest, we leave as much room as possible for future activities, allowing us to maximize the total number of activities selected.
