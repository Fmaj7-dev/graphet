#include "renderable.h"
#include "utils/log.h"

#include <vector>
#include <cassert>

render::ETint Renderable::LoadShader(render::ETenum type, const char *src)
{
    const render::ETuint id = render::CreateShader(type);
    assert(id);
    render::ShaderSource(id, 1, &src, nullptr);
    render::CompileShader(id);
    render::ETint compiled = 0;
    render::GetShaderiv(id, ET_COMPILE_STATUS, &compiled);
    //assert(compiled);
    etlog(std::string("* compiled: ")+std::to_string(compiled));
    if(compiled == ET_FALSE)
    {
        render::ETint maxLength = 0;
        render::GetShaderiv(id, ET_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<render::ETchar> errorLog(maxLength);
        render::GetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);
        etlog(&errorLog[0]);


        // Provide the infolog in whatever manor you deem best.
        // Exit with failure.
        render::DeleteShader(id);
        return 0;
    }
    return id;
};