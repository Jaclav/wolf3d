#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window({800, 600}, "Minimal Example");
    window.setVerticalSyncEnabled(true);

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if(event.type == sf::Event::KeyReleased)
            {
                if(event.key.code == sf::Keyboard::LShift)
                    std::cout << "LShift Released" << std::endl;
                else if(event.key.code == sf::Keyboard::RShift)
                    std::cout << "RShift Released" << std::endl;
                else if(event.key.code == sf::Keyboard::A)
                    std::cout << "A Released" << std::endl;
                else if(event.key.code == sf::Keyboard::D)
                    std::cout << "D Released" << std::endl;
            }
            else if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::LShift)
                    std::cout << "LShift Pressed" << std::endl;
                else if(event.key.code == sf::Keyboard::RShift)
                    std::cout << "RShift Pressed" << std::endl;
                else if(event.key.code == sf::Keyboard::A)
                    std::cout << "A Pressed" << std::endl;
                else if(event.key.code == sf::Keyboard::D)
                    std::cout << "D Pressed" << std::endl;
            }
        }

        window.clear();
        window.display();
    }
}