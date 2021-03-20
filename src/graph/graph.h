#ifndef GRAPH_H
#define GRAPH_H

#include <particlesystem.h>

#include <vector>

class Node
{
public:
    size_t id;
};

class Graph
{
public:
    Graph() = default; 
    void add(const Node& n);

    std::vector<Node> nodes_;
    ParticleSystem ps_;
};

#endif