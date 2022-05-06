#include "Floor.hpp"

Floor::Floor() {
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

    mTexture.loadFromFile("rsc/colorstone.png");
    mShader.setUniform("texture", mTexture);
}

void Floor::draw(glm::mat4 transformation) {
    sf::Shader::bind(&mShader);
    mShader.setUniform("transformation", sf::Glsl::Mat4(glm::value_ptr(glm::translate(transformation, position))));
    glBindVertexArray(mVao);
    glDrawArrays(GL_TRIANGLES, 0, sizeof(mPoints) / 3);
}

void Floor::setPosition(glm::vec3 position) {
    Floor::position = position;
}