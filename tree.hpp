/*
ID: 212487144
Email: nbashar4@gmail.com
*/

#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <string>
#include <sstream>
#include <iomanip>
#include <type_traits>
#include <SFML/Graphics.hpp>

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
        float x = 0; // x position for rendering
        float y = 0; // y position for rendering
        Node(T data) : data(data)
        {
            children.clear();
        }
    };

private:
    shared_ptr<Node> root;

    // Helper function for floating-point types
    template <typename U>
    typename enable_if<is_floating_point<U>::value, string>::type formatData(const U &data) const
    {
        ostringstream oss;
        oss << fixed << setprecision(2) << data; // Set precision to 2 decimal places for floating-point types
        return oss.str();
    }

    // Helper function for non-floating-point types
    template <typename U>
    typename enable_if<!is_floating_point<U>::value, string>::type formatData(const U &data) const
    {
        ostringstream oss;
        oss << data; // Default formatting for other types
        return oss.str();
    }

    // Helper function to setup positions using the Reingold-Tilford algorithm
    void setupPositions(shared_ptr<Node> node, int depth, float &nextPos, float siblingDistance) const
    {
        if (!node)
            return;
        for (auto child : node->children)
        {
            setupPositions(child, depth + 1, nextPos, siblingDistance);
        }
        if (node->children.empty())
        {
            node->x = nextPos;
            nextPos += siblingDistance;
        }
        else
        {
            float leftmost = node->children.front()->x;
            float rightmost = node->children.back()->x;
            node->x = (leftmost + rightmost) / 2;
        }
        node->y = (depth + 1) * 100; // Adjust depth factor to change vertical spacing
    }

    // calculate the offset for the root node to be centered and move all nodes accordingly
    void centerTree(shared_ptr<Node> node, float offset) const
    {
        if (!node)
            return;
        node->x += offset;
        for (auto child : node->children)
        {
            centerTree(child, offset);
        }
    }

    // print tree to GUI using SFML
    void drawNodes(sf::RenderWindow &window, shared_ptr<Node> node) const
    {
        if (node == nullptr)
            return;

        sf::CircleShape circle(30);
        circle.setFillColor(sf::Color::White);
        circle.setOutlineThickness(2);
        circle.setOutlineColor(sf::Color::Black);
        circle.setPosition(node->x - circle.getRadius(), node->y - circle.getRadius());
        window.draw(circle);

        sf::Font font;
        font.loadFromFile("/Library/Fonts/Arial Unicode.ttf");
        sf::Text text;
        text.setFont(font);
        text.setString(formatData(node->data));
        text.setCharacterSize(16);
        text.setFillColor(sf::Color::Black);
        text.setPosition(node->x - 15, node->y - 15);
        window.draw(text);

        for (auto child : node->children)
        {
            if (child != nullptr)
            {
                sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(node->x, node->y), sf::Color::Black),
                    sf::Vertex(sf::Vector2f(child->x, child->y), sf::Color::Black)};
                window.draw(line, 2, sf::Lines);
                drawNodes(window, child);
            }
        }
    }

    void drawTree(sf::RenderWindow &window) const
    {
        if (root == nullptr)
            return;
        float nextPos = 400;                   // initial position for the first node
        setupPositions(root, 0, nextPos, 150); // sibling distance
        centerTree(root, window.getSize().x / 2 - root->x);
        drawNodes(window, root);
    }

