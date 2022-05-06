#include "GUI.hpp"

GUI::GUI(const sf::Window &window) {
    assert(interface.create(window.getSize().x, window.getSize().y, window.getSettings()));

    assert(font.loadFromFile("rsc/DejaVuSans.ttf"));
    text.setFont(font);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(1);

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

    assert(mShader.loadFromFile("rsc/shaders/static.vert", "rsc/shaders/block.frag"));
    return;
}

void GUI::draw(const sf::Window &window, const std::wstring data) {
    mShader.setUniform("texture", interface.getTexture());
    sf::Shader::bind(&mShader);
    glBindVertexArray(mVao);
    glDrawArrays(GL_TRIANGLES, 0, sizeof(mPoints) / 3);

    window.setActive(false);
    interface.setActive(true);

    interface.clear(sf::Color::Transparent);
    text.setString(std::to_wstring(fpsCounter()) + data);
    interface.draw(text);
    interface.display();

    interface.setActive(false);
    window.setActive(true);
    return;
}

float GUI::fpsCounter(void) {
    static sf::Clock clck;
    static int numberOfSample = 0;
    static float toReturn = 0;

    numberOfSample++;

    if(clck.getElapsedTime().asMilliseconds() >= 1000) {
        toReturn = (numberOfSample * 1000.0f ) / clck.getElapsedTime().asMilliseconds();
        clck.restart();
        numberOfSample = 0;
    }

    return toReturn;
}