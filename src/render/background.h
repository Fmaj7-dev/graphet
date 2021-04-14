
#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "renderable.h"

#ifdef __APPLE__
   #define GL_SILENCE_DEPRECATION
   #include <GLUT/glut.h>
#else
    #define GL_GLEXT_PROTOTYPES
    #include <GL/glut.h>
#endif

class Background : Renderable
{
public: 
    void init();
    void draw();

private:
    class Context{ public: enum type{ Position_loc=9, Color_loc=10 }; };

    GLuint vertex_id;
    GLuint fragment_id;
    GLuint program_id;
    GLuint geom_id;
};

#endif