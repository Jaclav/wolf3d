#ifndef CUBE_HPP
#define CUBE_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Texture.hpp>

static const GLfloat points[] = {
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

        -0.5, 0, -0.5,
        -0.5, 1, -0.5,
        0.5, 1, -0.5,
        0.5, 1, -0.5,
        0.5, 0, -0.5,
        -0.5, 0, -0.5,

        -0.5, 0, 0.5,
        -0.5, 0, -0.5,
        0.5, 0, -0.5,

        0.5, 0, -0.5,
        0.5, 0, 0.5,
        -0.5, 0, 0.5,
    };

static const GLfloat texturePosition[] = {
    0, 0, // A
    1.0, 0, // B
    1.0, 1.0, // C
    1.0, 1.0, // D
    0, 1.0, // E
    0, 0, // F

    0, 0, // A
    1.0, 0, // B
    1.0, 1.0, // C
    1.0, 1.0, // D
    0, 1.0, // E
    0, 0, // F

    0, 0, // A
    1.0, 0, // B
    1.0, 1.0, // C
    1.0, 1.0, // D
    0, 1.0, // E
    0, 0, // F

    0, 0, // A
    1.0, 0, // B
    1.0, 1.0, // C
    1.0, 1.0, // D
    0, 1.0, // E
    0, 0, // F

    0, 0, // A
    1.0, 0, // B
    1.0, 1.0, // C
    1.0, 1.0, // D
    0, 1.0, // E
    0, 0, // F

    0.0, 0, // A
    1.0, 0, // B
    1.0, 1.0, // C
    1.0, 1.0, // D
    0, 1.0, // E
    0, 0, // F
};


class Cube {
public:
    Cube();
    Cube(glm::vec3 position);

    void draw(glm::mat4 transformation);
    void setPosition(glm::vec3 position);
    void setTexture(std::string path);

private:
    glm::vec3 position;

    GLuint pointsVbo = 0;
    GLuint texturePositionVbo = 0;
    GLuint vao = 0;

    sf::Shader mShader;
    sf::Texture mTexture;
};

#endif //CUBE_HPP