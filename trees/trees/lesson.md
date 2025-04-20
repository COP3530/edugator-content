# Trees

**Author:** *Brian Magnuson*

In this lesson, we will be covering tree data structures. Trees are a fundamental data structure in computer science used to represent hierarchical relationships between data. 

We will cover the following topics:
- Introduction to Trees
- Tree Terminology
- Tree Types
- Tree Representation
- Tree Traversals
- Binary Search Trees (BSTs)

# Introduction to Trees

A **tree data structure** is a rooted, hierarchical data structure where data is stored in nodes, ane each node can have zero or more child nodes but only one parent node (except the root).

![Example tree data structure. 'A' is the root node. 'A' has two child nodes, 'B' and 'F'. 'B' has three child nodes, 'C', 'D', and 'E'. 'F' has one child node, 'G'. 'G' has two child nodes, 'H' and 'I'. 'C', 'D', 'E', 'H', and 'I' are leaf nodes and have no children.](image.png)

In a tree:
- There is one node called the **root** node, which has no parent.
- All other nodes have one parent node and can have zero or more child nodes.
- There are no cycles in a tree, meaning there is no way to traverse back to a parent node from its child.

Throughout this lesson, we use the term "tree" to refer to the *tree data structure*. In graph theory, a tree is considered a special kind of graph that is connected and acyclic. Trees in graph theory are often undirected, meaning the edges have no direction. You will learn more about graphs in a later lesson.
In this lesson, we will focus on the tree data structure and its properties.

Trees can be used to represent hierarchical data, such as file systems, organizational charts, and family trees. They are also used in various algorithms and data structures, such as binary search trees, heaps, and tries.

The Linux file system can be represented as a tree. The root directory `/` is the root node, and each subdirectory and file is a child node of its parent directory.

![Tree showing some directories from the Filesystem Hierarchy Standard.](image-1.png)

Trees can also be used to represent expressions. This allows computers to evaluate expressions in a way that respects operator precedence and associativity. 
The expression `3 + 4 * 5 * (1 + 2)` can be represented as a tree, where the root node is the `+` operator, and its children are the operands `3` and `4 * 5 * (1 + 2)`.

![Expression tree for the expression 3 + 4 * 5 * (1 + 2)](image-2.png)

Trees can also be used for:
- Decision trees, which are used in machine learning to make decisions based on input data.
- Search trees, which are used to store and retrieve data efficiently.
- Heaps, which are used to implement priority queues.
- Tries, which are used to store strings and perform prefix searches.
- And more!

# Tree Terminology

# Tree Types

# Tree Representation

# Tree Traversals

# Binary Search Trees (BSTs)

# References

- [Cppreference](https://en.cppreference.com/)
- [COP 3530 Instructional Content](https://github.com/COP3530/Instructional-Content)

Graphics by Brian Magnuson.

Lesson content written with AI assistance.

Find a mistake? Open an issue on [GitHub](https://github.com/COP3530/edugator-content/issues)!
