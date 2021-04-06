#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "glwrapper.h"
/*#ifdef __APPLE__
   #define GL_SILENCE_DEPRECATION
   #include <GLUT/glut.h>
#else
    #define GL_GLEXT_PROTOTYPES
    #include <GL/glut.h>
#endif*/

class Renderable
{
public:
    render::ETint LoadShader( render::ETenum type, const char *src );
};

#endif 