
#include "rendermanager.h"

#if defined (EMSCRIPTEN)
    #include <stdio.h>
    #include <cassert>
#endif 

RenderManager::RenderManager(GLuint w, GLuint h)
  : //ps( ParticleSystem(20) ),
    //ss( SegmentSystem(10)),
    width_(w),
    height_(h),
    vertex_id(0),
    fragment_id(0),
    program_id(0),
    geom_id(0)
{
    
}

void RenderManager::printInfo()
{
    const GLubyte *renderer = glGetString( GL_RENDERER ); 
    const GLubyte *vendor = glGetString( GL_VENDOR ); 
    const GLubyte *version = glGetString( GL_VERSION ); 
    const GLubyte *glslVersion = glGetString( GL_SHADING_LANGUAGE_VERSION ); 

    /*GLint major, minor; 
    glGetIntegerv(GL_MAJOR_VERSION, &major); 
    glGetIntegerv(GL_MINOR_VERSION, &minor); */

    printf("GL Vendor            : %s\n", vendor); 
    printf("GL Renderer          : %s\n", renderer); 
    printf("GL Version (string)  : %s\n", version); 
    //printf("GL Version (integer) : %d.%d\n", major, minor); 
    printf("GLSL Version         : %s\n", glslVersion);
}

void RenderManager::init()
{
    printInfo();

    glClearColor(.2f, .1f, .1f, 1.f);

    //ps.init();
    //ss.init();
    
}

ParticleSystem* RenderManager::addParticleSystem( size_t hint_nparticles )
{
    particleSystems_.push_back( ParticleSystem( hint_nparticles ) );
    return &particleSystems_[ particleSystems_.size() - 1 ];
}

SegmentSystem* RenderManager::addSegmentSystem( size_t hint_nsegments)
{
    segmentSystems_.push_back( SegmentSystem( hint_nsegments ) );
    return &segmentSystems_[ segmentSystems_.size() - 1];
}

void RenderManager::draw()
{
    glViewport(0, 0, width_, height_);
    glClear(GL_COLOR_BUFFER_BIT);
    //glDisable(GL_CULL_FACE);
    
    //glUniform1f(g_context.u_time_loc, glutGet(GLUT_ELAPSED_TIME) / 1000.f);
    //glDrawArrays(GL_TRIANGLES, 0, 3);

    
    /*ss.draw();
    ps.draw();*/

    for (auto&& ss : segmentSystems_)
        ss.draw();

    for (auto&& ps : particleSystems_)
        ps.draw();
}

void RenderManager::update()
{

}