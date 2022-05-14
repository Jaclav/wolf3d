#include "Flat.hpp"

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
    setTexture("rsc/notFound.png");
}

Flat& Flat::operator=(const Flat &other) {
    this->position = other.position;
    this->camera = other.camera;
    this->mTexture = other.mTexture;
    assert(this->mShader.loadFromFile("rsc/shaders/block.vert", "rsc/shaders/block.frag"));
    this->mShader.setUniform("texture", this->mTexture);

    this->mVbo = other.mVbo;
    this->mTextureVbo = other.mTextureVbo;
    this->mVao = other.mVao;
    return *this;
}

void Flat::setCamera(const Camera *camera) {
    Flat::camera = camera;
}

void Flat::draw(glm::mat4 transformation) {
    float angle = std::asin((camera->getPosition().x - position.x) /
                            std::sqrt(std::pow(position.x - camera->getPosition().x, 2) +
                                      std::pow(position.z - camera->getPosition().z, 2)));
    if(camera->getPosition().z < position.z) {
        if(camera->getPosition().x < position.x)
            angle = -M_PI - angle;
        else if(camera->getPosition().x > position.x)
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

void Flat::setTexture(const sf::Texture &texture) {
    mTexture = texture;
    mShader.setUniform("texture", mTexture);
}