#ifndef BASELAYOUT_H
#define BASELAYOUT_H

class BaseLayout
{
public:
    BaseLayout(class Graph* g):graph_(g){};
    
    virtual ~BaseLayout() = default;

    // performs one single step of simulation
    virtual bool stepLayout() = 0;

    // performs the whole simulation
    virtual void fullLayout() = 0;

    // non-owning pointer to the graph structure
    class Graph* graph_;
};

#endif