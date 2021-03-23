
#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#ifdef __APPLE__
   #define GL_SILENCE_DEPRECATION
   #include <GLUT/glut.h>
#else
    #define GL_GLEXT_PROTOTYPES
    #include <GL/glut.h>
#endif

#include <vector>

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
    ParticleSystem(size_t n = 0);
    ~ParticleSystem();
    void randInitPositions();

    // particles
    void addParticle(const Particle&);
    Particle* getParticles();
    size_t getNumParticles();

    // render
    void init();
    GLint LoadShader(GLenum type, const char *src);
    void draw();

private:
    class Context{ public: enum type{ Position_loc, Color_loc }; };

    GLuint vertex_id;
    GLuint fragment_id;
    GLuint program_id;
    GLuint geom_id;

private:
    std::vector<Particle> particles_;
};

#endif