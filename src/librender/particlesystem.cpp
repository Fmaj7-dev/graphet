#include "particlesystem.h"
#include <cstdlib>
#include <iostream>

ParticleSystem::ParticleSystem(size_t n)
:num_particles_(n)
{
    std::cout<<"ParticleSystem"<<std::endl;
    particles_ = new Particle[n];
    srand(1337);
}

ParticleSystem::~ParticleSystem()
{
    delete []particles_;
}

void ParticleSystem::randInit()
{
    std::cout<<"randInit"<<std::endl;
    for (int i = 0; i < num_particles_; ++i)
    {
        float x = ((float) rand() / (RAND_MAX)*2)-1;
        float y = ((float) rand() / (RAND_MAX)*2)-1;
        float z = ((float) rand() / (RAND_MAX)*2)-1;

        particles_[i].position_[0] = x;
        particles_[i].position_[1] = y;
        particles_[i].position_[2] = z;

        particles_[i].color_[0] = 255;
        particles_[i].color_[1] = 0;
        particles_[i].color_[2] = 255;

        std::cout<<"init particle "<<x<<" "<<y<<" "<<z<<std::endl;
    } 
}