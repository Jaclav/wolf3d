#include "Enemy.hpp"

Enemy::Enemy() {
    Flat();
}

Enemy::Enemy(const Enemy &other) {
    flat = other.flat;
    mTexture = other.mTexture;
}

void Enemy::draw(glm::mat4 transformation) {
    flat.draw(transformation);
}

void Enemy::setCamera(const Camera *camera) {
    flat.setCamera(camera);
}

void Enemy::setPosition(glm::vec3 position) {
    flat.setPosition(position);
}

void Enemy::setTexture(std::string path, bool smooth) {
    if(!mTexture.loadFromFile(path)) {
        assert(mTexture.loadFromFile("rsc/notFound.png"));
    }
    mTexture.setSmooth(smooth);

    sf::Texture tmp;
    sf::Image img;

    img = mTexture.copyToImage();
    tmp.loadFromImage(img, sf::IntRect(0, 0, 64, 64));
    flat.setTexture(tmp);
}