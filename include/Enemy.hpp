#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Flat.hpp"

class Enemy {
public:
    Enemy();
    Enemy(const Enemy &other);
    void draw(glm::mat4 transformation);
    void setCamera(const Camera *camera);
    void setPosition(glm::vec3 position);
	void setTexture(std::string path, bool smooth = false);

private:
    Flat flat;
    sf::Texture mTexture;
};

#endif //ENEMY_HPP