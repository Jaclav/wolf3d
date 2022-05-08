#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SFML/Window/Window.hpp>

class Camera {
public:
    Camera(const sf::Window &window);

    Camera& operator+=(glm::vec3 position);
    Camera& operator-=(glm::vec3 position);

    glm::vec3 getDirection();
    float getFOV();
    float getHorizontalAngle();
    glm::vec3 getPosition() const;
    glm::vec3 getRight();
    glm::mat4 getTransformation();
    float getVerticalAngle();

    void setHorizontalAngle(float angle);
    void setPosition(glm::vec3 position);
    void setVerticalAngle(float angle);

    void calculateDirectionAndRight();
    void calculateView();

    void incFOV();
    void decFOV();

private:
    glm::vec3 direction;
    glm::vec3 right;
    glm::vec3 position;

    glm::mat4 viewMatrix;

    float P1 = 0.1f;
    float P2 = 100.0f;
    float FOV = 70.0f;
    float aspect;

    glm::mat4 perspectiveMatrix;

    float verticalAngle = 0;
    float horizontalAngle = 0;
};

#endif //CAMERA_HPP