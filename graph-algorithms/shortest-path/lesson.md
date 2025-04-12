# Graph Algorithms: Shortest Path Algorithms

**Author:** *Brian Magnuson*

In this 3-part series of lessons, we will explore various graph algorithms and their applications.
In this lesson, we will focus on shortest path algorithms.

We will cover the following topics:
- Introduction to shortest path algorithms
- Unweighted graphs: breadth-first search (BFS)
- Graphs with positive weights: Dijkstra's algorithm
- Graphs with negative weights and no negative cycles: Bellman-Ford algorithm

We will also be describing the time complexities of these algorithms. However, please note that, due to the nature of graphs and the relationships between the number of vertices and edges, these time complexities may be written in different ways.
In other words, do not treat the stated time complexities as absolute. They are meant to give you an idea of the algorithm's performance.

# Introduction to Shortest Path Algorithms

Shortest path algorithms are used to find the shortest path between two nodes in a graph.

Finding the shortest path has a variety of applications, such as:
- Routing in computer networks
- Navigation in GPS systems
- Finding the shortest path in a social network

There are several algorithms to solve this problem.
The algorithm we use may depend on the type of graph we are working with.

These algorithms generally work with both directed and undirected graphs. 
Undirected graphs may be treated as directed graphs by considering each edge as two directed edges.

# Unweighted Graphs: Breadth-First Search (BFS)

In an unweighted graph, we assume that each edge has the same weight/distance/cost.
In other words, finding the shortest path is a matter of finding the path with the fewest edges.
For this kind of graph, we can simply use a breadth-first search (BFS) algorithm.

![BFS algorithm to find shortest S-T path in unweighted graph](images-ppt.gif)

In the above example, we start by performing BFS, marking visited edges and vertices yellow. Edges traversed that point to visited vertices are marked red.
Once the target vertex is reached, we can use a predecessor table to reconstruct the path (in green).

If we only need to find the length of the shortest path, we can just count the number of steps in the BFS without using a predecessor table.

```
func reconstruct_path(predecessors, start, end):
    path = []
    current = end
    while current is not None:
        path.append(current)
        current = predecessors[current]
    path.reverse()
    return path

func bfs(graph, start, end):
    queue = [start]
    visited = set()
    predecessors = {start: None}

    while queue:
        node = queue.pop(0)
        if node == end:
            return reconstruct_path(predecessors, start, end)
        visited.add(node)

        for neighbor in graph[node]:
            if neighbor not in visited and neighbor not in queue:
                queue.enqueue(neighbor)
                predecessors[neighbor] = node

    return None
```

Assuming that set and dictionary operations are O(1), the BFS algorithm runs in O(V + E) time, where V is the number of vertices and E is the number of edges.

# Graphs With Positive Weights: Dijkstra's Algorithm

In a graph with positive weights, the shortest path is the path with the lowest total weight.
Dijkstra's algorithm is a popular algorithm for finding the shortest path in such graphs.

Dijkstra's algorithm, named after Edsger W. Dijkstra, works using a concept called "edge relaxation".
When we "relax" an edge, we check if the path to a vertex through that edge is shorter than any previously found path.

![Edge relaxation in a small graph.](images-ppt-2.gif)

In the above example, we track the current known distance to each vertex.
The source vertex 's' is initialized with a distance of 0, and all other vertices are initialized with infinity.
When we relax the edge with weight 8, we compare the current distance to the previous node (0 in this case) plus the edge weight (8) to the current distance to the target node (infinity).
Since 0 + 8 < infinity, we update the distance to the target node to 8.

In theory, if we keep relaxing edges, we will eventually reach a point where all distances are at their minimum.
However, this is not efficient in practice.
If the graph only has positive edge weights, we can strategically relax edges to find the shortest path.

Dijkstra's algorithm works like this:
1. Create a dictionary to store the shortest distance to each vertex and the predecessor of each vertex.
2. Initialize the distance to the source vertex to 0 and all other vertices to infinity.
3. Pick an unvisited vertex with the smallest distance and relax all its edges.
4. If the distance to a neighbor is updated from 3, update the predecessor.
4. Mark the chosen vertex as visited.
5. Repeat until all vertices are visited.
6. Use the predecessor table to reconstruct the shortest path.

