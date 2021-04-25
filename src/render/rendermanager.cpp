
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

{

    static float time = 0.0f;

    for (auto&& ps : particleSystems_)
        ps.setProjectionMatrixPtr( camera_->getProjectionPtr() );

    for (auto&& ss : segmentSystems_)
        ss.setProjectionMatrixPtr( camera_->getProjectionPtr() );

    // view
    glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    float radius = 1.0f;
    float camX   = sin(time) * radius;
    float camZ   = cos(time) * radius;
    view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    for (auto&& ps : particleSystems_)
        ps.setViewMatrixPtr( glm::value_ptr(view) );

    for (auto&& ss : segmentSystems_)
        ss.setViewMatrixPtr( glm::value_ptr(view) );

    time += 0.001f;
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