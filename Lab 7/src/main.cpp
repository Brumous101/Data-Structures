#include <iostream>
#include <heap.h>
#include <SFML/Graphics.hpp>
#include <Line.h>
#include <utility.h>
using namespace std;

int main()
{
	srand((unsigned int)time(NULL));
    ssuds::Heap<std::string> G(ssuds::HeapType::MAX_HEAP);
    G.push("Carl");
    G.push("Zion");
    G.push("Abe");
    G.push("Doug");
    G.push("Frank");
    cout << "G = " << G << endl;                // G = [Zion, Frank, Abe, Carl, Doug]
    cout << "G.peek() = " << G.peek() << endl;  // G.peek() = Zion
    
    cout << "list-like methods" << endl;        // list-like methods
    cout << "=================" << endl;        // =================
    for (int i = 0; i < G.size(); i++)          //    Zion
        cout << "\t" << G[i] << endl;           //    Frank
                                                //    Abe
                                                //    Carl
                                                //    Doug
    
    cout << "popping..." << endl;				// popping...
    cout << "==========" << endl;				// ==========
    while (!G.empty())							//    Zion
    {											//    Frank
        cout << "\t" << G.pop() << endl;		//    Doug
    }											//    Carl
                                                //    Abe
    
    ssuds::Heap<float> H{ ssuds::HeapType::MIN_HEAP, {3.7f, 2.1f, 0.6f, 8.5f, 9.3f, 6.5f, 0.5f, 12.3f, 0.1f} };
    cout << "H = " << H << endl;                // H = [0.1, 0.5, 0.6, 3.7, 9.3, 6.5, 2.1, 12.3, 8.5]
    cout << "H.peek() = " << H.peek() << endl;  // H.peek() = 0.1

	// SFML main program
	int win_width = 800;
	int win_height = 600;
	bool paused = false;
	sf::RenderWindow window(sf::VideoMode(win_width, win_height), "ETEC2101 Lab7");
	ssuds::Heap<ssuds::Line> blist(ssuds::HeapType::MAX_HEAP);
	for (int i = 0; i < 100; i++)
	{
		float x1 = ssuds::rand_float(10.0f, win_width - 10.0f);
		float y1 = ssuds::rand_float(10.0f, win_height - 10.0f);
		float x2 = ssuds::rand_float(10.0f, win_width - 10.0f);
		float y2 = ssuds::rand_float(10.0f, win_height - 10.0f);

		ssuds::Line new_b(x1, y1, x2, y2);
		blist.push(new_b);
	}
	//sf::Clock deltaClock;
	//sf::Font font;
	//font.loadFromFile("..\\media\\Bangers-Regular.ttf");


	// SFML main loop
	while (window.isOpen())
	{
		//sf::Time dt = deltaClock.restart();
		//if (paused)
		//	dt = sf::Time::Zero;

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
				else if (event.key.code == sf::Keyboard::Space)
					blist.pop();
			}
		}
		if (!window.isOpen())
			break;

		window.clear();
		for (int i =0; i < blist.size(); i++)
		{
			//b.update(dt.asSeconds(), win_width, win_height);
			//window.draw(b);
			blist[i].draw(window);
		}
		window.display();
	}

	return 0;
    /*
    // Bonus
    cout << G.tree_string() << endl;            // Zion
                                                //     <Frank
                                                //         <Carl
                                                //         >Doug
                                                //     >Abe

    cout << endl << H.tree_string() << endl;    // 0.1
                                                //     <0.5
                                                //         <3.7
                                                //             <12.3
                                                //             >8.5
                                                //         >9.3
                                                //     >0.6
                                                //         <6.5
                                                //         >2.1

    return 0;
    */
}
