#ifndef FORCEATLAS_LAYOUT_H
#define FORCEATLAS_LAYOUT_H

#include "baselayout.h"

#include "math/symmetric_matrix.hpp"

class ForceAtlasLayout : public BaseLayout
{
public:
    ForceAtlasLayout(class Graph*);
    ~ForceAtlasLayout();

    void setDirty();

    bool stepLayout() override;
    void fullLayout() override;

private:
    void recreateArrays();

    size_t lastNumberOfNodes_;
    bool dirty_;

    SymmetricMatrix smatrix_;

    // index is the order (1st node, 2nd node, etc), value is the id of the node
    // if a node is deleted in the graph, they will be different.
    std::vector<size_t> orderId_;

};

#endif