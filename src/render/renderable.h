#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "glwrapper.h"

class Renderable
{
public:
    render::ETint LoadShader( render::ETenum type, const char *src );
};

#endif 