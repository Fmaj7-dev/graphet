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
