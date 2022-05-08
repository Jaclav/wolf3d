#ifndef FLAT_HPP
#define FLAT_HPP

#include "Object.hpp"
#include "Camera.hpp"
#include <cmath>

class Flat : public Object {
public:
    Flat();
    void draw(glm::mat4 transformation);
    void setCamera(const Camera *camera);
    void setPosition(glm::vec3 position);
    void setTexture(std::string path, bool smooth = false);

private:
    glm::vec3 position;
	const Camera *camera;
    sf::Texture mTexture;
    sf::Shader mShader;

    GLuint mVbo = 0;
    GLuint mTextureVbo = 0;
    GLuint mVao = 0;

    const GLfloat mPoints[18] = {
        -0.5, 0, 0,
            0.5, 0, 0,
            0.5, 1, 0,
            0.5, 1, 0,
            -0.5, 1, 0,
            -0.5, 0, 0,
        };

    const GLfloat mTexturePoints[12] = {
        0, 1,
        1, 1,
        1, 0,
        1, 0,
        0, 0,
        0, 1
    };
};

#endif //2D_HPP