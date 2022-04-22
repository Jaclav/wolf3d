#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Texture.hpp>

class Object {
    virtual void draw(glm::mat4 transformation) = 0;
    virtual void setPosition(glm::vec3 position) = 0;
};

#endif //OBJECT_HPP