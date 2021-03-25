#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

#include "particlesystem.h"
#include "segmentsystem.h"

#ifdef __APPLE__
   #define GL_SILENCE_DEPRECATION
   #include <GLUT/glut.h>
#else
    #define GL_GLEXT_PROTOTYPES
    #include <GL/glut.h>
#endif

class RenderManager
{
public:
    RenderManager(GLuint w, GLuint h);

    void render();

    void draw();

    void update();

    void init();

    void printInfo();

private:
    GLint LoadShader(GLenum type, const char *src);

private:
    

    ParticleSystem ps;
    SegmentSystem ss;
    
    GLuint width_;
    GLuint height_;
    
    GLuint vertex_id;
    GLuint fragment_id;
    GLuint program_id;
    GLuint geom_id;
};

#endif