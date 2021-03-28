#ifndef RENDERABLE_H
#define RENDERABLE_H

#ifdef __APPLE__
   #define GL_SILENCE_DEPRECATION
   #include <GLUT/glut.h>
#else
    #define GL_GLEXT_PROTOTYPES
    #include <GL/glut.h>
#endif

class Renderable
{
public:
    GLint LoadShader( GLenum type, const char *src );
};

#endif 