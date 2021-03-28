#include "background.h"

#include <cassert>

GLfloat vVertices[] = {  -0.9, -0.9, 0,
                         -0.9,  0.9, 0,
                          0.9, -0.9, 0,
                          0.9,  0.9, 0 };

void Background::init()
{
    vertex_id = LoadShader(
    GL_VERTEX_SHADER,
    "attribute vec4 a_position;              \n"
    "void main()                             \n"
    "{                                       \n"
    "    gl_Position = a_position;           \n"
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
    "void main()                             \n"
    "{                                       \n"
    "    gl_FragColor = vec4 ( 0.1, 0.1, 0.1, 0.5 );             \n"
    "}                                       \n"
    );

    program_id = glCreateProgram();
    assert(program_id);
    glAttachShader(program_id, vertex_id);
    glAttachShader(program_id, fragment_id);
    glBindAttribLocation(program_id, Context::Position_loc, "a_position");
    //glBindAttribLocation(program_id, Context::Color_loc, "a_color");
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

    glGenBuffers(1, &geom_id);
    assert(geom_id);
    glBindBuffer(GL_ARRAY_BUFFER, geom_id);
    glBufferData(GL_ARRAY_BUFFER, 12*4, vVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(Context::Position_loc, 3, GL_FLOAT, 0, 0, 0);
    glEnableVertexAttribArray(Context::Position_loc);
}

void Background::draw()
{
    glUseProgram(program_id);
    glBindBuffer( GL_ARRAY_BUFFER , geom_id );
    glVertexAttribPointer(0 /* ? */, 3, GL_FLOAT, 0, 0, 0);
    glEnableVertexAttribArray(0);
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}