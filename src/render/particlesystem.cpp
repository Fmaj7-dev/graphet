#include "particlesystem.h"
#include "utils/log.h"

#include <cstdlib>
#include <iostream>

#if defined (EMSCRIPTEN)
    #include <stdio.h>
    #include <cassert>
#endif 

ParticleSystem::ParticleSystem(size_t n)
{
    particles_ = std::vector<Particle>(n);
    srand(1337);
}

ParticleSystem::~ParticleSystem()
{
}

/*void ParticleSystem::randInitPositions()
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
        particles_[i].color_[1] = 128;
        particles_[i].color_[2] = 255;
    } 
}*/

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

void ParticleSystem::recreateBuffers(size_t n)
{
    etlog(std::string("recreate particle buffers ")+std::to_string(n));

    glUseProgram(program_id);

    particles_ = std::vector<Particle>(n);

    //glGenBuffers(1, &geom_id);
    //assert(geom_id);
    glBindBuffer(GL_ARRAY_BUFFER, geom_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Particle)*getNumParticles(), getParticles(), GL_DYNAMIC_DRAW);

    auto offset = [](size_t value) -> const GLvoid * { return reinterpret_cast<const GLvoid *>(value); };

    glVertexAttribPointer(Context::Position_loc, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), offset(0));
    glEnableVertexAttribArray(Context::Position_loc);
    glVertexAttribPointer(Context::Color_loc, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Particle), offset(3 * sizeof(float)));
    glEnableVertexAttribArray(Context::Color_loc);
}

void ParticleSystem::init()
{
    //randInitPositions();

    vertex_id = LoadShader(
    GL_VERTEX_SHADER,
    "attribute vec4 a_position;              \n"
    "attribute vec4 a_color;                 \n"
    "varying vec4 v_color;                   \n"
    "void main()                             \n"
    "{                                       \n"
    "    gl_Position = a_position;           \n"
    "#ifdef GL_ES                            \n"
    "    gl_PointSize = 16.0;                 \n"
    "#endif                                  \n"
    "    v_color = a_color;                  \n"
    "}                                       \n"
    );

    fragment_id = LoadShader(
    GL_FRAGMENT_SHADER,
    #ifdef __APPLE__
    "#version 120\n"
    #endif
    "#ifdef GL_ES                            \n"
    "   precision mediump float;             \n"
    "#endif                                  \n"
    "varying vec4 v_color;                   \n"
    "void main()                             \n"
    "{                                       \n"
    "   vec2 temp = gl_PointCoord - vec2(0.5);\n"
    "   float f = dot(temp, temp);\n"
    //"   if (f>0.25) discard;\n"
    "   gl_FragColor = v_color;             \n"
    " gl_FragColor.a = 1.0-f*5.0;"
    "}                                       \n"
    );

    program_id = glCreateProgram();
    assert(program_id);
    glAttachShader(program_id, vertex_id);
    glAttachShader(program_id, fragment_id);
    glBindAttribLocation(program_id, Context::Position_loc, "a_position");
    glBindAttribLocation(program_id, Context::Color_loc, "a_color");
    glLinkProgram(program_id);
    GLint linked = 0;
    glGetProgramiv(program_id, GL_LINK_STATUS, &linked);
    assert(linked);
    glUseProgram(program_id);
   
    #ifdef __APPLE__
        glPointSize(16.0f);
    #else
        glEnable(GL_PROGRAM_POINT_SIZE);
    #endif

    etlog("reserving buffer for "+std::to_string(getNumParticles())+std::string(" particles"));

    glGenBuffers(1, &geom_id);
    assert(geom_id);
    glBindBuffer(GL_ARRAY_BUFFER, geom_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Particle)*getNumParticles(), getParticles(), GL_DYNAMIC_DRAW);
    auto offset = [](size_t value) -> const GLvoid * { return reinterpret_cast<const GLvoid *>(value); };

    glVertexAttribPointer(Context::Position_loc, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), offset(0));
    glEnableVertexAttribArray(Context::Position_loc);
    glVertexAttribPointer(Context::Color_loc, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Particle), offset(3 * sizeof(float)));
    glEnableVertexAttribArray(Context::Color_loc);
}

GLint ParticleSystem::LoadShader(GLenum type, const char *src)
{
    const GLuint id = glCreateShader(type);
    assert(id);
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    GLint compiled = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &compiled);
    //assert(compiled);
    printf("* compiled: %d\n", compiled);
    if(compiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);
        printf("%s", &errorLog[0]);

        // Provide the infolog in whatever manor you deem best.
        // Exit with failure.
        glDeleteShader(id);
        return 0;
    }
    return id;
};

void ParticleSystem::draw()
{
    // alpha for soft circles
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glUseProgram(program_id);
    glBindBuffer( GL_ARRAY_BUFFER , geom_id );
    glBufferSubData( GL_ARRAY_BUFFER , 0 , sizeof(Particle)*getNumParticles() , getParticles() );
    
    glDrawArrays(GL_POINTS, 0, getNumParticles());

    glDisable(GL_BLEND);
}