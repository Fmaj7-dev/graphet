#ifndef GRAPH_H
#define GRAPH_H

#include "render/rendermanager.h"
#include "render/segmentsystem.h"
#include "render/particlesystem.h"

#include <vector>
#include <string>

class Node
{
public:
    Node(std::string n, float xc = 0.0f, float yc = 0.0f )
    : name(n), x(xc), y(yc)
    {}
    size_t id;
    std::string name;
    float x;
    float y;
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
    Graph(RenderManager& rm);

    void addNode(Node& node);
    void rmNode(size_t id);

    void addLink(const Link& l);
    void addLink(const Node& a, const Node& b, float force = 1.0f);

    void initRandom();

    void print();

private:
    size_t num_nodes_;

    std::vector<Node> nodes_;
    std::vector<Link> links_;

    //RenderManager& rm_;
    ParticleSystem* ps_;
    SegmentSystem* ss_;
};

#endif