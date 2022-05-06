//TODO: add terminal
#ifndef GUI_HPP
#define GUI_HPP

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Window.hpp>
#include "Object.hpp"

class GUI {
public:
    GUI(const sf::Window &window);
    void draw(const sf::Window &window, const std::wstring data);
    float fpsCounter(void);

private:
    sf::RenderTexture interface;
    sf::Shader mShader;

    sf::Font font;
    sf::Text text;

    GLuint mVbo = 0;
    GLuint mTextureVbo = 0;
    GLuint mVao = 0;

    const GLfloat mPoints[18] = {
        -1, -1, 0,
            1, -1, 0,
            1, 1, 0,
            1, 1, 0,
            -1, 1, 0,
            -1, -1, 0
        };

    const GLfloat mTexturePoints[12] = {
        0, 0,
        1, 0,
        1, 1,
        1, 1,
        0, 1,
        0, 0,
    };
};

#endif //GUI_HPP