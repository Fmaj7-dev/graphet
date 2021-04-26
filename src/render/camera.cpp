#include "camera.h"

Camera::Camera(float fov, size_t width, size_t height, float near, float far)
 : fov_(fov),
   width_(width),
   height_(height),
   near_(near),
   far_(far),
   position_( glm::vec3(0.0f, 0.0f, 3.0f) ),
   front_( glm::vec3(0.0f, 0.0f, -1.0f) ),
   up_( glm::vec3(0.0f, 1.0f, 0.0f) )
{
    /*direction_ = glm::normalize( position_ - target_ );
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); 
    glm::vec3 right = glm::normalize( glm::cross( up, direction_ ) );

    up_ = glm::cross( direction_, right );*/

    projection_ = glm::perspective( glm::radians(fov), (float)width_ / (float)height_, near, far );
}

float* Camera::getProjectionPtr()
{
    return glm::value_ptr(projection_);
}

float* Camera::getViewPtr()
{
    /*static float time = 0.0f;
    time += 0.001f;

    // view
    view_ = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    float radius = 1.0f;
    float camX   = sin(time) * radius;
    float camZ   = cos(time) * radius;
    view_ = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    return glm::value_ptr(view_);*/

    view_ = glm::lookAt( position_, position_ + front_, up_ );
    return glm::value_ptr(view_);
}

void Camera::moveForward(float speed)
{
    position_ += speed * front_;
}

void Camera::moveBackward(float speed)
{
    position_ -= speed * front_;
}

void Camera::moveLeft(float speed)
{
    position_ -= glm::normalize(glm::cross(front_, up_)) * speed;
}

void Camera::moveRight(float speed)
{
    position_ += glm::normalize(glm::cross(front_, up_)) * speed;
}
