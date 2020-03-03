//Name: Kyle Johnson
//Class: ETEC2101
//Section: 01
//Assignment: 3
#include <iostream>
#include <string>			// contains getline function (among other things)
#include <array_list.h>
#include <SFML/Graphics.hpp>
#include <Bouncer.h>

using namespace std;
int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
	sf::CircleShape shape;
	//constructor called here
	ssuds::Bouncer B( 50.0f, 70.72f, 90.89f, 54.32f);

	shape.setFillColor(sf::Color(255, 200, 100));
	shape.setPosition(100.0f, 50.0f);
	shape.setRadius(30.0f);
	sf::Clock clock;

	while (window.isOpen())
	{
		// Process input events
		sf::Event event;
		sf::Time t = clock.restart();
		float dt = t.asSeconds();

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

	//return 0;
	//ssuds::ArrayList<string>slist;
		// Testing creation and basic methods
		ssuds::ArrayList<std::string> slist;
		std::cout << slist.size() << std::endl;							// 0
		std::cout << slist.capacity() << std::endl;						// 5 
		//Needs to initialize an array with 5 available strings and has nothing in it to start

		slist.push_back("Abe");
		slist.push_back("Barb");
		slist.push_back("Carl");
		slist.push_back("Doug");
		slist.push_back("Erin");
		slist.push_back("Frank");										// If in a debug build, we should see "[[GROW]]" here
		std::cout << slist << std::endl;								// [Abe, Barb, Carl, Doug, Erin, Frank]    I'll be grading spaces and commas too!
		std::cout << slist.size() << std::endl;				        	// 6
		std::cout << slist.capacity() << std::endl;						// 10 


		// Testing index accessor
		std::cout << "slist" << std::endl << "=====" << std::endl;		// slist
		for (int i = 0; i < (int)slist.size(); i++)						// =====
			std::cout << "\t" << slist[i] << std::endl;					//     Abe
																		//     Barb
																		//     Carl
																		//     Doug
																		//     Erin
																		//     Frank
		// ... if uncommented, these lines should throw std::out_of_range exceptions.  Once that's working, uncomment them
		slist[-5];//Operator overload
		slist[200];


		// Testing insert
		slist.insert("Xavier", 2);
		std::cout << slist << std::endl;								// [Abe, Barb, Xavier, Carl, Doug, Erin, Frank]


		// Testing find mechanisms
		slist.push_back("Barb");
		slist.push_back("Gina");
		slist.push_back("Barb");
		std::cout << slist << std::endl;								// [Abe, Barb, Xavier, Carl, Doug, Erin, Frank, Barb, Gina, Barb]
		std::cout << "Carl is at " << slist.find("Carl") << std::endl;	// Carl is at 3
		std::cout << "Barbs are at..." << std::endl;					// Barbs are at...
		int find_index = 0;												//     index=1
		while (1)														//     index=7
		{																//     index=9
			find_index = slist.find("Barb", find_index);
			if (find_index >= 0)
				std::cout << "\tindex=" << find_index << std::endl;
			else
				break;
			// Add one, so we start looking for more Barb's at the index after the one we just found
			find_index++;
		}

		// Testing remove
		slist.remove(7);
		slist.remove(8);
		std::cout << slist << std::endl;								// [Abe, Barb, Xavier, Carl, Doug, Erin, Frank, Gina]

		ssuds::ArrayList<float> flist;
		flist.push_back(1.1f);
		flist.push_back(2.2f);
		// Note: this int and double constant are silenty cast to floats.
		// You should get a warning on the second one (then you can change it to a float)
		flist.push_back(3);
		flist.push_back(4.4f);
		// Despite the 3 show by cout, a 3.0f is being store in the ArrayList
		std::cout << "flist = " << flist << std::endl;					// [1.1, 2.2, 3, 4.4]

	ssuds::ArrayList<string>::ArrayListIterator cur = slist.begin();
		cout << *slist.begin() << endl;
		cout << *slist.end() << endl;

	if (cur == slist.end())
	{
		cout << "Bad" << endl;
	}
    while (cur != slist.end())
    {
		string value = *cur;
		cout << value << endl;
        ++cur;
    }
		cout << endl;
		cout << "Printing with prettier interface:" << endl;
	for (string s : slist)
		cout << s << endl;

}