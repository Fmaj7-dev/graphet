#ifndef FORCEATLAS_LAYOUT_H
#define FORCEATLAS_LAYOUT_H

#include "baselayout.h"

class ForceAtlasLayout : public BaseLayout
{
public:
    ForceAtlasLayout(class Graph*);
    ~ForceAtlasLayout();

    bool stepLayout() override;
    void fullLayout() override;

private:

};

#endif