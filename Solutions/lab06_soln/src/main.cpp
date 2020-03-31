#include <SFML/Graphics.hpp>
#include <vector>
#include <prey.h>
#include <predator.h>
#include <utility.h>

int main()
{
    // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    // @ STARTUP CODE                        @
    // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    int win_w = 800, win_h = 600;
    sf::RenderWindow window(sf::VideoMode(win_w, win_h), "Lab6 Solution");
    sf::Clock clock;
    sf::Font font;
    font.loadFromFile("../../media/OdibeeSans-Regular.ttf");
    bool debug = true;
    bool paused = false;
    srand((unsigned int)time(NULL));
  

    // Load some images
    std::vector<std::string> img_fnames{ "crocodile", "dog", "chick", "chicken", "duck", "frog", "owl", "panda" };
    std::vector<sf::Texture> img_tex;
    for (std::string fn : img_fnames)
    {
        sf::Texture t;
        t.loadFromFile("../../media/kenney_animals/" + fn + ".png");
        img_tex.push_back(t);
    }

    // Load some critters
    std::vector<Critter*> critter_list;
    for (int i = 0; i < 30; i++)
    {
        const int buffer = 20;
        int x = ssuds::rand_int(buffer, win_w - buffer);
        int y = ssuds::rand_int(buffer, win_h - buffer);
        int img_num;
        if (ssuds::rand_int(1, 10) <= 2)
        {
            img_num = ssuds::rand_int(0, 1);
            critter_list.push_back(new Predator(x, y, img_tex[img_num]));
        }
        else
        {
            img_num = ssuds::rand_int(2, (int)img_fnames.size() - 1);
            critter_list.push_back(new Prey(x, y, img_tex[img_num]));
        }
    }
        

    // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    // @ GAME LOOP                           @
    // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    while (window.isOpen())
    {
        // Updates
        float delta_time = clock.restart().asSeconds();
        if (paused)
            delta_time = 0.0f;
        for (int i = 0; i < critter_list.size(); i++)
            critter_list[i]->update(delta_time, critter_list, win_w, win_h);

        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::Escape:
                    window.close();
                    break;
                case sf::Keyboard::F1:
                    debug = !debug;
                    break;
                case sf::Keyboard::Space:
                    paused = !paused;
                    break;
                }
            }
        }

        // Drawing code
        window.clear();
        int num_prey = 0, num_predators = 0;
        for (int i = 0; i < critter_list.size(); i++)
        {
            critter_list[i]->draw(window, debug);
            if (critter_list[i]->is_scary())
                num_predators++;
            else
                num_prey++;
        }
        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(20);
        text.setFillColor(sf::Color(255, 255, 0));
        text.setString("#Prey=" + std::to_string(num_prey) + "    #Predators=" + std::to_string(num_predators));
        window.draw(text);
        text.setString("Images from https://www.kenney.nl/assets/animal-pack-redux");
        text.setPosition(sf::Vector2f(0.0f, win_h - 50.0f));
        window.draw(text);
        text.setString("Font from github.com/barnard555/odibeesans");
        text.setPosition(sf::Vector2f(0.0f, win_h - 25.0f));
        window.draw(text);
        window.display();
    }

    // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    // @ SHUTDOWN CODE                       @
    // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    // Free up the critter list
    for (int i = 0; i < critter_list.size(); i++)
        delete critter_list[i];
    critter_list.clear();

    return 0;
}                                                                   

