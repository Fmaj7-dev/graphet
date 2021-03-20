#include "particlesystem.h"
#include <cstdlib>

ParticleSystem::ParticleSystem(size_t n)
{
    //particles_ = new Particle[n];
    particles_ = std::vector<Particle>(n);
    srand(1337);
}

ParticleSystem::~ParticleSystem()
{
    //delete []particles_;
}

void ParticleSystem::randInit()
{
    for (size_t i = 0; i < particles_.size(); ++i)
    {
        float x = ((float) rand() / float(RAND_MAX)*2)-1;
        float y = ((float) rand() / float(RAND_MAX)*2)-1;
        float z = ((float) rand() / float(RAND_MAX)*2)-1;

        particles_[i].position_[0] = x;
        particles_[i].position_[1] = y;
        particles_[i].position_[2] = z;

        particles_[i].color_[0] = 255;
        particles_[i].color_[1] = 0;
        particles_[i].color_[2] = 255;
    } 
}

Particle* ParticleSystem::getParticles()
{
    return &particles_[0];
}
size_t ParticleSystem::getNumParticles()
{
    return particles_.size();
}

void ParticleSystem::addParticle(const Particle& p)
{
    particles_.push_back(p);
}
