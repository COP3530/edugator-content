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

## Node Relationships

The relationships among nodes in a tree can be described using terminology similar to family relationships. In the following diagram, we'll focus on node 'E' and its relationship with other nodes:

![Diagram showing the different relationships among nodes in a tree.](image-3.png)

A node is said to be an **ancestor** of another node if it is on the path from the root to that node. It can also be defined as all the nodes reachable by traversing upwards from the node. In the above example, 'A' and 'C' are ancestors of 'E'.

The direct predecessor of a node is called its **parent**. 'C' is the parent of 'E'. The parent of a node's parent is that node's **grandparent**. 'A' is the grandparent of 'E'.

The nodes that share a parent with a node are that node's **siblings**. 'D' and 'E' are siblings.

A node is a **descendant** of another node if it is on the path from that node to a leaf. It can also be defined as all the nodes reachable by traversing downwards from the node. In the above example, 'F', 'G', 'H', and 'I' are descendants of 'E'.

The direct successor of a node is called its **child**. 'F' and 'G' are children of 'E'. The child of a node's child is that node's **grandchild**. 'H' and 'I' are grandchildren of 'E'.

The set of a single node and all of its descendants is a **subtree**.

![Diagram showing a tree with root 'A' and two subtrees below 'A'.](image-5.png)

In the above example, 'A' has two children, 'B' and 'C'. 'B' and all of its descendants form one subtree where 'B' is the root. 'C' and all of its descendants form another subtree where 'C' is the root.

## Depth and Height

The **depth** or **level** of a node is the number of edges from the root to that node. The root node is considered to have a depth of 0.

![Diagram showing the different levels in a tree.](image-4.png)

The **height** of a node describes its distance from its deepest leaf. Height can also be used to describe trees and subtrees; the height of a tree is the height of its root node.

![Diagram showing the 0-based height of nodes in a tree.](image-6.png)

Unlike depth, siblings do not necessarily have the same height. As shown in the diagram, 'B' and 'C' are siblings, but 'B' has a height of 1 while 'C' has a height of 0.

In the above example, we specifically use the **0-based** definition of height, which is the number of edges from the node to its deepest leaf. Leaf nodes have a height of 0. In this case, 'A' has a height of 3, 'B' has a height of 1, and 'C' has a height of 0. Null nodes and empty trees are considered to have a height of -1.

There is also a **1-based** definition of height. 
It is the number of nodes from the node to its deepest leaf, counting the node itself. Leaf nodes have a height of 1. Null nodes and empty trees are considered to have a height of 0.
A node's *1-based height* is equivalent to its *0-based height* plus 1.

![Diagram showing the 1-based height of nodes in a tree.](image-7.png)

In your projects, you can choose which definition of height to use as long as you are consistent.

The height of a node can also be defined recursively. The height of a node is the maximum height of its children plus one. The height of a null node is -1 when using the 0-based definition, and 0 when using the 1-based definition.
```
func height(node):
    if node is null:
        return -1  # or 0 for 1-based height
    else:
        return 1 + max(height(node.children[0]), height(node.children[1]), ...)
```

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
