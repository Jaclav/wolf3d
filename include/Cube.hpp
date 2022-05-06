#ifndef CUBE_HPP
#define CUBE_HPP

#include "Object.hpp"

class Cube : public Object {
public:
    Cube();
    Cube(glm::vec3 position);

    void draw(glm::mat4 transformation);
    void setPosition(glm::vec3 position);
    void setTexture(std::string path, bool smooth = false);

private:
    glm::vec3 position;

    GLuint pointsVbo = 0;
    GLuint texturePositionVbo = 0;
    GLuint vao = 0;

    sf::Shader mShader;
    sf::Texture mTexture;

    const GLfloat points[108] = {
        -0.5, 0, 0.5,
            0.5, 0, 0.5,
            0.5, 1, 0.5,
            0.5, 1, 0.5,
            -0.5, 1, 0.5,
            -0.5, 0, 0.5,

            0.5, 0, 0.5,
            0.5, 0, -0.5,
            0.5, 1, -0.5,
            0.5, 1, -0.5,
            0.5, 1, 0.5,
            0.5, 0, 0.5,

            -0.5, 1, -0.5,
            -0.5, 1, 0.5,
            0.5, 1, 0.5,
            0.5, 1, 0.5,
            0.5, 1, -0.5,
            -0.5, 1, -0.5,

            -0.5, 0, -0.5,
            -0.5, 0, 0.5,
            -0.5, 1, 0.5,
            -0.5, 1, 0.5,
            -0.5, 1, -0.5,
            -0.5, 0, -0.5,

            -0.5, 1, -0.5,
            0.5, 1, -0.5,
            0.5, 0, -0.5,
            0.5, 0, -0.5,
            -0.5, 0, -0.5,
            -0.5, 1, -0.5,

            -0.5, 0, 0.5,
            -0.5, 0, -0.5,
            0.5, 0, -0.5,
            0.5, 0, -0.5,
            0.5, 0, 0.5,
            -0.5, 0, 0.5
        };

    const GLfloat texturePosition[108] = {
        1, 1,
        0, 1.0, // E
        0, 0, // A
        0, 0, // F
        1.0, 0, // B
        1, 1,

        1, 1,
        0, 1.0, // E
        0, 0, // A
        0, 0, // F
        1.0, 0, // B
        1, 1,

        0, 0, // A
        1.0, 0, // B
        1.0, 1.0, // C
        1.0, 1.0, // D
        0, 1.0, // E
        0, 0, // F

        1, 1,
        0, 1.0, // E
        0, 0, // A
        0, 0, // F
        1.0, 0, // B
        1, 1,

        0, 0, // A
        1.0, 0, // B
        1.0, 1.0, // C
        1.0, 1.0, // D
        0, 1.0, // E
        0, 0, // F

        //TODO: good way, change points
        1.0, 1.0, // C
        1.0, 0, // B
        0, 0, // A
        0, 0, // F
        0, 1.0, // E
        1.0, 1.0 // D
    };
};

#endif //CUBE_HPP