We sometimes describe Dijkstra's algorithm as a **greedy algorithm** because it always picks the unvisited vertex with the smallest distance. Greedy algorithms do not always yield the optimal solution, but in this case, it does.
The exact proof for this is beyond the scope of this lesson.

Using Dijkstra's algorithm, we can find the shortest distances to all other nodes in a graph.
However, if our only concern is finding the shortest path to the target node,
we can stop once we pick the target node.

![Dijkstra's algorithm in action.](images-ppt-3.gif)

In the above example, we mark visited nodes yellow. We relax all outgoing edges from the current node, updating our table of distances and predecessors.
Once we reach the target node, we can use the predecessor table to reconstruct the shortest path.

We always pick the unvisited node with the smallest distance.
We can do this efficiently using a priority queue.

```
func dijkstra(graph, start, end):
    distances = {node: float('inf') for node in graph}
    predecessors = {node: None for node in graph}
    distances[start] = 0
    visited = set()
    queue = [(0, start)]

    while queue:
        current_distance, current_node = heapq.heappop(queue)
        if current_node in visited:
            continue
        visited.add(current_node)

        if current_node == end:
            return reconstruct_path(predecessors, start, end)

        for neighbor, edge_weight in graph[current_node].items():
            if neighbor not in visited:
                new_distance = current_distance + edge_weight
                if new_distance < distances[neighbor]:
                    distances[neighbor] = new_distance
                    predecessors[neighbor] = current_node
                    heapq.heappush(queue, (new_distance, neighbor))

    return None
```

Note that in the above code, a node may be pushed to the queue multiple times.
However, if the node is already visited, we pop it from the queue and ignore it.

Without priority queues, the algorithm runs in O(V^2) time, where V is the number of vertices, assuming that set and dictionary operations are O(1) and the graph is simple.

Picking the node with the smallest distance taks O(V) time. Visiting each node takes O(V) time. Additionally, every edge is relaxed once, taking O(E) time.
This brings the worst case time complexity to O(V^2 + E). Since the graph is simple, E is at most V^2, so we can simplify this to O(V^2).

With priority queues, the algorithm runs in O((V + E) log V) time, where V is the number of vertices and E is the number of edges. If we assume that V is upper bounded by E, we can alternatively write the time complexity as O(E log V).

Extracting the node with the smallest distance takes O(log V) time (since heap properties need to be maintained). This is done for every node, so this takes O(V log V) time.
Each time an edge is relaxed, we push the neighbor to the queue, which takes O(log V) time. This is done for every edge, so this takes O(E log V) time.
This brings the worst case time complexity to O((V + E) log V).

# Graphs With Negative Weights and No Negative Cycles: Bellman-Ford Algorithm

Sometimes, we may have a graph with negative edge weights.
Negative edge weights may not seem intuitive at first, but they can be useful in certain applications such as:
- Financial networks
- Game theory
- Network flow problems

![Example graph with negative edge weights.](image-1.png)

In a graph with negative edge weights, Dijkstra's algorithm may not work.
In the above example, Dijkstra's algorithm would assume that the shortest path to 'b' is through 's' since it has the smallest distance after the edges from 's' are relaxed. However, the actual shortest path to 'b' is through 'a'. Thus, Dijkstra's algorithm fails to find the shortest path.

Assuming that the graph has no negative cycles, we can use the Bellman-Ford algorithm, named after Richard Bellman and Lester Ford, Jr.

A **negative weight cycle** is a cycle in the graph where the sum of the edge weights is negative.
If a graph has a negative weight cycle, the shortest path cannot be determined since we can keep traversing the cycle to reduce the path length indefinitely.

![Example of a negative weight cycle in a graph.](image.png)

The Bellman-Ford algorithm takes longer to run than Dijkstra's algorithm, but is simpler to implement. It can also be used even if there are no negative edge weights.

1. Create a dictionary to store the shortest distance to each vertex and the predecessor of each vertex.
2. Initialize the distance to the source vertex to 0 and all other vertices to infinity.
3. Relax ALL edges in the graph.
4. Repeat step 3 for V - 1 times, where V is the number of vertices.
5. Relax ALL edges in the graph one more time.
6. If a vertex's distance is updated from step 5, the graph has a negative cycle. The shortest path cannot be determined.
7. Else, use the predecessor table to reconstruct the shortest path.

![Bellman-Ford algorithm in action.](images-ppt-4.gif)

In the above example, we have 4 nodes. Thus, we run for 4 iterations total, relaxing all edges in the graph. The last iteration is used to check for negative cycles.
In this case, there are no updates in the last iteration, so the graph has no negative cycles.

```
func bellman_ford(graph, start, end):
    distances = {node: float('inf') for node in graph}
    predecessors = {node: None for node in graph}
    distances[start] = 0

    for _ in range(len(graph) - 1):
        for node in graph:
            for neighbor, edge_weight in graph[node].items():
                if distances[node] + edge_weight < distances[neighbor]:
                    distances[neighbor] = distances[node] + edge_weight
                    predecessors[neighbor] = node

    for node in graph:
        for neighbor, edge_weight in graph[node].items():
            if distances[node] + edge_weight < distances[neighbor]:
                return "Graph has a negative cycle"

    return reconstruct_path(predecessors, start, end)
```

The Bellman-Ford algorithm runs in O(VE) time, where V is the number of vertices and E is the number of edges, assuming that set and dictionary operations are O(1) and the graph is simple.
Relaxing all edges takes O(E) time. This is done for V - 1 iterations, so this takes O(VE) time.
The last iteration takes an additional O(E) time.
Thus, the worst case time complexity is O(VE).

The algorithm may be optimized by skipping over vertices whose distances have not changed in the previous iteration.
This variation of the algorithm was introduced by Edward F. Moore in 1959 and is referred to as the *Bellman-Ford-Moore algorithm*.

------

![Directed, weighted graph with edge list: (s, a, 9), (s, b, 2), (s, d, 1), (a, d, 4), (b, c, 3), (b, e, 5), (c, e, 2), (d, c, 3), (d, e, 6), (e, a, 4)](image-4.png)

Using Dijkstra's algorithm, calculate the shortest distances from 's' to all other nodes and each node's predecessor.
Which of the following shows the correct output?
- a: (9, s), b: (2, s), c: (5, b), d: (1, s), e: (7, b)
- a: (2, e), b: (2, s), c: (3, d), d: (1, s), e: (6, d)
- a: (8, e), b: (2, s), c: (5, b), d: (1, s), e: (6, d)
- a: (9, s), b: (2, s), c: (4, d), d: (1, s), e: (7, d)
- a: (8, e), b: (2, s), c: (4, d), d: (1, s), e: (6, c)

<details>
<summary>Answer</summary>
a: (8, e), b: (2, s), c: (4, d), d: (1, s), e: (6, c)
</details>

------

```
s: 0, None
u: 14, w
v: 16, u
w: 6, s
x: 8, w
```

Consider the above possible output of Dijkstra's algorithm.
What is the weight of the edge from 'w' to 'u' in the graph?
- 6
- 8
- 14
- 16
- This cannot be determined from the given information.

<details>
<summary>Answer</summary>
8
</details>

------

# Conclusion

In this lesson, we covered three shortest path algorithms, their applications, and their time complexities.
In the next lesson, we will explore minimum spanning tree algorithms.

# References

- [COP 3530 Instructional Content](https://github.com/COP3530/Instructional-Content)
- [Wikipedia: Dijkstra's algorithm](https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm)
- [Wikipedia: Bellman-Ford algorithm](https://en.wikipedia.org/wiki/Bellman%E2%80%93Ford_algorithm)

Graphics by Brian Magnuson.

Lesson content written with AI assistance.

This work by Brian Magnuson is licensed under [CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/).

Find a mistake? Open an issue on [GitHub](https://github.com/COP3530/edugator-content/issues)!
