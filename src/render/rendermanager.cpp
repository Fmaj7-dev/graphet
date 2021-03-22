
#include "rendermanager.h"

#if defined (EMSCRIPTEN)
    #include <stdio.h>
    #include <cassert>
#endif 

RenderManager::RenderManager(GLuint w, GLuint h)
  : ps( ParticleSystem(2000) ),
    width_(w),
    height_(h),
    vertex_id(0),
    fragment_id(0),
    program_id(0),
    geom_id(0)
{
    
}

void RenderManager::printInfo()
{
    const GLubyte *renderer = glGetString( GL_RENDERER ); 
    const GLubyte *vendor = glGetString( GL_VENDOR ); 
    const GLubyte *version = glGetString( GL_VERSION ); 
    const GLubyte *glslVersion = glGetString( GL_SHADING_LANGUAGE_VERSION ); 

    /*GLint major, minor; 
    glGetIntegerv(GL_MAJOR_VERSION, &major); 
    glGetIntegerv(GL_MINOR_VERSION, &minor); */

    printf("GL Vendor            : %s\n", vendor); 
    printf("GL Renderer          : %s\n", renderer); 
    printf("GL Version (string)  : %s\n", version); 
    //printf("GL Version (integer) : %d.%d\n", major, minor); 
    printf("GLSL Version         : %s\n", glslVersion);
}

void RenderManager::init()
{
    printInfo();
    
   ps.randInit();

   glClearColor(.1f, .1f, .1f, 1.f);

   vertex_id = LoadShader(
    GL_VERTEX_SHADER,
    "attribute vec4 a_position;              \n"
    "attribute vec4 a_color;                 \n"
    "uniform float u_time;                   \n"
    "varying vec4 v_color;                   \n"
    "void main()                             \n"
    "{                                       \n"
    "    float sz = sin(u_time);             \n"
    "    float cz = cos(u_time);             \n"
    "    mat4 rot = mat4(                    \n"
    "     cz, -sz, 0,  0,                    \n"
    "     sz,  cz, 0,  0,                    \n"
    "     0,   0,  1,  0,                    \n"
    "     0,   0,  0,  1                     \n"
    "    );                                  \n"
    "    gl_Position = a_position * rot;     \n"
    "#ifdef GL_ES                            \n"
    "    gl_PointSize = 3.0;                 \n"
    "#endif                                  \n"
    "    v_color = a_color;                  \n"
    "}                                       \n"
   );
   printf("- vertex shader loaded\n");

   fragment_id = LoadShader(
    GL_FRAGMENT_SHADER,
    "#ifdef GL_ES                            \n"
    "precision mediump float;                \n"
    "#endif                                  \n"
    "varying vec4 v_color;                   \n"
    "void main()                             \n"
    "{                                       \n"
    "    gl_FragColor = v_color;             \n"
    "}                                       \n"
   );
   printf("- fragment shader loaded\n");

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
   //g_context.u_time_loc = glGetUniformLocation(program_id, "u_time");
   //assert(g_context.u_time_loc >= 0);
   glUseProgram(program_id);
   printf("- shader program linked & bound\n");

   
#ifdef __APPLE__
   glPointSize(3.0f);
#else
   glEnable(GL_PROGRAM_POINT_SIZE);
#endif
   
   glGenBuffers(1, &geom_id);
   assert(geom_id);
   glBindBuffer(GL_ARRAY_BUFFER, geom_id);
   glBufferData(GL_ARRAY_BUFFER, sizeof(Particle)*ps.getNumParticles(), ps.getParticles(), GL_DYNAMIC_DRAW);
   auto offset = [](size_t value) -> const GLvoid * { return reinterpret_cast<const GLvoid *>(value); };
   glVertexAttribPointer(Context::Position_loc, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), offset(0));
   glEnableVertexAttribArray(Context::Position_loc);
   glVertexAttribPointer(Context::Color_loc, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Particle), offset(3 * sizeof(float)));
   glEnableVertexAttribArray(Context::Color_loc);
   printf("- geometry created & bound\n");
}

GLint RenderManager::LoadShader(GLenum type, const char *src)
{
    const GLuint id = glCreateShader(type);
    assert(id);
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    GLint compiled = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &compiled);
    //assert(compiled);
    printf("compiled: %d\n", compiled);
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

void RenderManager::draw()
{
    glViewport(0, 0, width_, height_);
    glClear(GL_COLOR_BUFFER_BIT);

    //glUniform1f(g_context.u_time_loc, glutGet(GLUT_ELAPSED_TIME) / 1000.f);
    //glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindBuffer( GL_ARRAY_BUFFER , geom_id );
    //glBufferSubData( GL_ARRAY_BUFFER , 0 , sizeof(vtcs) , vtcs );
    glBufferSubData( GL_ARRAY_BUFFER , 0 , sizeof(Particle)*ps.getNumParticles() , ps.getParticles() );

    glDrawArrays(GL_POINTS, 0, ps.getNumParticles());
}

void RenderManager::update()
{
    ps.getParticles()[0].position_[0] += 0.001f;
    ps.getParticles()[1].position_[0] += 0.01f;
    ps.getParticles()[2].position_[0] += 0.0001f;
    ps.getParticles()[3].position_[0] += 0.01f;
    ps.getParticles()[4].position_[0] += 0.001f;
    ps.getParticles()[5].position_[0] += 0.0001f;
    ps.getParticles()[6].position_[0] += 0.003f;
    ps.getParticles()[7].position_[0] += 0.0003f;
}