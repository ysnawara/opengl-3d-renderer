#include "camera.h"

#include <algorithm>
#include <cmath>

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : Front(glm::vec3(0.0f, 0.0f, -1.0f))
    , MovementSpeed(CameraDefaults::SPEED)
    , MouseSensitivity(CameraDefaults::SENSITIVITY)
    , Zoom(CameraDefaults::ZOOM)
    , Position(position)
    , WorldUp(up)
    , Yaw(yaw)
    , Pitch(pitch)
{
    updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(Position, Position + Front, Up);
}

void Camera::processKeyboard(CameraMovement direction, float deltaTime) {
    float velocity = MovementSpeed * deltaTime;

    switch (direction) {
        case FORWARD:  Position += Front   * velocity; break;
        case BACKWARD: Position -= Front   * velocity; break;
        case LEFT:     Position -= Right   * velocity; break;
        case RIGHT:    Position += Right   * velocity; break;
        case UP:       Position += WorldUp * velocity; break;
        case DOWN:     Position -= WorldUp * velocity; break;
    }
}

void Camera::processMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw   += xoffset;
    Pitch += yoffset;

    if (constrainPitch) {
        Pitch = std::clamp(Pitch, -89.0f, 89.0f);
    }

    updateCameraVectors();
}

void Camera::processMouseScroll(float yoffset) {
    Zoom -= yoffset;
    Zoom  = std::clamp(Zoom, 1.0f, 120.0f);
}

void Camera::updateCameraVectors() {
    glm::vec3 front;
    front.x = std::cos(glm::radians(Yaw)) * std::cos(glm::radians(Pitch));
    front.y = std::sin(glm::radians(Pitch));
    front.z = std::sin(glm::radians(Yaw)) * std::cos(glm::radians(Pitch));
    Front   = glm::normalize(front);

    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up    = glm::normalize(glm::cross(Right, Front));
}
