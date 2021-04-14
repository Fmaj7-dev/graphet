#include "glwrapper.h"
#include "utils/log.h"

#ifdef __APPLE__
   #define GL_SILENCE_DEPRECATION
   #include <GLUT/glut.h>
#else
    #define GL_GLEXT_PROTOTYPES
    #include <GL/glut.h>
#endif

#include <iostream>
#include <iomanip>
#include <sstream>

namespace render
{
bool GetError(std::string from)
{
    GLenum err;
    bool found = false;
    while((err = glGetError()) != GL_NO_ERROR)
    {
        etlog(from + std::string(" error detected ")+std::to_string(err));
        found = true;
    }
    return found;
}

void logFunction(std::string text)
{
    //etlog(". "+text);
    text = text;
}

void UseProgram(GLuint program)
{
    glUseProgram(program);
    GetError(__FUNCTION__);
    logFunction(__FUNCTION__+std::string(" ")+std::to_string(program));
}

const GLubyte* GetString (GLenum name)
{
    const GLubyte* ret = glGetString (name);
    GetError(__FUNCTION__);
    logFunction(__FUNCTION__);
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
    logFunction(__FUNCTION__);
}

void ClearColor (ETclampf red, ETclampf green, ETclampf blue, ETclampf alpha)
{
    glClearColor(red, green, blue, alpha);
    GetError(__FUNCTION__);
    logFunction(__FUNCTION__);
}

void Viewport (ETint x, ETint y, ETsizei width, ETsizei height)
{
    glViewport (x, y, width, height);
    GetError(__FUNCTION__);
    logFunction(std::string(__FUNCTION__) + " "+std::to_string(width)+ " "+std::to_string(height));
}

void Clear (GLbitfield mask)
{
    glClear(mask);
    GetError(__FUNCTION__);
    logFunction(__FUNCTION__);
}

ETuint CreateShader(ETenum type)
{
    ETuint ret = glCreateShader (type);
    GetError(__FUNCTION__);
    logFunction(__FUNCTION__+std::string(" -> ")+std::to_string(ret));
    return ret;
}

void ShaderSource(ETuint shader, ETsizei count, const ETchar* const *string, const ETint *length)
{
    glShaderSource (shader, count, string, length);
    GetError(__FUNCTION__);
    logFunction(__FUNCTION__);
}

void CompileShader (ETuint shader)
{
    glCompileShader (shader);
    GetError(__FUNCTION__);
    logFunction(__FUNCTION__ + std::string(" ") + std::to_string(shader));
}

void GetShaderiv (ETuint shader, ETenum pname, ETint *params)
{
    glGetShaderiv (shader, pname, params);
    GetError(__FUNCTION__);
    logFunction(__FUNCTION__);
}

void GetShaderInfoLog (ETuint shader, ETsizei bufSize, ETsizei* length, ETchar *infoLog)
{
    glGetShaderInfoLog (shader, bufSize, length, infoLog);
    GetError(__FUNCTION__);
    logFunction(__FUNCTION__);
}

void DeleteShader (ETuint shader)
{
    glDeleteShader (shader);
    GetError(__FUNCTION__);
    logFunction(__FUNCTION__);
}

void BindBuffer (render::ETenum target, render::ETuint buffer)
{
    glBindBuffer(target, buffer);
    GetError(__FUNCTION__);
    logFunction(__FUNCTION__ + std::string(" target: ")+std::to_string(target)+std::string(" ")+std::to_string(buffer));
}

void BufferData (ETenum target, ETsizeiptr size, const ETvoid *data, ETenum usage)
{
    glBufferData(target, size, data, usage);
    GetError(__FUNCTION__);
    std::stringstream stream;
    stream << std::hex << (long int)data;
    std::string result( stream.str() );
    logFunction(__FUNCTION__+std::string(" size: ")+std::to_string(size) + std::string(" address: ") + result);
}

void VertexAttribPointer (ETuint index, ETint size, ETenum type, ETboolean normalized, ETsizei stride, const ETvoid *pointer)
{
    glVertexAttribPointer (index, size, type, normalized, stride, pointer);
    GetError(__FUNCTION__);
    logFunction(__FUNCTION__+std::string(" index: ")+std::to_string(index) + std::string(" size: ") + std::to_string(size));
}

void EnableVertexAttribArray (GLuint index)
{
    glEnableVertexAttribArray (index);
    GetError(__FUNCTION__);
    logFunction(__FUNCTION__+std::string(" index: ")+std::to_string(index));
}

ETuint CreateProgram (void)
{
    ETuint ret = glCreateProgram();
    GetError(__FUNCTION__);
    logFunction(__FUNCTION__+std::string(" -> ")+std::to_string(ret));
    return ret;
}

void AttachShader (ETuint program, ETuint shader)
{
    glAttachShader (program, shader);
    GetError(__FUNCTION__);
    logFunction(__FUNCTION__ + std::string("program: ")+std::to_string(program)+std::string(" shader: ")+std::to_string(shader));
}

void BindAttribLocation (ETuint program, ETuint index, const ETchar *name)
{
    glBindAttribLocation (program, index, name);
    GetError(__FUNCTION__);
    logFunction(__FUNCTION__+std::string(" ")+std::to_string(program)+ " "+std::to_string(index)+" "+std::string(name));
}

void LinkProgram (ETuint program)
{
    glLinkProgram (program);
    GetError(__FUNCTION__);
    logFunction(__FUNCTION__ + std::string(" ") + std::to_string(program));
}

void GetProgramiv (ETuint program, ETenum pname, ETint *params)
{
    glGetProgramiv (program, pname, params);
    GetError(__FUNCTION__);
    logFunction(__FUNCTION__);
}

void PointSize (ETfloat size)
{
    glPointSize(size);
    GetError(__FUNCTION__);
    logFunction(__FUNCTION__);
}

void Enable (ETenum cap)
{
    glEnable(cap);
    if (GetError(__FUNCTION__))
        std::cout<<std::to_string(cap)<<std::endl;
    logFunction(__FUNCTION__);
    
}

void GenBuffers (ETsizei n, ETuint *buffers)
{
    glGenBuffers (n, buffers);
    GetError(__FUNCTION__);
    logFunction(__FUNCTION__+std::string(" ")+std::to_string(*buffers));
}

void BlendFunc (ETenum sfactor, ETenum dfactor)
{
    glBlendFunc (sfactor, dfactor);
    GetError(__FUNCTION__);
    logFunction(__FUNCTION__);
}

void BufferSubData (ETenum target, ETintptr offset, ETsizeiptr size, const ETvoid *data)
{
    glBufferSubData (target, offset, size, data);
    GetError(__FUNCTION__);
    std::stringstream stream;
    stream << std::hex << (long int)data;
    std::string result( stream.str() );
    logFunction(__FUNCTION__+std::string(" size: ")+std::to_string(size) + std::string(" address: ") + result);
}

void DrawArrays (ETenum mode, ETint first, ETsizei count)
{
    glDrawArrays (mode, first, count);
    GetError(__FUNCTION__);
    logFunction(__FUNCTION__+std::string(" count. ") + std::to_string(count));
}

void Disable (ETenum cap)
{
    glDisable (cap);
    GetError(__FUNCTION__);
    logFunction(__FUNCTION__);
}

void LineWidth(float w)
{
    glLineWidth(w);
    GetError(__FUNCTION__);
    logFunction(__FUNCTION__);
}

ETint GetAttribLocation (ETuint program, const ETchar *name)
{
    ETint ret = glGetAttribLocation(program, name);
    GetError(__FUNCTION__);
    logFunction(__FUNCTION__ + std::string(" ")+name+" " + std::to_string(ret));

    return ret;
}

}