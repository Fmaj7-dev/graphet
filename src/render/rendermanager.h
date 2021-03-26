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

    ParticleSystem* addParticleSystem(size_t hint_nparticles);
    SegmentSystem* addSegmentSystem(size_t hint_nsegments);

private:
    GLint LoadShader(GLenum type, const char *src);

private:
    

    std::vector<ParticleSystem> particleSystems_;
    std::vector<SegmentSystem> segmentSystems_;
    
    GLuint width_;
    GLuint height_;
    
    GLuint vertex_id;
    GLuint fragment_id;
    GLuint program_id;
    GLuint geom_id;
};

#endif