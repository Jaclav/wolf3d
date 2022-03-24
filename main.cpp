#include <cmath>
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SFML/Graphics.hpp>
#include "Cube.hpp"

float fpsCounter(void) {
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

int main() {
    sf::Window window(sf::VideoMode::getDesktopMode(), "Wolf3D", sf::Style::Default, sf::ContextSettings(24, 8, 8, 4, 6));
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    sf::Event event;

    glewInit();
    glClearColor(0.2, 0.3, 0.3, 1);

    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glPointSize(20.0);

    //Cube
    Cube cube;
    cube.setTexture("rsc/Brick.jpg");
    std::vector<glm::vec3>positions;
    positions.push_back(glm::vec3(1, 0, 3));
    positions.push_back(glm::vec3(0, 0, 0));
    positions.push_back(glm::vec3(1, 0, 0));
    positions.push_back(glm::vec3(2, 0, 0));
    positions.push_back(glm::vec3(0, 0, 2));
    positions.push_back(glm::vec3(2, 0, 2));

    positions.push_back(glm::vec3(0, 1, 0));

    /*for(int x = 0; x < 100; x++) {
        for(int y = 0; y < 100; y++) {
            positions.push_back(glm::vec3(x, y, 8));
        }
    }*/

    //camera
    sf::Clock gravityClock;
    bool gravity = true;
    float velocity = 0.1;
    glm::vec3 direction(0.0, 0, 0);
    glm::vec3 right(0, 0, 0);
    glm::vec3 cameraPos(0, 0, 1);

    glm::mat4 viewMatrix = glm::lookAt(cameraPos, cameraPos + direction, glm::cross(right, direction));

    float P1 = 0.1f;
    float P2 = 100.0f;
    float FOV = 70.0f;
    float aspect = (float)window.getSize().x / (float)window.getSize().y;

    glm::mat4 perspectiveMatrix = glm::perspective(FOV, aspect, P1, P2);

    float vertical_angle = 0;
    float horizontal_angle = M_PI / 2;
    sf::Mouse::setPosition(sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2));
    sf::Clock mouseClock;

    //dimension lines
    sf::Shader positionShader;
    assert(positionShader.loadFromFile("rsc/shaders/position.vert", "rsc/shaders/position.frag"));

    while(window.isOpen()) {
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::KeyPressed) {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
                    velocity = 0.5;
                }
                else {
                    velocity = 0.1;
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                    if(gravity)
                        cameraPos += glm::vec3(direction.x, 0, direction.z) * velocity;//going forward shouldn't case jumping
                    else
                        cameraPos += direction * velocity;
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                    if(gravity)
                        cameraPos -= glm::vec3(direction.x, 0, direction.z) * velocity;
                    else
                        cameraPos -= direction * velocity;
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                    cameraPos -= right * velocity;
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                    cameraPos += right * velocity;
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                    cameraPos += glm::vec3(0, 0.4, 0);
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                    cameraPos += glm::vec3(0, -0.1, 0);
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::G))
                    gravity = !gravity;
            }//end KeyPressed

            if(event.type == event.MouseMoved) {
                horizontal_angle += float((int)window.getSize().x / 2 -
                                          sf::Mouse::getPosition().x) / (float)window.getSize().x;
                vertical_angle += float((int)window.getSize().y / 2 -
                                        sf::Mouse::getPosition().y) / (float)window.getSize().y;

                if(vertical_angle < -M_PI / 2)
                    vertical_angle = -M_PI / 2;

                if(vertical_angle > M_PI / 2)
                    vertical_angle = M_PI / 2;

                direction = glm::vec3(cos(vertical_angle) * sin(horizontal_angle),
                                      sin(vertical_angle),
                                      cos(vertical_angle) * cos(horizontal_angle));
                right = glm::vec3(-cos(horizontal_angle), 0,
                                  sin(horizontal_angle));

                if(mouseClock.getElapsedTime().asMilliseconds() > 50) {
                    sf::Mouse::setPosition(sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2));
                    mouseClock.restart();
                }
            }
            if(event.type == sf::Event::MouseWheelMoved) {
                if(event.mouseWheel.delta > 0)
                    FOV -= 0.1f;
                else if(event.mouseWheel.delta < 0)
                    FOV += 0.1f;
                perspectiveMatrix = glm::perspective(FOV, aspect, P1, P2);
            }

            //cannot go under ground
            if(cameraPos.y < 0.5 && gravity) {
                cameraPos.y = 0.5;
            }
            viewMatrix = glm::lookAt(cameraPos, cameraPos + direction, glm::cross(right, direction));
        }
        //gravity
        if(gravity && cameraPos.y > 0.5 && gravityClock.getElapsedTime().asMilliseconds() > 50) {
            cameraPos.y -= 0.05;
            gravityClock.restart();
            viewMatrix = glm::lookAt(cameraPos, cameraPos + direction, glm::cross(right, direction));
        }
        //drawing
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        std::sort(positions.begin(), positions.end(), [&](glm::vec3 a, glm::vec3 b) {
            if((a.x - cameraPos.x) * (a.x - cameraPos.x) +
                    (a.y - cameraPos.y) * (a.y - cameraPos.y) +
                    (a.z - cameraPos.z) * (a.z - cameraPos.z) >
                    (b.x - cameraPos.x) * (b.x - cameraPos.x) +
                    (b.y - cameraPos.y) * (b.y - cameraPos.y) +
                    (b.z - cameraPos.z) * (b.z - cameraPos.z))
                return true;
            return false;
        });
        for(auto i : positions) {
            cube.setPosition(i);
            //TODO: don't draw not displayed cubes
            cube.draw(perspectiveMatrix * viewMatrix);
        }

        //dimension lines
        sf::Shader::bind(&positionShader);
        positionShader.setUniform("transformation", sf::Glsl::Mat4(glm::value_ptr(
                                      perspectiveMatrix * viewMatrix)));

        glBegin(GL_POINTS);
        glVertex3f(0.0, 0, 0);
        glEnd();

       /* glBegin(GL_POINTS);
        for(float x = -5; x < 5; x += 0.03) {
            for(float y = -5; y < 5; y += 0.03) {
                glVertex3f(x, y, x * x + y * y);
            }
        }
        glEnd();*/

        glBegin(GL_LINES);
        glVertex3f(0, 0, 0);
        glVertex3f(1, 0, 0);

        glVertex3f(0, 0, 0);
        glVertex3f(0, 1, 0);

        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, 1);
        glEnd();

        window.display();
        window.setTitle(std::to_string(fpsCounter()) + "@Wolf3D" + std::to_string(FOV));
    }
}