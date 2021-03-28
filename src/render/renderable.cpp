#include "renderable.h"
#include "utils/log.h"

#include <vector>
 #include <cassert>

GLint Renderable::LoadShader(GLenum type, const char *src)
{
    const GLuint id = glCreateShader(type);
    assert(id);
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    GLint compiled = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &compiled);
    //assert(compiled);
    etlog(std::string("* compiled: ")+std::to_string(compiled));
    if(compiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);
        etlog(&errorLog[0]);


        // Provide the infolog in whatever manor you deem best.
        // Exit with failure.
        glDeleteShader(id);
        return 0;
    }
    return id;
};