#include "Floor.hpp"

Floor::Floor() {
    glGenBuffers(1, &floorVbo);
    glBindBuffer(GL_ARRAY_BUFFER, floorVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(floorPoints), floorPoints, GL_STATIC_DRAW);

    glGenBuffers(1, &floorTextureVbo);
    glBindBuffer(GL_ARRAY_BUFFER, floorTextureVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(floorTexturePoints), &floorTexturePoints, GL_STATIC_DRAW);

    glGenVertexArrays(1, &floorVao);
    glBindVertexArray(floorVao);

    glBindBuffer(GL_ARRAY_BUFFER, floorVbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, floorTextureVbo);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(1);

    assert(floorShader.loadFromFile("rsc/shaders/block.vert", "rsc/shaders/block.frag"));

    floorTexture.loadFromFile("rsc/colorstone.png");
    floorShader.setUniform("texture2D", floorTexture);
}

void Floor::draw(glm::mat4 transformation) {
    sf::Shader::bind(&floorShader);
    floorShader.setUniform("transformation", sf::Glsl::Mat4(glm::value_ptr(glm::translate(transformation, position))));
    glBindVertexArray(floorVao);
    glDrawArrays(GL_TRIANGLES, 0, sizeof(floorPoints) / 3);
}

void Floor::setPosition(glm::vec3 position) {
    Floor::position = position;
}