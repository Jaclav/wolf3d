#ifndef FLOOR_HPP
#define FLOOR_HPP

#include "Object.hpp"

class Floor : Object {
public:
    Floor();
    void draw(glm::mat4 transformation);
    void setPosition(glm::vec3 position);

private:
    glm::vec3 position;

    GLuint mVbo = 0;
    GLuint mTextureVbo = 0;
    GLuint mVao = 0;

    sf::Shader mShader;
    sf::Texture mTexture;

    const GLfloat mPoints[18] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f,

        0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f,

    };

    const GLfloat mTexturePoints[12] = {
        0.0f, 0.0f, // A
        1.0f, 0.0f, // B
        1.0f, 1.0f, // C
        1.0f, 1.0f, // D
        0.0f, 1.0f, // E
        0.0f, 0.0f, // F
    };
};

#endif //FLOOR_HPP