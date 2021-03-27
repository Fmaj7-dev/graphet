#include "graph.h"
#include "utils/log.h"
#include <iostream>

Graph::Graph(RenderManager& rm)
: dirty_(true),
  rm_(&rm)
{

}

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

size_t Graph::getNumNodes() const
{
    return nodes_.size();
}

size_t Graph::getNumLinks()const
{
    return links_.size();
}

void Graph::initRandom()
{ 
    for (int i=0; i < 100; ++i)
    {
        Node n("", ((float) rand() / float(RAND_MAX)*2)-1, ((float) rand() / float(RAND_MAX)*2)-1);
        n.r = i*12 % 256;
        n.g = i*3 % 256;
        n.b = i*5 % 256;
        addNode(n);

        if (i>0)
            addLink(n, nodes_[i-1]);
    }

    ps_ = rm_->addParticleSystem( getNumNodes() );
    ss_ = rm_->addSegmentSystem( getNumLinks() );

    synchronizeBuffers();

    ps_->init();
    ss_->init();
}

void Graph::synchronizeBuffers()
{
    if (!dirty_)
        return;

    if (ps_->getNumParticles() != getNumNodes())
    {
        etlog("need to recreate node buffers");
        etlog(std::string("num particles: ") + std::to_string(ps_->getNumParticles()));
        etlog(std::string("num nodes: ") + std::to_string(getNumNodes()));
    }

    Particle* particlesA = ps_->getParticles();
    int i = 0;
    for( auto&& node : nodes_ )
    {
        Particle p(node.x, node.y, node.z, node.r, node.g, node.b);
        particlesA[i++] = p;
    }

    

    if(ss_->getNumSegmentPoints() != getNumLinks()*2)
    {
        etlog("need to recreate link buffers");
        etlog(std::string("num segment points: ") + std::to_string(ss_->getNumSegmentPoints()));
        etlog(std::string("num links: ") + std::to_string(getNumLinks()));
    }

    SegmentPoint* segmentPoints = ss_->getSegmentPoints();
    int j = 0;
    for( auto&& link : links_ )
    {
        Node& a = nodes_[link.from];
        Node& b = nodes_[link.to];

        SegmentPoint pa(a.x, a.y, a.z, a.r, a.g, a.b);
        SegmentPoint pb(b.x, b.y, b.z, b.r, b.g, b.b);

        segmentPoints[2*j] = pa;
        segmentPoints[2*j+1] = pb;
        ++j;
    }

    dirty_ = false;
}

void Graph::update()
{
    int i=0;
    for(auto&& n : nodes_)
    {
        n.x += 0.0001 * ((i++)%5 - 2);
    }
        
    dirty_ = true;

    synchronizeBuffers();
}
