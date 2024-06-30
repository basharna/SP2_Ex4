#include "tree.hpp"

template <typename T, size_t K>
void Tree<T, K>::add_root(T data)
{
    root = make_shared<Node>(data);
}

template <typename T, size_t K>
void Tree<T, K>::add_sub_node(T parent, T child)
{
    if (!root)
        return;

    queue<shared_ptr<Node>> q;
    q.push(root);

    while (!q.empty())
    {
        shared_ptr<Node> current = q.front();
        q.pop();

        if (current->data == parent)
        {
            for (size_t i = 0; i < K; i++)
            {
                if (!current->children[i])
                {
                    current->children[i] = make_shared<Node>(child);
                    return;
                }
            }
        }

        for (size_t i = 0; i < K; i++)
        {
            if (current->children[i])
                q.push(current->children[i]);
        }
    }
}

template <typename T, size_t K>
void Tree<T, K>::clear()
{
    root = nullptr;
}

template <typename T, size_t K>
void Tree<T, K>::print_tree()
{
    if (!root)
        return;

    queue<shared_ptr<Node>> q;
    q.push(root);

    while (!q.empty())
    {
        shared_ptr<Node> current = q.front();
        q.pop();

        cout << current->data << ": ";
        for (size_t i = 0; i < K; i++)
        {
            if (current->children[i])
            {
                cout << current->children[i]->data << " ";
                q.push(current->children[i]);
            }
        }
        cout << endl;
    }
}

// Iterators
template <typename T, size_t K>
Tree<T, K>::Iterator::Iterator(shared_ptr<Node> root, const string &type)
{
    if (type == "pre_order")
        pre_order(root);
    else if (type == "post_order")
        post_order(root);
    else if (type == "in_order")
        in_order(root);
    else if (type == "bfs_scan")
        bfs_scan(root);
    else if (type == "dfs_scan")
        dfs_scan(root);

    if (!tQueue.empty())
    {
        current = tQueue.front();
        tQueue.pop();
    }
    else
    {
        current = nullptr;
    }
}

template <typename T, size_t K>
T &Tree<T, K>::Iterator::operator*()
{
    return current->data;
}

template <typename T, size_t K>
typename Tree<T, K>::Iterator &Tree<T, K>::Iterator::operator++()
{
    if (!tQueue.empty())
    {
        current = tQueue.front();
        tQueue.pop();
    }
    else
    {
        current = nullptr;
    }
    return *this;
}

template <typename T, size_t K>
typename Tree<T, K>::Iterator Tree<T, K>::Iterator::operator++(int)
{
    Iterator it = *this;
    ++(*this);
    return it;
}

template <typename T, size_t K>
bool Tree<T, K>::Iterator::operator==(const Iterator &it) const
{
    return current == it.current;
}

template <typename T, size_t K>
bool Tree<T, K>::Iterator::operator!=(const Iterator &it) const
{
    return current != it.current;
}

template <typename T, size_t K>
void Tree<T, K>::Iterator::pre_order(shared_ptr<Node> node)
{
    if (!node)
    {
        return;
    }

    tQueue.push(node);
    pre_order(node->children[0]);
    pre_order(node->children[1]);
}

template <typename T, size_t K>
void Tree<T, K>::Iterator::post_order(shared_ptr<Node> node)
{
    if (!node)
    {
        return;
    }

    post_order(node->children[0]);
    post_order(node->children[1]);
    tQueue.push(node);
}

template <typename T, size_t K>
void Tree<T, K>::Iterator::in_order(shared_ptr<Node> node)
{
    if (!node)
        return;

    in_order(node->children[0]);
    tQueue.push(node);
    in_order(node->children[1]);
}

template <typename T, size_t K>
void Tree<T, K>::Iterator::bfs_scan(shared_ptr<Node> node)
{
    if (!node)
        return;

    queue<shared_ptr<Node>> q;
    q.push(node);

    while (!q.empty())
    {
        shared_ptr<Node> current = q.front();
        q.pop();

        tQueue.push(current);

        for (size_t i = 0; i < current->children.size(); i++)
        {
            if (current->children[i])
                q.push(current->children[i]);
        }
    }
}

template <typename T, size_t K>
void Tree<T, K>::Iterator::dfs_scan(shared_ptr<Node> node)
{
    if (!node)
        return;

    tQueue.push(node);
    for (size_t i = 0; i < node->children.size(); i++)
    {
        dfs_scan(node->children[i]);
    }

    return;
}

