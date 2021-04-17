
#include "rendermanager.h"

/*#ifdef __APPLE__
   #define GL_SILENCE_DEPRECATION
   #include <GLUT/glut.h>
#else
    #define GL_GLEXT_PROTOTYPES
    #include <GL/glut.h>
#endif*/

#if defined (EMSCRIPTEN)
    #include <stdio.h>
    #include <cassert>
#endif 

RenderManager::RenderManager(GLuint w, GLuint h)
  : width_(w),
    height_(h),
    vertex_id(0),
    fragment_id(0),
    program_id(0),
    geom_id(0)
{
    
}

void RenderManager::printInfo()
{
    render::printInfo();
}

void RenderManager::init()
{
    printInfo();

    render::ClearColor(.2f, .2f, .3f, 1.f);

    bg.init();
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
    render::Viewport(0, 0, width_, height_);
    render::Clear(ET_COLOR_BUFFER_BIT);

    //glDisable(GL_CULL_FACE);
    glEnable( GL_DEPTH_TEST );
    glClear( GL_DEPTH_BUFFER_BIT );


    
bg.draw();

    for (auto&& ss : segmentSystems_)
        ss.draw();
        

    for (auto&& ps : particleSystems_)
        ps.draw();

        

    
}

void RenderManager::update()
{

}