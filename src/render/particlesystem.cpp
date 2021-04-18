#include "particlesystem.h"
#include "utils/log.h"

#include <cstdlib>
#include <iostream>
#include <cassert>

ParticleSystem::ParticleSystem(size_t n)
{
    particles_ = std::vector<Particle>(n);
    srand(1337);
}

ParticleSystem::~ParticleSystem()
{
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

void ParticleSystem::recreateBuffers(size_t n)
{
    etlog(std::string("recreate particle buffers ")+std::to_string(n));

    render::UseProgram(program_id);

    particles_ = std::vector<Particle>(n);

    //glGenBuffers(1, &geom_id);
    //assert(geom_id);
    render::BindBuffer(ET_ARRAY_BUFFER, geom_id);
    render::BufferData(ET_ARRAY_BUFFER, sizeof(Particle)*getNumParticles(), getParticles(), ET_DYNAMIC_DRAW);

    auto offset = [](size_t value) -> const render::ETvoid * { return reinterpret_cast<const render::ETvoid *>(value); };

    render::VertexAttribPointer(Context::Position_loc, 3, ET_FLOAT, ET_FALSE, sizeof(Particle), offset(0));
    render::EnableVertexAttribArray(Context::Position_loc);
    render::VertexAttribPointer(Context::Color_loc, 4, ET_UNSIGNED_BYTE, ET_TRUE, sizeof(Particle), offset(3 * sizeof(float)));
    render::EnableVertexAttribArray(Context::Color_loc);
}

void ParticleSystem::init()
{
    vertex_id = LoadShader(
    ET_VERTEX_SHADER,
    "attribute vec4 a_position;              \n"
    "attribute vec4 a_color;                 \n"
    "varying vec4 v_color;                   \n"
    "void main()                             \n"
    "{                                       \n"
    "    gl_Position = a_position;           \n"
    "#ifdef GL_ES                            \n"
    "    gl_PointSize = 16.0;                \n"
    "#endif                                  \n"
    "    v_color = a_color;                  \n"
    "}                                       \n"
    );

    fragment_id = LoadShader(
    ET_FRAGMENT_SHADER,
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

    program_id = render::CreateProgram();
    assert(program_id);
    render::AttachShader(program_id, vertex_id);
    render::AttachShader(program_id, fragment_id);
    render::BindAttribLocation(program_id, Context::Position_loc, "a_position");
    render::BindAttribLocation(program_id, Context::Color_loc, "a_color");
    render::LinkProgram(program_id);

    render::GetAttribLocation( program_id, "a_position" );
    render::GetAttribLocation( program_id, "a_color" );

    render::ETint linked = 0;
    render::GetProgramiv(program_id, ET_LINK_STATUS, &linked);
    assert(linked);
    render::UseProgram(program_id);
   
    #ifdef __APPLE__
        render::PointSize(16.0f);
    #else
        //render::Enable(GL_PROGRAM_POINT_SIZE);
    #endif

    //etlog("reserving buffer for "+std::to_string(getNumParticles())+std::string(" particles"));

    render::GenBuffers(1, &geom_id);
    assert(geom_id);
    render::BindBuffer(ET_ARRAY_BUFFER, geom_id);
    render::BufferData(ET_ARRAY_BUFFER, sizeof(Particle)*getNumParticles(), getParticles(), ET_DYNAMIC_DRAW);
    auto offset = [](size_t value) -> const render::ETvoid * { return reinterpret_cast<const render::ETvoid *>(value); };

    render::VertexAttribPointer(Context::Position_loc, 3, ET_FLOAT, ET_FALSE, sizeof(Particle), offset(0));
    render::EnableVertexAttribArray(Context::Position_loc);
    render::VertexAttribPointer(Context::Color_loc, 4, ET_UNSIGNED_BYTE, ET_TRUE, sizeof(Particle), offset(3 * sizeof(float)));
    render::EnableVertexAttribArray(Context::Color_loc);
}

void ParticleSystem::draw()
{
    // alpha for soft circles
    render::Enable(ET_BLEND);
    render::BlendFunc(ET_SRC_ALPHA, ET_ONE_MINUS_SRC_ALPHA);

    render::UseProgram(program_id);
    render::BindBuffer( ET_ARRAY_BUFFER , geom_id );
    render::BufferSubData( ET_ARRAY_BUFFER , 0 , sizeof(Particle)*getNumParticles() , getParticles() );

    /*std::cout<<"{";
    for (int i = 0; i < 10; ++i)
    {
        std::cout<<"[x:"<<particles_[i].position_[0]<<", y:"<<particles_[i].position_[1]<<", z:"<<particles_[i].position_[2]<<"], ";
    }
    std::cout<<"}"<<std::endl;*/
    
    render::DrawArrays(ET_POINTS, 0, getNumParticles());

    render::Disable(ET_BLEND);
}