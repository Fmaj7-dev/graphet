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
    : name(n), x(xc), y(yc), z(0)
    {}

    size_t id;

    std::string name;

    float x;
    float y;
    float z;

    char r;
    char g;
    char b;
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
    Graph( RenderManager* rm );

    // node operations
    void addNode( Node& node);
    //void rmNode( size_t id );
    size_t getNumNodes() const;
    std::vector<Node>& getNodes();

    // link operations
    void addLink( const Link& l );
    void addLink( const Node& a, const Node& b, float force = 1.0f );
    size_t getNumLinks() const;
    std::vector<Link>& getLinks();

    void update();

    void initRandom();

    void print();

private:
    void synchronizeBuffers();

    size_t num_nodes_;

    std::vector<Node> nodes_;
    std::vector<Link> links_;

    bool dirty_;

    RenderManager* rm_;
    ParticleSystem* ps_;
    SegmentSystem* ss_;

    class BaseLayout* layout_;
};

#endif
