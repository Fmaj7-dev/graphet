#include "background.h"

#include <cassert>

GLfloat vVertices[] = {  -1.0, -1.0, -0.5,
                         -1.0,  1.0, -0.5,
                          1.0, -1.0, -0.5,
                          1.0,  1.0, -0.5 };

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
    /*"void main()                             \n"
    "{                                       \n"
    "    gl_FragColor = vec4 ( gl_FragCoord.x, 0.1, 0.1, 0.5 );             \n"
    "}                                       \n"*/
    "void main()                             \n"
    "{"
    "vec2 u_resolution=vec2(640,480);"
    "vec2 st = gl_FragCoord.xy/u_resolution.xy;"
    "vec3 color1 = vec3(0.0, 0.12, 0.23);"
    "vec3 color2 = vec3(0.0, 0.08, 0.1);"
    "float mixValue1 = distance(st,vec2(0.4,0.5));"
    "float mixValue2 = distance(st,vec2(0.6,0.5));"
    "float mixValue=min(mixValue1, mixValue2);"
    "vec3 color = mix(color1, color2,  mixValue*3.0);"
    "gl_FragColor = vec4(color,mixValue);"
    "}"
    );

    program_id = render::CreateProgram();
    assert(program_id);
    render::AttachShader(program_id, vertex_id);
    render::AttachShader(program_id, fragment_id);
    render::BindAttribLocation(program_id, Context::Position_loc, "a_position");
    //glBindAttribLocation(program_id, Context::Color_loc, "a_color");
    render::LinkProgram(program_id);
    
    render::GetAttribLocation( program_id, "a_position" );

    GLint linked = 0;
    render::GetProgramiv(program_id, GL_LINK_STATUS, &linked);
    assert(linked);
    render::UseProgram(program_id);
   
    /*#ifdef __APPLE__
        render::PointSize(16.0f);
    #else
        glEnable(GL_PROGRAM_POINT_SIZE);
    #endif*/

    render::GenBuffers(1, &geom_id);
    assert(geom_id);
    render::BindBuffer(GL_ARRAY_BUFFER, geom_id);
    render::BufferData(GL_ARRAY_BUFFER, 12*4, vVertices, GL_STATIC_DRAW);

    render::VertexAttribPointer(Context::Position_loc, 3, GL_FLOAT, 0, 0, 0);
    render::EnableVertexAttribArray(Context::Position_loc);
}

void Background::draw()
{
    render::UseProgram(program_id);
    render::BindBuffer( GL_ARRAY_BUFFER , geom_id );
    //render::VertexAttribPointer(0 /* ? */, 3, GL_FLOAT, 0, 0, 0);
    //render::EnableVertexAttribArray(0);
    
    render::DrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}