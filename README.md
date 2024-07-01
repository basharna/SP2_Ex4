# Tree Data Structure

## Overview
This project implements a generic tree data structure in C++ using templates. It supports various operations like adding nodes, tree traversal (pre-order, post-order, in-order, BFS, DFS), transforming into a minimum heap, and visualization using SFML.

## Classes

### Tree<T, K>
- **Description**: Represents a generic tree with nodes of type `T` and branching factor `K`.
- **Public Methods**:
  - `Tree()`: Constructor to initialize an empty tree.
  - `~Tree()`: Destructor to clear memory.
  - `void add_root(T data)`: Adds a root node with the given data.
  - `void add_sub_node(T parent, T child)`: Adds a child node to a parent node.
  - `void print_tree()`: Prints the tree structure.
  - Iterators for traversal:
    - `begin_pre_order()`, `end_pre_order()`
    - `begin_post_order()`, `end_post_order()`
    - `begin_in_order()`, `end_in_order()`
    - `begin_bfs_scan()`, `end_bfs_scan()`
    - `begin_dfs_scan()`, `end_dfs_scan()`
  - `Iterator myHeap()`: Transforms the tree into a minimum heap.
  - `ostream &operator<<(ostream &os, const Tree<T, K> &tree)`: Draws the tree using SFML for visualization.

### Tree<T, K>::Node
- **Description**: Represents a node in the tree.
- **Attributes**:
  - `T data`: Data stored in the node.
  - `vector<shared_ptr<Node>> children`: Children nodes.
  - `float x`: x position used in GUI.
  - `float y`: y position used in GUI.
- **Methods**:
  - `Node(T data)`: Constructor to initialize a node with data.

### Tree<T, K>::Iterator
- **Description**: Iterator class for tree traversal.
- **Methods**:
  - `T &operator*()`: Dereferences the iterator.
  - `Iterator &operator++()`, `Iterator operator++(int)`: Prefix and postfix increment operators.
  - Various initialization methods for different traversal types.

## Libraries Used
- **SFML**: Used for graphical visualization of the tree structure.
- **C++ Standard Library**: Utilized for data structures (`vector`, `queue`, `stack`) and algorithms (`sort`, `transform`).
- **Doctest**: Used for unit testing.

## Installation and Usage
1. **Dependencies**: Ensure SFML is installed (`sudo apt-get install libsfml-dev` for Linux, or download from [SFML website](https://www.sfml-dev.org/download.php)).
2. **Compile**: Use `make tree` to compile the main program. Use `make test` to compile the UnitTest.
3. **Run**: Execute the main program with `./tree`. Execute the UnitTest with `./test`.

## Example
```cpp
#include "tree.hpp"

int main() {
    Tree<double> tree;
    tree.add_root(1.1);
    tree.add_sub_node(1.1, 1.2);
    tree.add_sub_node(1.1, 1.3);
    tree.add_sub_node(1.2, 1.4);
    tree.add_sub_node(1.2, 1.5);
    tree.add_sub_node(1.3, 1.6);
    std::cout << tree << std::endl; // Print tree structure into GUI
    return 0;
}

```
