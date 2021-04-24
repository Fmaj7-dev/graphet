
#include "rendermanager.h"

#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_transform.hpp>

#if defined (EMSCRIPTEN)
    #include <stdio.h>
    #include <cassert>
#endif 

#include <iostream>

RenderManager::RenderManager(GLuint w, GLuint h)
  : width_(w),
    height_(h),
    vertex_id(0),
    fragment_id(0),
    program_id(0),
    geom_id(0)
{
    
}

void RenderManager::resize(render::ETuint w, render::ETuint h)
{
    width_ = w;
    height_ = h;
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

    /*glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f); 
    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); 
    glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
    glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);*/

    glm::mat4 view;
    view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), 
                       glm::vec3(0.0f, 0.0f, 0.0f), 
                       glm::vec3(0.0f, 1.0f, 0.0f));

    static float v = 0.0f;
    glLoadIdentity();
    gluLookAt(	0, v, 0,
                0, 0, 1 ,
                0.0f, 10.0f,  0.0f);

    bg.draw();

    for (auto&& ss : segmentSystems_)
        ss.draw();

    for (auto&& ps : particleSystems_)
        ps.draw();
}

void RenderManager::update()
{

}