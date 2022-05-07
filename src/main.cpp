//TODO: add enemies as Flat object with two siedes.
#include <cmath>
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SFML/Graphics.hpp>
#include "Cube.hpp"
#include "Camera.hpp"
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

    //camera
    sf::Clock gravityClock;
    glm::vec3 velocity = glm::vec3(0.03); //! X is velocity for X and Z
    Camera camera(window);

    sf::Mouse::setPosition(sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2));
    sf::Clock mouseClock;

    //map of blocks
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
    light.setCamera(&camera);
    light.setTexture("rsc/greenlight.png");

    Flat barrel;
    barrel.setCamera(&camera);
    barrel.setTexture("rsc/barrel.png");

    std::map<char, Object*> objects{{'#', &brick},
        {'!', &wood}, {'@', &redBrick}, {'$', &blueStone},
        {'%', &eagle}, {'s', &stasio}, {'l', &light}, {'b', &barrel}};

    //floor
    Floor floor;

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

            //mouse
            if(event.type == event.MouseMoved) {
                camera.setHorizontalAngle(camera.getHorizontalAngle() + float((int)window.getSize().x / 2 -
                                          sf::Mouse::getPosition().x) / (float)window.getSize().x);
                camera.setVerticalAngle(camera.getVerticalAngle() + float((int)window.getSize().y / 2 -
                                        sf::Mouse::getPosition().y) / (float)window.getSize().y);

                if(mouseClock.getElapsedTime().asMilliseconds() > 50) {
                    sf::Mouse::setPosition(sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2));
                    mouseClock.restart();
                }
            }
            if(event.type == sf::Event::MouseWheelMoved) {
                if(event.mouseWheel.delta > 0)
                    camera.decFOV();
                else if(event.mouseWheel.delta < 0)
                    camera.incFOV();
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
                /*if(camera.getHorizontalAngle() > 0) {
                    if(map[(int)camera.getPosition().z][(int)camera.getPosition().x + 1] == ' ')
                        cameraPosition += glm::vec3(camera.getDirection().x, 0, 0) * velocity.x;
                    else {
                        camera.getPosition().x = ((int)camera.getPosition().x);
                    }
                }

                if(camera.getHorizontalAngle() < 0) {
                    if(map[(int)camera.getPosition().z][(int)camera.getPosition().x - 1] == ' ')
                        cameraPosition += glm::vec3(camera.getDirection().x, 0, 0) * velocity.x;
                    else {
                        camera.getPosition().x = ((int)camera.getPosition().x);
                    }
                }

                if(camera.getHorizontalAngle() < M_PI / 2 && camera.getHorizontalAngle() > -M_PI / 2) {
                    if(map[(int)camera.getPosition().z + 1][(int)camera.getPosition().x] == ' ')
                        cameraPosition += glm::vec3(0, 0, camera.getDirection().z) * velocity.x;
                    else {
                        camera.getPosition().z = camera.getPosition().z;
                    }
                }

                if(camera.getHorizontalAngle() < -M_PI / 2 || camera.getHorizontalAngle() > M_PI / 2) {
                    if(map[(int)camera.getPosition().z - 1][(int)camera.getPosition().x] == ' ')
                        cameraPosition += glm::vec3(0, 0, camera.getDirection().z) * velocity.x;
                    else {
                        camera.getPosition().z = (int)camera.getPosition().z;
                    }
                }*/

                camera += glm::vec3(camera.getDirection().x, 0, camera.getDirection().z) * velocity.x * 1.6f;
                if(collision(map[(int)std::round(camera.getPosition().z)][(int)std::round(camera.getPosition().x)]))
                    camera -= glm::vec3(camera.getDirection().x, 0, camera.getDirection().z) * velocity.x * 2.0f;
            }
            else
                camera += camera.getDirection() * velocity.x;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            if(!noclip) {
                camera -= glm::vec3(camera.getDirection().x, 0, camera.getDirection().z) * velocity.x;
                if(collision(map[(int)std::round(camera.getPosition().z)][(int)std::round(camera.getPosition().x)]))
                    camera += glm::vec3(camera.getDirection().x, 0, camera.getDirection().z) * velocity.x * 1.6f;
            }
            else
                camera -= camera.getDirection() * velocity.x;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            camera -= camera.getRight() * velocity.x;
            if(collision(map[(int)std::round(camera.getPosition().z)][(int)std::round(camera.getPosition().x)]))
                camera += camera.getRight() * velocity.x * 1.6f;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            camera += camera.getRight() * velocity.x;
            if(collision(map[(int)std::round(camera.getPosition().z)][(int)std::round(camera.getPosition().x)]))
                camera -= camera.getRight() * velocity.x * 1.6f;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            if(velocity.y == 0)
                velocity.y = 3;
            if(!!noclip)
                camera += glm::vec3(0, 0.3f, 0);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
            camera += glm::vec3(0, -0.1f, 0);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            camera.setHorizontalAngle(camera.getHorizontalAngle() - 0.06f);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            camera.setHorizontalAngle(camera.getHorizontalAngle() + 0.06f);
        }

        //!noclip
        if(!noclip) {
            if(camera.getPosition().y > 0.5)
                velocity.y -= gravityClock.getElapsedTime().asMilliseconds() / 1000.0f * 10;
            camera.setPosition(glm::vec3(camera.getPosition().x, camera.getPosition().y + velocity.y * gravityClock.getElapsedTime().asMilliseconds() / 1000.0f, camera.getPosition().z));
            gravityClock.restart();
        }

        //cannot go under ground
        if(camera.getPosition().y < 0.5 && !noclip) {
            camera.setPosition(glm::vec3(camera.getPosition().x, 0.5, camera.getPosition().z));
            velocity.y = 0;
        }

        //!drawing
        camera.calculateView();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //floor
        for(int x = 0; x < 10; x++) {
            for(int z = 0; z < 30; z++) {
                floor.setPosition(glm::vec3(x, 0, z));
                floor.draw(camera.getTransformation());
            }
        }

        //blocks
        std::sort(positions.begin(), positions.end(), [&](glm::vec3 a, glm::vec3 b) {
            if((a.x - camera.getPosition().x) * (a.x - camera.getPosition().x) +
                    (a.y - camera.getPosition().y) * (a.y - camera.getPosition().y) +
                    (a.z - camera.getPosition().z) * (a.z - camera.getPosition().z) >
                    (b.x - camera.getPosition().x) * (b.x - camera.getPosition().x) +
                    (b.y - camera.getPosition().y) * (b.y - camera.getPosition().y) +
                    (b.z - camera.getPosition().z) * (b.z - camera.getPosition().z))
                return true;
            return false;
        });
        for(auto i : positions) {
            //TODO: don't draw not displayed cubes
            if(objects.find(map[(int)i.z][(int)i.x]) != objects.end()) {
                objects[map[(int)i.z][(int)i.x]]->setPosition(i);
                objects[map[(int)i.z][(int)i.x]]->draw(camera.getTransformation());
            }
        }

        if(showGUI) {
            //dimension lines
            sf::Shader::bind(&positionShader);
            positionShader.setUniform("transformation", sf::Glsl::Mat4(glm::value_ptr(camera.getTransformation())));

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

            gui.draw(window, L"X = " + std::to_wstring(camera.getPosition().x) +
                     L"\nY = " + std::to_wstring(camera.getPosition().y) +
                     L"\nZ = " + std::to_wstring(camera.getPosition().z) +
                     L"\nφ = " + std::to_wstring(camera.getHorizontalAngle() * 180 / M_PI) +
                     L"\nθ = " + std::to_wstring(camera.getVerticalAngle() * 180 / M_PI) +
                     L"\nFOV = " + std::to_wstring(camera.getFOV()));
        }

        window.display();
    }
    return 0;
}
