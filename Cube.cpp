#include "Cube.hpp"
#include <iostream>

Cube::Cube() {
    glGenBuffers(1, &pointsVbo);
    glBindBuffer(GL_ARRAY_BUFFER, pointsVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    glGenBuffers(1, &texturePositionVbo);
    glBindBuffer(GL_ARRAY_BUFFER, texturePositionVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texturePosition), &texturePosition, GL_STATIC_DRAW);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, pointsVbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, texturePositionVbo);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(1);

    assert(mShader.loadFromFile("rsc/shaders/block.vert", "rsc/shaders/block.frag"));

    setTexture("rsc/notFound.png");
}

Cube::Cube(glm::vec3 position) : Cube() {
    setPosition(position);
}

void Cube::draw(glm::mat4 transformation) {
    sf::Shader::bind(&mShader);
    mShader.setUniform("transformation", sf::Glsl::Mat4(glm::value_ptr(glm::translate(transformation, position))));

    glBindVertexArray(vao);
	//TODO: don't draw not displayed walls
    glDrawArrays(GL_TRIANGLES, 0, sizeof(points) / 3);
}

void Cube::setPosition(glm::vec3 position) {
    Cube::position = position;
}

void Cube::setTexture(std::string path) {
    if(!mTexture.loadFromFile(path)) {
        assert(mTexture.loadFromFile("rsc/notFound.png"));
    }
    mShader.setUniform("texture", mTexture);
}