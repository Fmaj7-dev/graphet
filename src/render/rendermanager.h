#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

#include "particlesystem.h"
#include "segmentsystem.h"
#include "background.h"
#include "glwrapper.h"
#include "camera.h"


class RenderManager
{
public:
    RenderManager(render::ETuint w, render::ETuint h);

    void resize(render::ETuint w, render::ETuint h);

    void render();

    void draw();

    void update();

    void init();

    void printInfo();

    void moveForward();
    void moveBackward();
    void moveLeft();
    void moveRight();


    ParticleSystem* addParticleSystem(size_t hint_nparticles);
    SegmentSystem* addSegmentSystem(size_t hint_nsegments);

private:
    render::ETint LoadShader(render::ETenum type, const char *src);

private:

    std::unique_ptr<Camera> camera_;    

    std::vector<ParticleSystem> particleSystems_;
    std::vector<SegmentSystem> segmentSystems_;

    Background bg;
    
    render::ETuint width_;
    render::ETuint height_;
    
    render::ETuint vertex_id;
    render::ETuint fragment_id;
    render::ETuint program_id;
    render::ETuint geom_id;
};

#endif