#include <iostream>
#include <string>			// contains getline function (among other things)
#include <array_list.h>
#include <SFML/Graphics.hpp>

namespace ssuds
{
	class Bouncer : public sf::CircleShape
	{
	protected:
		sf::Vector2f mVelocity;
		int mBounces;       // We need to print this onto the circles
		float mPositionX;
		float mPositionY;
		float mSize;

	public:
		void move_me(float dt, int win_w, int win_h);
		void draw_text(sf::CircleShape shape);
		Bouncer(float startPosX, float startPosY, float xVelocity, float yVelocity, float radius);		//Constructor
		Bouncer();																		//Constructor
		~Bouncer();
	};
}