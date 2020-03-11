#include <SFML/Graphics.hpp>
#include <array_list.h>
#include <bouncer.h>
#include <utility.h>
#include <critter.h>
#include <prey.h>
#include <predator.h>

int main()
{
	std::vector<Critter*> clist;
	srand((unsigned int)time(NULL));
	// SFML main program
	int win_width = 800;
	int win_height = 600;
	bool paused = false;
	bool debug = false;
	sf::Clock deltaClock;
	sf::Font font;
	sf::RenderWindow window(sf::VideoMode(win_width, win_height), "ETEC2101 Lab3");

	font.loadFromFile("../media/OdibeeSans-Regular.ttf");

	std::vector<std::string> img_fnames{ "bear", "buffalo", "chick", "chicken", "cow", "crocodile", "dog", "duck", "elephant", "frog", "giraffe", "goat", "gorilla", "hippo", "horse", "monkey", "moose", "narwhal", "owl" ,"panda", "parrot", "penguin", "pig", "rabbit", "rhino", "sloth", "snake", "walrus", "whale", "zebra" };
	std::vector<sf::Texture> img_tex;
	for (std::string fn : img_fnames)
	{
		sf::Texture t;
		t.loadFromFile("../media/kenney_animals/" + fn + ".png");
		img_tex.push_back(t);
	}

	for (int totalPrey = 0; totalPrey < 80; totalPrey++)
	{
		int x = ssuds::rand_float(50, 750);
		int y = ssuds::rand_float(50, 550);
		clist.push_back(new ssuds::Prey(x, y, img_tex[ssuds::rand_int(0, img_tex.size() - 1)], 0.2));//goes through all the textures from above
	}

	for (int totalPredators = 0; totalPredators < 20; totalPredators++)
	{
		int x = ssuds::rand_float(50, 750);
		int y = ssuds::rand_float(50, 550);
		clist.push_back(new ssuds::Predator(x, y, img_tex[ssuds::rand_int(0, img_tex.size() - 1)], 0.5));//goes through all the textures from above

	}

	// SFML main loop
	while (window.isOpen())
	{
		sf::Time dt = deltaClock.restart();
		if (paused)
			dt = sf::Time::Zero;
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
				else if (event.key.code == sf::Keyboard::P)
					paused = !paused;
				else if (event.key.code == sf::Keyboard::F1)
					debug = !debug;
			}
		}
		if (!window.isOpen())
			break;

		window.clear();
		//separate loops and also walk backwards. make i=0 i=size
		for (int i = 0; i < clist.size(); i++)
		{
			clist[i]->update(dt.asSeconds(), clist, win_width, win_height);
		}
		for (int i = 0; i < clist.size(); i++)
		{
			clist[i]->draw(window, debug);
		}
		window.display();
	}

	return 0;
}