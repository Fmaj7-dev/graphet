#include "testlayout.h"
#include "graph.h"

#include <glm/vec3.hpp>

#include <iostream>

TestLayout::TestLayout(Graph* g)
: BaseLayout(g)
{

}

TestLayout::~TestLayout()
{

}

bool TestLayout::stepLayout()
{
    std::vector<Node>& nodes = graph_->getNodes();

    int i=0;
    for(auto&& n : nodes)
    {
        n.x += 0.00001 * ((i++)%5 - 2);
        n.y += 0.00001 * ((i++)%7 - 3.5);
    }

    return true;
}

void TestLayout::fullLayout()
{

}
