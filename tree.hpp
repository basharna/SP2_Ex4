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

// Helper function for floating-point types
template <typename U>
typename std::enable_if<std::is_floating_point<U>::value, std::string>::type formatData(const U &data)
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << data; // Set precision to 2 decimal places for floating-point types
    return oss.str();
}

// Helper function for non-floating-point types
template <typename U>
typename std::enable_if<!std::is_floating_point<U>::value, std::string>::type formatData(const U &data)
{
    std::ostringstream oss;
    oss << data; // Default formatting for other types
    return oss.str();
}

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

public:
    Tree() : root(nullptr) {}
    ~Tree() { clear(); }

    // getter
    shared_ptr<Node> getRoot();

    void clear();

    // return size
    size_t size();

    void add_root(T data){
        root = make_shared<Node>(data);
    }
    void add_sub_node(T parent, T child);

    void print_tree();

    // ----------------- Iterators -----------------
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

        // getters
        shared_ptr<Node> &get_current();
    };

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

#include "tree.tpp"

#endif // TREE_HPP