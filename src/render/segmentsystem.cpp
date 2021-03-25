#include "segmentsystem.h"
#include <cstdlib>
#include <iostream>

#if defined (EMSCRIPTEN)
    #include <stdio.h>
    #include <cassert>
#endif 

SegmentSystem::SegmentSystem(size_t n)
{
    segments_ = std::vector<Segment>(n);
    srand(420);
}

SegmentSystem::~SegmentSystem()
{
}

void SegmentSystem::randInitPositions()
{
    for (size_t i = 0; i < segments_.size(); ++i)
    {
        float x1 = ((float) rand() / float(RAND_MAX)*2)-1;
        float y1 = ((float) rand() / float(RAND_MAX)*2)-1;
        float z1 = ((float) rand() / float(RAND_MAX)*2)-1;

        segments_[i].position1_[0] = x1;
        segments_[i].position1_[1] = y1;
        segments_[i].position1_[2] = z1;

        /*if (i % 2)
        {
            segments_[i].position1_[0] = 0.1*i;
            segments_[i].position1_[1] = 0.2;
            segments_[i].position1_[2] = 0;
        }
        else
        {
            segments_[i].position1_[0] = 0.1*i;
            segments_[i].position1_[1] = 0;
            segments_[i].position1_[2] = 0;
        }*/

        segments_[i].color1_[0] = 128;
        segments_[i].color1_[1] = 255;
        segments_[i].color1_[2] = 255;
    } 
}

Segment* SegmentSystem::getSegments()
{
    return &segments_[0];
}
size_t SegmentSystem::getNumSegments()
{
    return segments_.size();
}

void SegmentSystem::addSegment(const Segment& p)
{
    segments_.push_back(p);
}

void SegmentSystem::init()
{
    randInitPositions();

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
    
    //WTF
    glUseProgram(program_id);
    glGenBuffers(1, &geom_id);
    assert(geom_id);
    glBindBuffer(GL_ARRAY_BUFFER, geom_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Segment)*getNumSegments(), getSegments(), GL_DYNAMIC_DRAW);
    auto offset = [](size_t value) -> const GLvoid * { return reinterpret_cast<const GLvoid *>(value); };
    glVertexAttribPointer(Context::Position_loc, 3, GL_FLOAT, GL_FALSE, sizeof(Segment), offset(0));
    glEnableVertexAttribArray(Context::Position_loc);
    glVertexAttribPointer(Context::Color_loc, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Segment), offset(3 * sizeof(float)));
    glEnableVertexAttribArray(Context::Color_loc);
}

GLint SegmentSystem::LoadShader(GLenum type, const char *src)
{
    const GLuint id = glCreateShader(type);
    assert(id);
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    GLint compiled = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &compiled);
    //assert(compiled);
    printf("- compiled: %d\n", compiled);
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

void SegmentSystem::draw()
{
    glUseProgram(program_id);
    glBindBuffer( GL_ARRAY_BUFFER , geom_id );
    glBufferSubData( GL_ARRAY_BUFFER , 0 , sizeof(Segment)*getNumSegments() , getSegments() );
    glLineWidth(1.0); //FIXME: needed? YES

    glDrawArrays(GL_LINES, 0, getNumSegments());
}