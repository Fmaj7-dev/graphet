
#include "rendermanager.h"
#include "camera.h"

#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>

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
    const float near = 0.1f;
    const float far = 100.0f;
    camera_ = std::unique_ptr< Camera > ( new Camera( 45, width_, height_, near, far ) );
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

    // set view & projection matrices
    for (auto&& ps : particleSystems_)
    {
        ps.setProjectionMatrixPtr( camera_->getProjectionPtr() );
        ps.setViewMatrixPtr( camera_->getViewPtr() );
    }

    for (auto&& ss : segmentSystems_)
    {
        ss.setProjectionMatrixPtr( camera_->getProjectionPtr() );
        ss.setViewMatrixPtr( camera_->getViewPtr() );
    }

    bg.draw();

    for (auto&& ss : segmentSystems_)
        ss.draw();

    for (auto&& ps : particleSystems_)
        ps.draw();
}

void RenderManager::update()
{

}

void RenderManager::moveForward()
{
    camera_->moveForward( 0.001f );
}

void RenderManager::moveBackward()
{
    camera_->moveBackward( 0.001f );
}

void RenderManager::moveLeft()
{
    camera_->moveLeft( 0.001f );
}

void RenderManager::moveRight()
{
    camera_->moveRight( 0.001f );
}