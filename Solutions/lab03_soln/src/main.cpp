#include <SFML/Graphics.hpp>
#include <array_list.h>
#include <bouncer.h>
#include <utility.h>

int main()
{
	// Test code for our ArrayList iterator
	ssuds::ArrayList<std::string> slist;
	slist.push_back("Abe");
	slist.push_back("Barb");
	slist.push_back("Carl");
	std::cout << "iterator test#1" << std::endl << "===============" << std::endl;
	ssuds::ArrayList<std::string>::ArrayListIterator slist_iter = slist.begin();
	while (slist_iter != slist.end())
	{
		std::cout << *slist_iter << std::endl;
		++slist_iter;
	}
	std::cout << "iterator test#2" << std::endl << "===============" << std::endl;
	for (std::string s : slist)
		std::cout << s << std::endl;


	// SFML main program
	int win_width = 800;
	int win_height = 600;
	bool paused = false;
	sf::RenderWindow window(sf::VideoMode(win_width, win_height), "ETEC2101 Lab3");
	ssuds::ArrayList<ssuds::Bouncer> blist;
	for (int i = 0; i < 100; i++)
	{
		float rad = ssuds::rand_float(10.0f, 30.0f);
		float x = ssuds::rand_float(rad, win_width - rad);
		float y = ssuds::rand_float(rad, win_height - rad);
		float vel_x = ssuds::rand_float(-100, 100);
		float vel_y = ssuds::rand_float(-100, 100);
		ssuds::Bouncer new_b(x, y, rad, vel_x, vel_y);
		new_b.setOutlineColor(sf::Color::White);
		new_b.setOutlineThickness(1.0f);
		blist.push_back(new_b);
	}
	sf::Clock deltaClock;
	sf::Font font;
	font.loadFromFile("..\\media\\Bangers-Regular.ttf");


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
			}
		}
		if (!window.isOpen())
			break;

		window.clear();
		for (ssuds::Bouncer& b : blist)
		{
			b.update(dt.asSeconds(), win_width, win_height);
			window.draw(b);
			b.drawBounces(window, font);
		}
		window.display();
	}

	return 0;
}