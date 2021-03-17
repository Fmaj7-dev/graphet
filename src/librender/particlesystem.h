
#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include <stddef.h>

class Particle
{
public:
    Particle() = default;
    Particle(float x, float y, float z, int r, int g, int b)
    {
        position_[0] = x;
        position_[1] = y;
        position_[2] = z;

        color_[0] = r;
        color_[1] = g;
        color_[2] = b; 
    }
//private:
    float position_[3];
    unsigned char color_[3];
};

class ParticleSystem
{
public:
    ParticleSystem(size_t n);
    ~ParticleSystem();
    void randInit();

    Particle* particles_;

    size_t num_particles_;
};

#endif