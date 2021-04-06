
#ifndef GL_WRAPPER_H
#define GL_WRAPPER_H

#ifdef __APPLE__
   #define GL_SILENCE_DEPRECATION
   #include <GLUT/glut.h>
#else
    #define GL_GLEXT_PROTOTYPES
    #include <GL/glut.h>
#endif

#include <string>

#define ET_COLOR_BUFFER_BIT               0x00004000
#define ET_COMPILE_STATUS                 0x8B81
#define ET_INFO_LOG_LENGTH                0x8B84

// I hate wrapping this, but I need it to log the errors.
// as I am getting something strange somewhere...
namespace render
{
    typedef int32_t  ETint;
    typedef uint32_t ETuint;
    typedef uint8_t  ETubyte;
    typedef uint32_t ETenum;
    typedef float    ETclampf;
    typedef int32_t  ETsizei;
    typedef char     ETchar;

    void GetError(std::string from="");
    void UseProgram(GLuint program);
    const GLubyte *GetString (GLenum name);
    void printInfo();

    void ClearColor (ETclampf red, ETclampf green, ETclampf blue, ETclampf alpha);
    void Viewport (ETint x, ETint y, ETsizei width, ETsizei height);

    void Clear (GLbitfield mask);

    ETuint CreateShader(ETenum type);

    void ShaderSource(ETuint shader, ETsizei count, const ETchar* const *string, const ETint *length);
    void CompileShader (ETuint shader);
    void GetShaderiv (ETuint shader, ETenum pname, ETint *params);
    void GetShaderInfoLog (ETuint shader, ETsizei bufSize, ETsizei* length, ETchar *infoLog);
    void DeleteShader (ETuint shader);
}

#endif