#include "segmentsystem.h"
#include "utils/log.h"

#include <cstdlib>
#include <iostream>
#include <cassert>

SegmentSystem::SegmentSystem(size_t n)
{
    segmentPoints_ = std::vector<SegmentPoint>(n*2);
    srand(420);
}

SegmentSystem::~SegmentSystem()
{
}

/*void SegmentSystem::randInitPositions()
{
    for (size_t i = 0; i < segmentPoints_.size(); ++i)
    {
        float x1 = ((float) rand() / float(RAND_MAX)*2)-1;
        float y1 = ((float) rand() / float(RAND_MAX)*2)-1;
        float z1 = ((float) rand() / float(RAND_MAX)*2)-1;

        segmentPoints_[i].position1_[0] = x1;
        segmentPoints_[i].position1_[1] = y1;
        segmentPoints_[i].position1_[2] = z1;

        segmentPoints_[i].color1_[0] = 128;
        segmentPoints_[i].color1_[1] = 255;
        segmentPoints_[i].color1_[2] = 255;
    } 
}*/

SegmentPoint* SegmentSystem::getSegmentPoints()
{
    return &segmentPoints_[0];
}
size_t SegmentSystem::getNumSegmentPoints()
{
    return segmentPoints_.size();
}

void SegmentSystem::addSegment(const Segment& p)
{
    segmentPoints_.push_back(p.a);
    segmentPoints_.push_back(p.b);
}

void SegmentSystem::recreateBuffers(size_t n)
{
    etlog("recreate segment point buffers "+std::to_string(n*2));

    glUseProgram(program_id);

    segmentPoints_ = std::vector<SegmentPoint>(n*2);

    glGenBuffers(1, &geom_id);
    assert(geom_id);
    glBindBuffer(GL_ARRAY_BUFFER, geom_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(SegmentPoint)*getNumSegmentPoints(), getSegmentPoints(), GL_DYNAMIC_DRAW);

    auto offset = [](size_t value) -> const GLvoid * { return reinterpret_cast<const GLvoid *>(value); };
    glVertexAttribPointer(Context::Position_loc, 3, GL_FLOAT, GL_FALSE, sizeof(SegmentPoint), offset(0));
    glEnableVertexAttribArray(Context::Position_loc);
    glVertexAttribPointer(Context::Color_loc, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(SegmentPoint), offset(3 * sizeof(float)));
    glEnableVertexAttribArray(Context::Color_loc);
}

void SegmentSystem::init()
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
    "   gl_FragColor = v_color;              \n"
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
    
    etlog("reserving buffer for "+std::to_string(getNumSegmentPoints())+std::string(" segmentpoints"));
    
    glUseProgram(program_id);
    glGenBuffers(1, &geom_id);
    assert(geom_id);
    glBindBuffer(GL_ARRAY_BUFFER, geom_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(SegmentPoint)*getNumSegmentPoints(), getSegmentPoints(), GL_DYNAMIC_DRAW);
    auto offset = [](size_t value) -> const GLvoid * { return reinterpret_cast<const GLvoid *>(value); };
    glVertexAttribPointer(Context::Position_loc, 3, GL_FLOAT, GL_FALSE, sizeof(SegmentPoint), offset(0));
    glEnableVertexAttribArray(Context::Position_loc);
    glVertexAttribPointer(Context::Color_loc, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(SegmentPoint), offset(3 * sizeof(float)));
    glEnableVertexAttribArray(Context::Color_loc);
}

void SegmentSystem::draw()
{
    if (getNumSegmentPoints() == 0)
        return;
    
    glUseProgram(program_id);
    glBindBuffer( GL_ARRAY_BUFFER , geom_id );
    glBufferSubData( GL_ARRAY_BUFFER , 0 , sizeof(SegmentPoint)*getNumSegmentPoints() , getSegmentPoints() );
    glLineWidth(1.0); //FIXME: needed? YES

    glDrawArrays(GL_LINES, 0, getNumSegmentPoints());
}