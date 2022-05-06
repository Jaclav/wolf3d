#ifndef FLOOR_HPP
#define FLOOR_HPP

#include "Object.hpp"

class Floor : public Object {
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
        0, 0, 0,
        0, 0, 1,
        1, 0, 1,

        1, 0, 1,
        1, 0, 0,
        0, 0, 0
    };

    const GLfloat mTexturePoints[12] = {
        0, 0,
        1, 0,
        1, 1,
        1, 1,
        0, 1,
        0, 0
    };
};

#endif //FLOOR_HPP