#include "graph.h"
#include "utils/log.h"

#include "testlayout.h"
#include "forceatlaslayout.h"

Graph::Graph(RenderManager* rm)
: num_nodes_(0),
  dirty_(true),
  rm_(rm),
  ps_(nullptr),
  ss_(nullptr),
  //layout_(new TestLayout(this))
  layout_(new ForceAtlasLayout(this))
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
        std::cout<<node.id<<": "<<node.name<< node.x<<", "<<node.y<<", "<<node.z<<std::endl;

    std::cout<<"Links:"<<std::endl;
    for (auto& link: links_)
        std::cout<<link.from<<" "<<link.to<<std::endl;
}

size_t Graph::getNumNodes() const
{
    return nodes_.size();
}

std::vector<Node>& Graph::getNodes()
{
    return nodes_;
}

std::vector<Link>& Graph::getLinks()
{
    return links_;
}

size_t Graph::getNumLinks()const
{
    return links_.size();
}

void Graph::initRandom()
{ 
    #if 1
    for (int i=0; i < 50; ++i)
    {
        Node n("", ((float) rand() / (float(RAND_MAX)*1))-0.5f, 
                   ((float) rand() / (float(RAND_MAX)*1))-0.5f,
                   ((float) rand() / (float(RAND_MAX)*1))-0.5f);

        if(i==0)
            n.r=n.g=n.b=(char)255;
        else
        {
            n.r = i*17 % 256;
            n.g = i*63 % 256;
            n.b = i*43 % 256;
        }
        //n.r = n.g = n.b = (char)255;
        addNode(n);

        if (i>0)
            addLink(n, nodes_[i-1]);
        /*if (i%5 == 0 && i > 0)
            addLink(n, nodes_[0]);*/
        
    }
    #else

    Node a("", ((float) rand() / (float(RAND_MAX)*1))-0.5f, ((float) rand() / (float(RAND_MAX)*1))-0.5f);
    Node b("", ((float) rand() / (float(RAND_MAX)*1))-0.5f, ((float) rand() / (float(RAND_MAX)*1))-0.5f);
    Node c("", ((float) rand() / (float(RAND_MAX)*1))-0.5f, ((float) rand() / (float(RAND_MAX)*1))-0.5f);
    Node d("", ((float) rand() / (float(RAND_MAX)*1))-0.5f, ((float) rand() / (float(RAND_MAX)*1))-0.5f);
    Node e("", ((float) rand() / (float(RAND_MAX)*1))-0.5f, ((float) rand() / (float(RAND_MAX)*1))-0.5f);
    
    addNode(a);
    addNode(b);
    addNode(c);
    addNode(d);
    addNode(e);

    addLink(a, b);
    addLink(a, c);
    addLink(a, d);
    addLink(e, d);
    #endif

    ps_ = rm_->addParticleSystem( getNumNodes() );
    ss_ = rm_->addSegmentSystem( getNumLinks() );

    ps_->init();
    ss_->init();

    synchronizeBuffers();

    //etlog(std::string("num segment points after init: ") + std::to_string(1/*ss_->getNumSegmentPoints()*/));
    //etlog(std::string("num links after init: ") + std::to_string(0/*getNumLinks()*/));
}

void Graph::synchronizeBuffers()
{
    if (!dirty_)
        return;

    if (ps_->getNumParticles() != getNumNodes() &&
        ps_->getNumParticles() > 0)
    {
        ps_->recreateBuffers(getNumNodes());
    }

    Particle* particles = ps_->getParticles();
    int i = 0;

    for( auto&& node : nodes_ )
    {
        Particle p(node.x, node.y, node.z, node.r, node.g, node.b);
        particles[i++] = p;
    }

    if (ss_)
    {
        if( ss_->getNumSegmentPoints() != getNumLinks()*2 &&
            ss_->getNumSegmentPoints() > 0)
        {
            etlog(std::to_string(getNumLinks()));

            ss_->recreateBuffers( getNumLinks() );
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
    }

    dirty_ = false;
}

void Graph::update()
{
    /*Node n("", ((float) rand() / float(RAND_MAX)*2)-1, ((float) rand() / float(RAND_MAX)*2)-1);
    n.r=n.g=n.b= (char)125;
    addNode(n);
    addLink(n, nodes_[nodes_.size()-2]);*/

    /*int i=0;
    for(auto&& n : nodes_)
    {
        n.x += 0.00001 * ((i++)%5 - 2);
        n.y += 0.00001 * ((i++)%7 - 3.5);
    }
        
    dirty_ = true;*/

    dirty_ = layout_->stepLayout();

    synchronizeBuffers();
}
