#ifndef TREE_HPP
#define TREE_HPP

#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <string>

using namespace std;

class Node;

template <typename T, size_t K = 2>
class Tree
{
public:
    class Node
    {
    public:
        T data;
        vector<shared_ptr<Node>> children;
        Node(T data) : data(data), children(K, nullptr) {}
    };

private:
    shared_ptr<Node> root;

public:
    Tree() : root(nullptr) {}
    ~Tree() { clear(); }

    void clear();
    
    // return size
    size_t size();

    void add_root(T data);
    void add_sub_node(T parent, T child);

    void print_tree();

    // Iterators
    class Iterator;
    Iterator begin_pre_order();
    Iterator end_pre_order();
    Iterator begin_post_order();
    Iterator end_post_order();
    Iterator begin_in_order();
    Iterator end_in_order();
    Iterator begin_bfs_scan();
    Iterator end_bfs_scan();
    Iterator begin_dfs_scan();
    Iterator end_dfs_scan();
    Iterator begin();
    Iterator end();

    // myHeap() The method transforms a binary tree into a minimum heap tree and returns iterators for the resulting heap.
    Iterator myHeap();

    class Iterator
    {
    private:
        queue<shared_ptr<Node>> tQueue;
        shared_ptr<Node> current;
        void pre_order(shared_ptr<Node> node);
        void post_order(shared_ptr<Node> node);
        void in_order(shared_ptr<Node> node);
        void bfs_scan(shared_ptr<Node> node);
        void dfs_scan(shared_ptr<Node> node);

    public:
        Iterator(shared_ptr<Node> root, const string &type);

        T &operator*();
        Iterator &operator++();
        Iterator operator++(int);
        bool operator==(const Iterator &it) const;
        bool operator!=(const Iterator &it) const;

        void init_pre_order();
        void init_post_order();
        void init_in_order();
        void init_bfs_scan();
        void init_dfs_scan();

        // getters
        shared_ptr<Node> &get_current();
    };
};

#include "tree.tpp"

#endif // TREE_HPP