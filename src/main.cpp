//TODO: add enemies as Flat object with two siedes.
#include <cmath>
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SFML/Graphics.hpp>
#include "Cube.hpp"
#include "Floor.hpp"
#include "Flat.hpp"
#include "GUI.hpp"

bool noclip = false;

bool collision(char block) {
    if(block == ' ' || block == 'l' || noclip)
        return false;
    return true;
}

int main() {
    static const std::string startMessage("Starting compilation: " + std::string(__DATE__) + " - " + std::string(__TIME__));
    GUI::print(std::wstring(startMessage.begin(), startMessage.end()));

    sf::Window window(sf::VideoMode::getDesktopMode(), "Wolf3D", sf::Style::Fullscreen, sf::ContextSettings(24, 8, 8, 4, 6));
    window.setFramerateLimit(60);
    window.setMouseCursorVisible(false);
    window.setVerticalSyncEnabled(true);

    sf::Event event;

    glewInit();
    glClearColor(0.2, 0.3, 0.3, 1);

    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glPointSize(20.0);
    glLineWidth(10.0);

    std::vector<std::string> map = {"#@@@####!!",
                                    "@  b@     !",
                                    "@   @  s  !",
                                    "@   @     !",
                                    "%  b!  #! !",
                                    "@  !!  #! !",
                                    "@      #! !",
                                    "$$ $$$$ ! !",
                                    "$      !! !",
                                    "$   $  % l!",
                                    "$   $  !! !",
                                    "$ $$$$$$! !",
                                    "@     b$! !",
                                    "@   l  $! !",
                                    "@      $! !",
                                    "@   l  $! !",
                                    "@      $! !",
                                    "@   l     !",
                                    "@@@@@@@@s!",
                                    "        @",
                                   };//! (x,y) element of map is map[z][x]

    for(int i = 0; i < 10; i++)
        map.insert(map.end() - 3, "@      $! !");

    std::vector<glm::vec3>positions;
    for(unsigned int z = 0; z < map.size(); z++) {
        for(unsigned int x = 0; x < map[z].size(); x++) {
            if(map[z][x] != ' ')
                positions.push_back(glm::vec3(x, 0, z));
        }
    }

    //Cube
    Cube brick;
    brick.setTexture("rsc/Brick.jpg", true);

    Cube wood;
    wood.setTexture("rsc/wood.png");

    Cube redBrick;
    redBrick.setTexture("rsc/redbrick.png");

    Cube blueStone;
    blueStone.setTexture("rsc/bluestone.png");

    Cube eagle;
    eagle.setTexture("rsc/eagle.png");

    Cube notFound;
    notFound.setTexture("rsc/notFound.png");

    Cube stasio;
    stasio.setTexture("rsc/stasio.png", true);

    Flat light;
    light.setTexture("rsc/greenlight.png");

    Flat barrel;
    barrel.setTexture("rsc/barrel.png");

    //floor
    Floor floor;

    //camera
    sf::Clock gravityClock;
    glm::vec3 velocity = glm::vec3(0.03); //! X is velocity for X and Z
    glm::vec3 direction(0.0, 0, 0);
    glm::vec3 right(0, 0, 0);
    glm::vec3 cameraPos(2, 0, 3);

    glm::mat4 viewMatrix = glm::lookAt(cameraPos, cameraPos + direction, glm::cross(right, direction));

    float P1 = 0.1f;
    float P2 = 100.0f;
    float FOV = 70.0f;
    float aspect = (float)window.getSize().x / (float)window.getSize().y;

    glm::mat4 perspectiveMatrix = glm::perspective(FOV, aspect, P1, P2);

    float vertical_angle = 0;
    float horizontalAngle = 0;
    sf::Mouse::setPosition(sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2));
    sf::Clock mouseClock;

    //dimension lines
    sf::Shader positionShader;
    assert(positionShader.loadFromFile("rsc/shaders/position.vert", "rsc/shaders/position.frag"));

    //GUI
    GUI gui(window);
    bool showGUI = false;

    while(window.isOpen()) {
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();

            if(event.type == sf::Event::KeyPressed) {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
                    noclip = !noclip;
                    gravityClock.restart();
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Tilde)) {
                    showGUI = !showGUI;
                    break;
                }
            }

            //*mouse
            if(event.type == event.MouseMoved) {
                horizontalAngle += float((int)window.getSize().x / 2 -
                                         sf::Mouse::getPosition().x) / (float)window.getSize().x;
                vertical_angle += float((int)window.getSize().y / 2 -
                                        sf::Mouse::getPosition().y) / (float)window.getSize().y;

                if(horizontalAngle > M_PI)
                    horizontalAngle = -M_PI + fmod(horizontalAngle, M_PI);

                if(horizontalAngle < -M_PI)
                    horizontalAngle = M_PI + fmod(horizontalAngle, M_PI);

                if(vertical_angle < -M_PI / 2)
                    vertical_angle = -M_PI / 2;

                if(vertical_angle > M_PI / 2)
                    vertical_angle = M_PI / 2;

                direction = glm::vec3(cos(vertical_angle) * sin(horizontalAngle),
                                      sin(vertical_angle),
                                      cos(vertical_angle) * cos(horizontalAngle));
                right = glm::vec3(-cos(horizontalAngle), 0,
                                  sin(horizontalAngle));

                if(mouseClock.getElapsedTime().asMilliseconds() > 50) {
                    sf::Mouse::setPosition(sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2));
                    mouseClock.restart();
                }
            }
            if(event.type == sf::Event::MouseWheelMoved) {
                if(event.mouseWheel.delta > 0 && FOV > 69.3f)
                    FOV -= 0.1f;
                else if(event.mouseWheel.delta < 0 && FOV < 72.1)
                    FOV += 0.1f;
                perspectiveMatrix = glm::perspective(FOV, aspect, P1, P2);
            }
        }//end event

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
            velocity.x = 0.06;
        }
        else {
            velocity.x = 0.03;
        }

        //moving
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            if(!noclip) {
                /*if(horizontalAngle > 0) {
                    if(map[(int)cameraPos.z][(int)cameraPos.x + 1] == ' ')
                        cameraPos += glm::vec3(direction.x, 0, 0) * velocity.x;
                    else {
                        cameraPos.x = ((int)cameraPos.x);
                    }
                }

                if(horizontalAngle < 0) {
                    if(map[(int)cameraPos.z][(int)cameraPos.x - 1] == ' ')
                        cameraPos += glm::vec3(direction.x, 0, 0) * velocity.x;
                    else {
                        cameraPos.x = ((int)cameraPos.x);
                    }
                }

                if(horizontalAngle < M_PI / 2 && horizontalAngle > -M_PI / 2) {
                    if(map[(int)cameraPos.z + 1][(int)cameraPos.x] == ' ')
                        cameraPos += glm::vec3(0, 0, direction.z) * velocity.x;
                    else {
                        cameraPos.z = cameraPos.z;
                    }
                }

                if(horizontalAngle < -M_PI / 2 || horizontalAngle > M_PI / 2) {
                    if(map[(int)cameraPos.z - 1][(int)cameraPos.x] == ' ')
                        cameraPos += glm::vec3(0, 0, direction.z) * velocity.x;
                    else {
                        cameraPos.z = (int)cameraPos.z;
                    }
                }*/

                cameraPos += glm::vec3(direction.x, 0, direction.z) * velocity.x * 1.6f;
                if(collision(map[(int)std::round(cameraPos.z)][(int)std::round(cameraPos.x)]))
                    cameraPos -= glm::vec3(direction.x, 0, direction.z) * velocity.x * 2.0f;
            }
            else
                cameraPos += direction * velocity.x;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            if(!noclip) {
                cameraPos -= glm::vec3(direction.x, 0, direction.z) * velocity.x;
                if(collision(map[(int)std::round(cameraPos.z)][(int)std::round(cameraPos.x)]))
                    cameraPos += glm::vec3(direction.x, 0, direction.z) * velocity.x * 1.6f;
            }
            else
                cameraPos -= direction * velocity.x;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            cameraPos -= right * velocity.x;
            if(collision(map[(int)std::round(cameraPos.z)][(int)std::round(cameraPos.x)]))
                cameraPos += right * velocity.x * 1.6f;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            cameraPos += right * velocity.x;
            if(collision(map[(int)std::round(cameraPos.z)][(int)std::round(cameraPos.x)]))
                cameraPos -= right * velocity.x * 1.6f;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            if(velocity.y == 0)
                velocity.y = 3;
            if(!!noclip)
                cameraPos += glm::vec3(0, 0.3, 0);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
            cameraPos += glm::vec3(0, -0.1, 0);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            horizontalAngle -= 0.06;
            if(horizontalAngle > M_PI)
                horizontalAngle = -M_PI + fmod(horizontalAngle, M_PI);

            if(horizontalAngle < -M_PI)
                horizontalAngle = M_PI + fmod(horizontalAngle, M_PI);

            direction = glm::vec3(cos(vertical_angle) * sin(horizontalAngle),
                                  sin(vertical_angle),
                                  cos(vertical_angle) * cos(horizontalAngle));
            right = glm::vec3(-cos(horizontalAngle), 0,
                              sin(horizontalAngle));
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            horizontalAngle += 0.06;
            if(horizontalAngle > M_PI)
                horizontalAngle = -M_PI + fmod(horizontalAngle, M_PI);

            if(horizontalAngle < -M_PI)
                horizontalAngle = M_PI + fmod(horizontalAngle, M_PI);

            direction = glm::vec3(cos(vertical_angle) * sin(horizontalAngle),
                                  sin(vertical_angle),
                                  cos(vertical_angle) * cos(horizontalAngle));
            right = glm::vec3(-cos(horizontalAngle), 0,
                              sin(horizontalAngle));
        }

        //!noclip
        if(!noclip) {
            if(cameraPos.y > 0.5)
                velocity.y -= gravityClock.getElapsedTime().asMilliseconds() / 1000.0f * 10;
            cameraPos.y += velocity.y * gravityClock.getElapsedTime().asMilliseconds() / 1000.0f;
            gravityClock.restart();
        }

        //cannot go under ground
        if(cameraPos.y < 0.5 && !noclip) {
            cameraPos.y = 0.5;
            velocity.y = 0;
        }

        //drawing
        viewMatrix = glm::lookAt(cameraPos, cameraPos + direction, glm::cross(right, direction));
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //floor
        for(int x = 0; x < 10; x++) {
            for(int z = 0; z < 30; z++) {
                floor.setPosition(glm::vec3(x, 0, z));
                floor.draw(perspectiveMatrix * viewMatrix);
            }
        }

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
            //TODO: don't draw not displayed cubes
            switch(map[(int)i.z][(int)i.x]) {
            case '#': {
                brick.setPosition(i);
                brick.draw(perspectiveMatrix * viewMatrix);
            }
            break;
            case '!': {
                wood.setPosition(i);
                wood.draw(perspectiveMatrix * viewMatrix);
            }
            break;
            case '@': {
                redBrick.setPosition(i);
                redBrick.draw(perspectiveMatrix * viewMatrix);
            }
            break;
            case '$': {
                blueStone.setPosition(i);
                blueStone.draw(perspectiveMatrix * viewMatrix);
            }
            break;
            case '%': {
                eagle.setPosition(i);
                eagle.draw(perspectiveMatrix * viewMatrix);
            }
            break;
            case 's': {
                stasio.setPosition(i);
                stasio.draw(perspectiveMatrix * viewMatrix);
            }
            break;
            case 'l': {
                light.setPosition(i);
                light.draw(perspectiveMatrix * viewMatrix, cameraPos);
            }
            break;
            case 'b': {
                barrel.setPosition(i);
                barrel.draw(perspectiveMatrix * viewMatrix, cameraPos);
            }
            break;
            default: {
                notFound.setPosition(i);
                notFound.draw(perspectiveMatrix * viewMatrix);
            }
            }
        }
        if(showGUI) {
            //dimension lines
            sf::Shader::bind(&positionShader);
            positionShader.setUniform("transformation", sf::Glsl::Mat4(glm::value_ptr(
                                          perspectiveMatrix * viewMatrix)));

            glBegin(GL_POINTS);
            glVertex3f(0.0, 0, 0);
            glEnd();

            glBegin(GL_LINES);
            glVertex3f(0, 0, 0);
            glVertex3f(1, 0, 0);

            glVertex3f(0, 0, 0);
            glVertex3f(0, 1, 0);

            glVertex3f(0, 0, 0);
            glVertex3f(0, 0, 1);
            glEnd();

            gui.draw(window, L"X = " + std::to_wstring(cameraPos.x) +
                     L"\nY = " + std::to_wstring(cameraPos.y) +
                     L"\nZ = " + std::to_wstring(cameraPos.z) +
                     L"\nθ = " + std::to_wstring(horizontalAngle * 180 / M_PI) +
                     L"\nφ = " + std::to_wstring(vertical_angle * 180 / M_PI) +
                     L"\nFOV = " + std::to_wstring(FOV));
        }

        window.display();
    }
    return 0;
}
