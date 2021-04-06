#include "glwrapper.h"
#include "utils/log.h"

#include <iostream>

namespace render
{
void GetError(std::string from)
{
    GLenum err;
    while((err = glGetError()) != GL_NO_ERROR)
    {
        etlog(from + std::string(" error detected ")+std::to_string(err));
    }
    etlog(from);
}

void UseProgram(GLuint program)
{
    glUseProgram(program);
    GetError(__FUNCTION__);
}

const GLubyte *GetString (GLenum name)
{
    const GLubyte* ret = glGetString (name);
    GetError();
    return ret;
}

void printInfo()
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

void ClearColor (ETclampf red, ETclampf green, ETclampf blue, ETclampf alpha)
{
    glClearColor(red, green, blue, alpha);
}

void Viewport (ETint x, ETint y, ETsizei width, ETsizei height)
{
    glViewport (x, y, width, height);
}

void Clear (GLbitfield mask)
{
    glClear(mask);
}

ETuint CreateShader(ETenum type)
{
    return glCreateShader (type);
}

void ShaderSource(ETuint shader, ETsizei count, const ETchar* const *string, const ETint *length)
{
    glShaderSource (shader, count, string, length);
}

void CompileShader (ETuint shader)
{
    glCompileShader (shader);
}

void GetShaderiv (ETuint shader, ETenum pname, ETint *params)
{
    glGetShaderiv (shader, pname, params);
}

void GetShaderInfoLog (ETuint shader, ETsizei bufSize, ETsizei* length, ETchar *infoLog)
{
    glGetShaderInfoLog (shader, bufSize, length, infoLog);
}

void DeleteShader (ETuint shader)
{
    glDeleteShader (shader);
}

}