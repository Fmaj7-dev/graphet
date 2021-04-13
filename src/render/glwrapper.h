
#ifndef GL_WRAPPER_H
#define GL_WRAPPER_H

#include <string>

#define ET_COLOR_BUFFER_BIT               0x00004000
#define ET_COMPILE_STATUS                 0x8B81
#define ET_INFO_LOG_LENGTH                0x8B84
#define ET_TRUE                           1
#define ET_FALSE                          0
#define ET_FLOAT                          0x1406
#define ET_UNSIGNED_BYTE                  0x1401
#define ET_ARRAY_BUFFER                   0x8892
#define ET_DYNAMIC_DRAW                   0x88E8
#define ET_VERTEX_SHADER                  0x8B31
#define ET_FRAGMENT_SHADER                0x8B30
#define ET_BLEND                          0x0BE2
#define ET_SRC_ALPHA                      0x0302
#define ET_ONE_MINUS_SRC_ALPHA            0x0303
#define ET_POINTS                         0x0000
#define ET_LINK_STATUS                    0x8B82



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
    typedef uint32_t ETbitfield;
    typedef intptr_t ETsizeiptr;
    typedef void     ETvoid;
    typedef uint8_t  ETboolean;
    typedef float    ETfloat;
    typedef intptr_t ETintptr;

    bool GetError(std::string from="");
    void UseProgram(ETuint program);
    const ETubyte *GetString (ETenum name);
    void printInfo();

    void ClearColor (ETclampf red, ETclampf green, ETclampf blue, ETclampf alpha);
    void Viewport (ETint x, ETint y, ETsizei width, ETsizei height);

    void Clear (ETbitfield mask);

    ETuint CreateShader(ETenum type);

    void ShaderSource(ETuint shader, ETsizei count, const ETchar* const *string, const ETint *length);
    void CompileShader (ETuint shader);
    void GetShaderiv (ETuint shader, ETenum pname, ETint *params);
    void GetShaderInfoLog (ETuint shader, ETsizei bufSize, ETsizei* length, ETchar *infoLog);
    void DeleteShader (ETuint shader);
    void BindBuffer (ETenum target, ETuint buffer);
    void BufferData (ETenum target, ETsizeiptr size, const ETvoid *data, ETenum usage);
    void VertexAttribPointer (ETuint index, ETint size, ETenum type, ETboolean normalized, ETsizei stride, const ETvoid *pointer);
    void EnableVertexAttribArray (ETuint index);

    ETuint CreateProgram (void);
    void AttachShader (ETuint program, ETuint shader);
    void BindAttribLocation (ETuint program, ETuint index, const ETchar *name);
    void LinkProgram (ETuint program);
    void GetProgramiv (ETuint program, ETenum pname, ETint *params);
    void PointSize (ETfloat size);
    void Enable (ETenum cap);
    void GenBuffers (ETsizei n, ETuint *buffers);
    void BlendFunc (ETenum sfactor, ETenum dfactor);
    void BufferSubData (ETenum target, ETintptr offset, ETsizeiptr size, const ETvoid *data);
    void DrawArrays (ETenum mode, ETint first, ETsizei count);
    void Disable (ETenum cap);
    void LineWidth(float w);

}

#endif