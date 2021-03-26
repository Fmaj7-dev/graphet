#include "graph.h"
#include <iostream>

Graph::Graph()
:num_nodes_(0)
{}

void Graph::addNode( Node& n )
{
    n.id = num_nodes_++;
    nodes_.push_back(n);
}

void Graph::addLink( const Link& l )
{
    links_.push_back(l);
}

void Graph::addLink( const Node& a, const Node& b, float force )
{
    Link l;
    l.from = a.id;
    l.to = b.id;
    l.force = force;

    addLink(l);
}

void Graph::print()
{
    std::cout<<"Nodes:"<<std::endl;
    for (auto& node: nodes_) 
        std::cout<<node.id<<" "<<node.name<< std::endl;

    std::cout<<"Links:"<<std::endl;
    for (auto& link: links_)
        std::cout<<link.from<<" "<<link.to<<std::endl;
}

void Graph::initRandom()
{ 
    Node a("Alekhine", 0.0f, 0.0f);
    Node b("Barsov", 0.2f, -0.6f);
    Node c("Carlsen", 0.3f, 0.6f);
    Node d("Dimitrov", -0.8, -0.3);

    addNode(a);
    addNode(b);
    addNode(c);
    addNode(d);

    addLink(a, b);
    addLink(b, c);
    addLink(c, d);
    addLink(b, d);
}
