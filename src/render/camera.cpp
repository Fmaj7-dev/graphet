#include "camera.h"

Camera::Camera(float fov, size_t width, size_t height, float near, float far)
 : fov_(fov),
   width_(width),
   height_(height),
   near_(near),
   far_(far)
{
    projection = glm::perspective( glm::radians(fov), (float)width_ / (float)height_, near, far );
}

float* Camera::getProjectionPtr()
{
    return glm::value_ptr(projection);
}