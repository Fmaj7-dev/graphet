#include "forceatlaslayout.h"
#include "graph.h"
#include "utils/log.h"

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include <iostream>

ForceAtlasLayout::ForceAtlasLayout(Graph* g)
: BaseLayout(g),
  lastNumberOfNodes_(0),
  dirty_(true)
  
{

}

ForceAtlasLayout::~ForceAtlasLayout()
{

}

void ForceAtlasLayout::setDirty()
{
    dirty_ = true;
}

void ForceAtlasLayout::recreateArrays()
{
    etlog("recreateArrays");
    smatrix_ = SymmetricMatrix( graph_->getNumNodes() );
    orderId_.resize( graph_->getNumNodes() );

    size_t i = 0;
    for(auto&& node: graph_->getNodes() )
        orderId_[i++] = node.id;

    lastNumberOfNodes_ = graph_->getNumNodes();
    dirty_ = false;
}

bool ForceAtlasLayout::stepLayout()
{
    const float max_repel_distance = 0.1;
    const float repel_force = 0.01f;
    const float attract_force = 1.0f;
    const float spring_distance = 0.001;
    const float dt = 0.001f;

    std::vector<glm::vec3> new_positions;

    // make sure we have the right size of buffers
    if (graph_->getNumNodes() != lastNumberOfNodes_ || dirty_)
        recreateArrays();

    new_positions.resize(lastNumberOfNodes_);

    // make all forces repel
    smatrix_.reset(-repel_force);

    // make links attract
    for (auto&& link: graph_->getLinks())
        smatrix_.set(link.from, link.to, attract_force); //FIXME: node ids

    // calculate forces
    for (size_t i = 0; i < lastNumberOfNodes_; ++i)
    {
        glm::vec3 accum_i(0.0, 0.0, 0.0);
        Node& node_i = graph_->getNodes()[i];
        glm::vec3 vec_i(node_i.x, node_i.y, node_i.z);

        for ( size_t j = 0; j < lastNumberOfNodes_; ++j)
        {
            if (i == j) continue;
            Node& node_j = graph_->getNodes()[j];
            glm::vec3 vec_j(node_j.x, node_j.y, node_j.z);

            float force = smatrix_.get(i, j);
            float distance = glm::distance(vec_i, vec_j);
            glm::vec3 direction = vec_j - vec_i;

            // repel
            if (force < 0)
            {
                if (distance < max_repel_distance)
                    accum_i += force*direction;
            }
            //attract
            else
            {
                float error = abs(spring_distance - distance);
                if (distance < spring_distance)
                    accum_i -= force*direction*error/100.0f;
                else
                    accum_i += force*direction*error;
            } 
        }
        new_positions[i] = vec_i + accum_i*dt;
    }
    for (size_t i = 0; i < lastNumberOfNodes_; ++i)
    {
        Node& node_i = graph_->getNodes()[i];
        node_i.x = new_positions[i].x;
        node_i.y = new_positions[i].y;
        node_i.z = new_positions[i].z;
    }
    
    return true;
}

void ForceAtlasLayout::fullLayout()
{

}
