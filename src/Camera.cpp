#include "Camera.hpp"

Camera::Camera(const sf::Window &window) : direction(0.0), right(0.0) {
    position = glm::vec3(2, 0, 3);//starting position

    viewMatrix = glm::lookAt(position, position + direction, glm::cross(right, direction));
    aspect = (float)window.getSize().x / (float)window.getSize().y;
    perspectiveMatrix =  glm::perspective(FOV, aspect, P1, P2);
}

Camera& Camera::operator+=(glm::vec3 position) {
    this->position += position;
    return *this;
}

Camera& Camera::operator-=(glm::vec3 position) {
    this->position -= position;
    return *this;
}

glm::vec3 Camera::getDirection() {
    return direction;
}

float Camera::getFOV() {
    return FOV;
}

float Camera:: getHorizontalAngle() {
    return horizontalAngle;
}

glm::vec3 Camera::getPosition() {
    return position;
}

glm::vec3 Camera::getRight() {
    return right;
}

glm::mat4 Camera::getTransformation() {
    return perspectiveMatrix * viewMatrix;
}

float Camera::getVerticalAngle() {
    return verticalAngle;
}

void Camera::setHorizontalAngle(float angle) {
    horizontalAngle = angle;
}

void Camera::setPosition(glm::vec3 position) {
    Camera::position = position;
}

void Camera::setVerticalAngle(float angle) {
    verticalAngle = angle;
}

void Camera::calculateDirectionAndRight() {
    direction = glm::vec3(cos(verticalAngle) * sin(horizontalAngle),
                          sin(verticalAngle),
                          cos(verticalAngle) * cos(horizontalAngle));
    right = glm::vec3(-cos(horizontalAngle), 0,
                      sin(horizontalAngle));
}

void Camera::calculateView() {
    viewMatrix = glm::lookAt(position, position + direction, glm::cross(right, direction));
}


void Camera::incFOV() {
    if(FOV > 69.3f)
        FOV -= 0.1f;
    perspectiveMatrix = glm::perspective(FOV, aspect, P1, P2);
}

void Camera::decFOV() {
    if(FOV < 72.1)
        FOV += 0.1f;
    perspectiveMatrix = glm::perspective(FOV, aspect, P1, P2);
}
