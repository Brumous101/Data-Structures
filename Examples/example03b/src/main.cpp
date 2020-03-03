#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    sf::CircleShape shape;
    shape.setFillColor(sf::Color(255, 200, 100));
    shape.setPosition(100.0f, 50.0f);
    shape.setRadius(30.0f);
    //sf::Clock clock;

    while (window.isOpen())
    {
        // Process input events
        sf::Event event;
        //sf::Time t = clock.restart();
        //float dt = t.asSeconds();
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
            }
        }

        // Drawing code
        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}