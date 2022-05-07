#include "Flat.hpp"
#include "GUI.hpp"

Flat::Flat() {
    glGenBuffers(1, &mVbo);
    glBindBuffer(GL_ARRAY_BUFFER, mVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(mPoints), mPoints, GL_STATIC_DRAW);

    glGenBuffers(1, &mTextureVbo);
    glBindBuffer(GL_ARRAY_BUFFER, mTextureVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(mTexturePoints), &mTexturePoints, GL_STATIC_DRAW);

    glGenVertexArrays(1, &mVao);
    glBindVertexArray(mVao);

    glBindBuffer(GL_ARRAY_BUFFER, mVbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, mTextureVbo);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(1);

    assert(mShader.loadFromFile("rsc/shaders/block.vert", "rsc/shaders/block.frag"));
    return;
}

void Flat::draw(glm::mat4 transformation) {
    float angle = std::asin((cameraPosition.x - position.x) /
                            std::sqrt(std::pow(position.x - cameraPosition.x, 2) +
                                      std::pow(position.z - cameraPosition.z, 2)));
    if(cameraPosition.z < position.z) {
        if(cameraPosition.x < position.x)
            angle = -M_PI - angle;
        else if(cameraPosition.x > position.x)
            angle = M_PI - angle;
    }

    mShader.setUniform("transformation", sf::Glsl::Mat4(glm::value_ptr(glm::rotate(
                           glm::translate(transformation, position),
                           angle,
                           glm::vec3(0, 1, 0)))));
    sf::Shader::bind(&mShader);
    glBindVertexArray(mVao);
    glDrawArrays(GL_TRIANGLES, 0, sizeof(mPoints) / 3);
}

void Flat::setPosition(glm::vec3 position) {
    Flat::position = position;
}

void Flat::setTexture(std::string path, bool smooth) {
    if(!mTexture.loadFromFile(path)) {
        assert(mTexture.loadFromFile("rsc/notFound.png"));
    }
    mTexture.setSmooth(smooth);
    mShader.setUniform("texture", mTexture);
}