template <typename T, size_t K>
void Tree<T, K>::Iterator::init_pre_order()
{
    pre_order(current);
}

template <typename T, size_t K>
void Tree<T, K>::Iterator::init_post_order()
{
    post_order(current);
}

template <typename T, size_t K>
void Tree<T, K>::Iterator::init_in_order()
{
    in_order(current);
}

template <typename T, size_t K>
void Tree<T, K>::Iterator::init_bfs_scan()
{
    bfs_scan(current);
}

template <typename T, size_t K>
void Tree<T, K>::Iterator::init_dfs_scan()
{
    dfs_scan(current);
}

template <typename T, size_t K>
shared_ptr<typename Tree<T, K>::Node> &Tree<T, K>::Iterator::get_current()
{
    return current;
}

template <typename T, size_t K>
size_t Tree<T, K>::size()
{
    size_t count = 0;
    for (auto it = begin_dfs_scan(); it != end_dfs_scan(); ++it)
    {
        count++;
    }
    return count;
}

template <typename T, size_t K>
typename Tree<T, K>::Iterator Tree<T, K>::begin_pre_order()
{
    if (K == 2)
    {
        return Iterator(root, "pre_order");
    }
    else
    {
        return Iterator(root, "dfs_scan");
    }
}

template <typename T, size_t K>
typename Tree<T, K>::Iterator Tree<T, K>::end_pre_order()
{
    if (K == 2)
        return Iterator(nullptr, "pre_order");
    else
        return Iterator(nullptr, "dfs_scan");
}

template <typename T, size_t K>
typename Tree<T, K>::Iterator Tree<T, K>::begin_post_order()
{
    if (K == 2)
        return Iterator(root, "post_order");
    else
        return Iterator(root, "dfs_scan");
}

template <typename T, size_t K>
typename Tree<T, K>::Iterator Tree<T, K>::end_post_order()
{
    if (K == 2)
        return Iterator(nullptr, "post_order");
    else
        return Iterator(nullptr, "dfs_scan");
}

template <typename T, size_t K>
typename Tree<T, K>::Iterator Tree<T, K>::begin_in_order()
{
    if (K == 2)
        return Iterator(root, "in_order");
    else
        return Iterator(root, "dfs_scan");
}

template <typename T, size_t K>
typename Tree<T, K>::Iterator Tree<T, K>::end_in_order()
{
    if (K == 2)
        return Iterator(nullptr, "in_order");
    else
        return Iterator(nullptr, "dfs_scan");
}

template <typename T, size_t K>
typename Tree<T, K>::Iterator Tree<T, K>::begin_bfs_scan()
{
    return Iterator(root, "bfs_scan");
}

template <typename T, size_t K>
typename Tree<T, K>::Iterator Tree<T, K>::end_bfs_scan()
{
    return Iterator(nullptr, "bfs_scan");
}

template <typename T, size_t K>
typename Tree<T, K>::Iterator Tree<T, K>::begin_dfs_scan()
{
    return Iterator(root, "dfs_scan");
}

template <typename T, size_t K>
typename Tree<T, K>::Iterator Tree<T, K>::end_dfs_scan()
{
    return Iterator(nullptr, "dfs_scan");
}

template <typename T, size_t K>
typename Tree<T, K>::Iterator Tree<T, K>::begin()
{
    return begin_bfs_scan();
}

template <typename T, size_t K>
typename Tree<T, K>::Iterator Tree<T, K>::end()
{
    return end_bfs_scan();
}

template <typename T, size_t K>
typename Tree<T, K>::Iterator Tree<T, K>::myHeap()
{
    if (!root || K != 2)
        return end_dfs_scan();

    // collect all nodes in a vector
    vector<shared_ptr<Node>> nodes;
    for (auto it = begin_dfs_scan(); it != end_dfs_scan(); ++it)
    {
        nodes.push_back(it.get_current());
    }

    // sort the vector in ascending order
    sort(nodes.begin(), nodes.end(), [](shared_ptr<Node> a, shared_ptr<Node> b)
         { return a->data < b->data; });

    // transform the sorted vector into a minimum heap tree
    for (size_t i = 0; i < nodes.size(); i++)
    {
        nodes[i]->children[0] = (2 * i + 1 < nodes.size()) ? nodes[2 * i + 1] : nullptr;
        nodes[i]->children[1] = (2 * i + 2 < nodes.size()) ? nodes[2 * i + 2] : nullptr;
    }

    root = nodes[0];

    return begin_bfs_scan();
}
