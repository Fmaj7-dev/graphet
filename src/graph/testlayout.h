#ifndef TEST_LAYOUT_H
#define TEST_LAYOUT_H

#include "baselayout.h"

class TestLayout : public BaseLayout
{
public:
    TestLayout(class Graph*);
    ~TestLayout();

    bool stepLayout() override;
    void fullLayout() override;

private:

};

#endif