public:
    Tree() : root(nullptr) {}
    ~Tree() { clear(); }

    // getter
    shared_ptr<Node> getRoot()
    {
        return root;
    }

    void add_root(T data)
    {
        root = make_shared<Node>(data);
    }
    void add_sub_node(T parent, T child)
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
                if (current->children.size() < K)
                {
                    current->children.push_back(make_shared<Node>(child));
                    return;
                }
                else
                {
                    return;
                }
            }

            for (auto child : current->children)
            {
                q.push(child);
            }
        }
    }

    void print_tree()
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
            for (auto child : current->children)
            {
                cout << child->data << " ";
                q.push(child);
            }
            cout << endl;
        }
    }

    void clear()
    {
        root = nullptr;
    }

    // return size
    size_t size()
    {
        size_t count = 0;
        for (auto it = begin_dfs_scan(); it != end_dfs_scan(); ++it)
        {
            count++;
        }
        return count;
    }

    // ----------------- Iterators -----------------
    class Iterator;
    Iterator begin_pre_order()
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
    Iterator end_pre_order()
    {
        if (K == 2)
        {
            return Iterator(nullptr, "pre_order");
        }
        else
            return Iterator(nullptr, "dfs_scan");
    }
    Iterator begin_post_order()
    {
        if (K == 2)
            return Iterator(root, "post_order");
        else
            return Iterator(root, "dfs_scan");
    }
    Iterator end_post_order()
    {

        if (K == 2)
            return Iterator(nullptr, "post_order");
        else
            return Iterator(nullptr, "dfs_scan");
    }
    Iterator begin_in_order()
    {
        if (K == 2)
            return Iterator(root, "in_order");
        else
            return Iterator(root, "dfs_scan");
    }
    Iterator end_in_order()
    {
        if (K == 2)
            return Iterator(nullptr, "in_order");
        else
            return Iterator(nullptr, "dfs_scan");
    }
    Iterator begin_bfs_scan()
    {
        return Iterator(root, "bfs_scan");
    }
    Iterator end_bfs_scan()
    {
        return Iterator(nullptr, "bfs_scan");
    }
    Iterator begin_dfs_scan()
    {
        return Iterator(root, "dfs_scan");
    }
    Iterator end_dfs_scan()
    {
        return Iterator(nullptr, "dfs_scan");
    }
    Iterator begin()
    {
        return begin_bfs_scan();
    }
    Iterator end()
    {
        return end_bfs_scan();
    }

    // myHeap() The method transforms a binary tree into a minimum heap tree and returns iterators for the resulting heap.
    Iterator myHeap()
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
            nodes[i]->children.clear();
            nodes[i]->children.push_back((2 * i + 1 < nodes.size()) ? nodes[2 * i + 1] : nullptr);
            nodes[i]->children.push_back((2 * i + 2 < nodes.size()) ? nodes[2 * i + 2] : nullptr);
        }
        root = nodes[0];

        return begin_bfs_scan();
    }

    class Iterator
    {
    private:
        queue<shared_ptr<Node>> tQueue;
        shared_ptr<Node> current;
        void pre_order(shared_ptr<Node> node)
        {
            if (!node)
            {
                return;
            }

            tQueue.push(node);

            if (node->children.empty())
            {
                return;
            }

            for (size_t i = 0; i < node->children.size(); i++)
            {
                pre_order(node->children[i]);
            }
        }
        void post_order(shared_ptr<Node> node)
        {
            if (!node)
            {
                return;
            }

            for (auto child : node->children)
            {
                post_order(child);
            }
            tQueue.push(node);
        }
        void in_order(shared_ptr<Node> node)
        {
            if (!node)
                return;

            if (node->children.size() > 0)
                in_order(node->children[0]);
            tQueue.push(node);
            if (node->children.size() > 1)
                in_order(node->children[1]);
        }
        void bfs_scan(shared_ptr<Node> node)
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
        void dfs_scan(shared_ptr<Node> node)
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

    public:
        Iterator(shared_ptr<Node> root, const string &type)
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

        T &operator*()
        {
            return current->data;
        }
        Iterator &operator++()
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
        Iterator operator++(int)
        {
            Iterator it = *this;
            ++(*this);
            return it;
        }
        bool operator==(const Iterator &it) const
        {
            return current == it.current;
        }
        bool operator!=(const Iterator &it) const
        {
            return current != it.current;
        }

        // getters
        shared_ptr<Node> &get_current()
        {
            return current;
        }
    };

    // Overloaded operator for outputting tree to ostream
    friend ostream &operator<<(ostream &os, const Tree<T, K> &tree)
    {
        sf::RenderWindow window(sf::VideoMode(800, 600), "Tree");
        sf::View view(sf::FloatRect(0.f, 0.f, window.getSize().x, window.getSize().y));
        window.setView(view);

        sf::Vector2i lastMousePos;

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                switch (event.type)
                {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::Resized:
                {
                    // Adjust the view to the new size of the window
                    sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                    window.setView(sf::View(visibleArea));
                    break;
                }
                case sf::Event::MouseWheelScrolled:
                {
                    if (event.mouseWheelScroll.delta > 0)
                        view.zoom(0.9f); // Zoom in
                    else if (event.mouseWheelScroll.delta < 0)
                        view.zoom(1.1f); // Zoom out
                    window.setView(view);
                    break;
                }
                case sf::Event::MouseButtonPressed:
                {
                    if (event.mouseButton.button == sf::Mouse::Right)
                    {
                        // Recenter view to initial position
                        view.setCenter(window.getSize().x / 2.f, window.getSize().y / 2.f);
                        window.setView(view);
                    }
                    else if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        // Store current mouse position for dragging
                        lastMousePos = sf::Mouse::getPosition(window);
                    }
                    break;
                }
                case sf::Event::MouseButtonReleased:
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        // Clear last mouse position after dragging
                        lastMousePos = sf::Vector2i(0, 0);
                    }
                    break;
                }
                case sf::Event::MouseMoved:
                {
                    // Handle dragging view with left mouse button
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        sf::Vector2i currentMousePos = sf::Mouse::getPosition(window);
                        sf::Vector2f delta = window.mapPixelToCoords(lastMousePos) - window.mapPixelToCoords(currentMousePos);
                        view.move(delta);
                        window.setView(view);
                        lastMousePos = currentMousePos;
                    }
                    break;
                }
                default:
                    break;
                }
            }

            window.clear(sf::Color::White);
            tree.drawTree(window);
            window.display();
        }

        return os;
    }
};

#endif // TREE_HPP