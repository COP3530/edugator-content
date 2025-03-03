
## Table of Contents

1. [Introduction](#introduction)
2. [Types of Graphs](#types-of-graphs)
3. [Terminology](#terminology)
4. [Implementation](#implementation)
5. [Traversals](#traversals)
6. [Conclusion](#conclusion)


## Introduction

Graphs are a fundamental data structure in computer science with a wide range of theoretical and practical applications. A graph is an non-linear ordered data structure.

We've already seen a few examples of graphs in previous lessons. For example, trees — acyclic undirected graphs (we'll get into what that means in the next section).

### Definition

A **graph** $`G`$ is a set of vertices (also called nodes) $`V`$ and a set of unordered pairs called edges $`E`$.

![graph](../images/graph-1.png)

In the above example, the vertices are $`V = \{a, b, c, d, e\}`$ and the edges are $`E = \{\{a, b\}, \{b, c\}, \{c, d\}, \{d, e\}\}`$. Note that the edges are unordered pairs, meaning that the edge $`\{a, b\}`$ is the same as the edge $`\{b, a\}`$.

Consider the tree below:

![graph](../images/graph-2.png)

The set of vertices and edges are:

- A. $`V = \{a, b, c, d, e, f, g\},`$ $`E = \{\{a, b\}, \{a, c\}, \{d, c\}\}`$
- B. $`V = \{a, b, c, d\},`$ $`E = \{\{a, b\}, \{a, c\}, \{d, c\}, \{b, c\}\}`$
- C. $`V = \{a, b, c, d\},`$ $`E = \{\{a, b\}, \{c, b\}, \{c, d\}\}`$
- D. $`V = \{a, b, c, d\},`$ $`E = \{\{a, b\}, \{b, c\}\}`$

<details>
<summary>Answer</summary>
C.
</details>

## Types of Graphs

### Undirected Graph

A graph is **undirected** if the edges are a set of *unordered* pairs. This means that if there is an edge between vertices $`a`$ and $`b`$, then there is also an edge between $`b`$ and $`a`$. The edges in an undirected graph are represented visually as lines.

![undirected-graph](../images/undirected-1.png)

### Directed Graph

A graph is **directed** if the edges are a set of *ordered* pairs. Unlike undirected graphs, an edge is an ordered pair $`(v_1, v_2)`$ meaning that there is an connection from $`v_1`$ to $`v_2`$ but not necessarily from $`v_2`$ to $`v_1`$. The edges in a directed grpah are represented as arrows starting from the source vertex and pointing to the destination vertex.

![directed-graph](../images/directed-1.png)

The set of vertices and edges are:

- $`V = \{a, b, c, d, e\}`$
- $`e = \{(a, b), (c, b), (c, a), (d, e)\}`$



## Terminology

Below are a list of common terms used when discussing graphs:

### Vertex (Node)

A single element in a graph.

### Edge

A connection between two vertices.

### Weight

A value assigned to an edge. Edges *only* have weights in weighted graphs. The graph below shows integer values associated with each edge. The notion of weights is important in many graph algorithms such as Dijkstra's algorithm for finding the shortest path between two vertices.

![weighted-graph](../images/weighted-1.png)

### Adjancency

Two vertices $`v_1`$ and $`v_2`$ are **adjacent** if there is an edge between them. If there is an edge between vertices in an undirected graph, then they are adjacent. However, in an undirected graph, if there is an edge from $`v_1`$ to $`v_2`$ but not from $`v_2`$ to $`v_1`$, then $`v_1`$ is adjacent to $`v_2`$ but $`v_2`$ is not adjacent to $`v_1`$.

For example, consider the directed graph below. The vertices $`a`$ is adjacent to $`b`$ but $`b`$ is not adjacent to $`a`$. In the directed graph, however, the the vertices $`a`$ and $`b`$ *are* adjacent.

![undirected-and-directed](../images/undirected-and-directed-1.png)

### Simple Graph

A **simple graph** is a graph with no self-loops or multiple edges between the same pair of vertices. In other words, there is at most one edge between any two vertices and no edge from a vertex to itself.

The graph below is not *simple* because there is a self-loop on vertex $`a`$. and two edges between vertices $`a`$ and $`b`$.

![#not-simple](../images/not-simple-1.png)

### Path

A **path** is a sequence of vertices in which each vertex is adjacent to the next. The length of a path is the number of edges in the path. Consider the graph below, a path highlighted by the green edges is $`a, b, d, f, b`$. Note that path is allowed to revisit vertices such.

![path](../images/path-1.png)


### Simple Path

A **simple path** is a path where *only* the first and last vertex may be the same.

Consider the graph on the left with the path $`a, b, d, f, b`$. This is *not* a simple path because the vertex $`b`$ appears twice but is not the first vertex. The path on the right, $`a, b, c, a`$ *is* a simple path. Although the vertex $`a`$ appears twice, it is the first and last vertex which is acceptable.

![#simple-path](../images/simple-path-1.png)

### Cycle

A **cycle** is a simple path where the first and last vertex are the same.

The graph below has a cycle $`a, b, c, a`$.

![#cylcle](../images/cycle-1.png)

### Connected

Two vertices $`v_1`$ and $`v_2`$ are **connected** if there exists a path between them.

The vertices $`a`$ and $`b`$ are connected in the graph below because the path $`a, b`$ exists. However, the vertices $`a`$ and $`e`$ are not connected because there is no path between them.

![connected](../images/connected-1.png)

### Connected Graph

A graph is **connected** if every pair of vertices is connected.

For example, the graph on the left is connected because there is a path between every pair of vertices. However there exists no path between $`a`$ and $`e`$ in the graph on the right, thus, it is disconnected.

![connected-graph](../images/connected-disconnected.png)


## Implementation

Talk about the most popular implementations of graphs: adjancency lists, adjacency matrices, and edge lists. Discuss the pros and cons of each.

## Traversals

Discuss the most common graph traversal algorithms: Depth-First Search (DFS) and Breadth-First Search (BFS). Explain how they work, their time and space complexity, and their use cases.

## Conclusion
