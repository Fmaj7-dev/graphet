
#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera 
{
public:
    Camera() = default;
    Camera(float fov, size_t width, size_t height, float near, float far);

    void moveForward(float);
    void rotate(float);

    float* getProjectionPtr();
    float* getViewPtr();

private:
    float fov_;
    size_t width_;
    size_t height_;
    float near_;
    float far_;
    
    glm::vec3 position_;
    glm::vec3 lookAt_;
    glm::vec3 up_;

    glm::mat4 projection_;
    glm::mat4 view_;
};

#endif
