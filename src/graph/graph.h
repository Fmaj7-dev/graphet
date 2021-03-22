#ifndef GRAPH_H
#define GRAPH_H

#include <particlesystem.h>

#include <vector>
#include <string>

class Node
{
public:
    Node(std::string n):name(n){}
    size_t id;
    std::string name;
};

class Link
{
public:
    size_t from;
    size_t to;
    bool directed;
    float force;
};

class Graph
{
public:
    Graph();

    void addNode(Node& node);
    void rmNode(size_t id);

    void addLink(const Link& l);
    void addLink(const Node& a, const Node& b, float force = 1.0f);

    void print();

private:
    size_t num_nodes_;

    std::vector<Node> nodes_;
    std::vector<Link> links_;

    //ParticleSystem ps_;
};

#endif