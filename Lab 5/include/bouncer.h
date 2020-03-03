#pragma once
#include <SFML/Graphics.hpp>
#include <ostream>

namespace ssuds
{
	///The Bouncer class. Provides graphics for the bouncing object.
	class Bouncer : public sf::CircleShape
	{
	protected:
		///Initializes the center of the bouncer
		sf::Vector2f mPos;			
		///Initializes the bouncers number of bounces
		int mNumBounces;
		///Initializes the bouncer with a radius
		float mRadius;
	public:
		///Declares a two-direction velocity for the bouncer
		sf::Vector2f mVelocity;
		///Bouncer constructor that is passed arguments of an existing bouncer
		Bouncer(float center_x, float center_y, float radius, float vel_x = 0.0f, float vel_y = 0.0f);
		///Bouncer constructor
		Bouncer();
		///updates the bouncer location
		void update(float dt, int width, int height);
		///Draws the text on the bounder
		void drawBounces(sf::RenderWindow& win, sf::Font& font);

		///Gets the velocity of the bouncer
		sf::Vector2f getVelocity();
		///Gets the position of the bouncer
		sf::Vector2f getPosition();

		///Compares the speeds of the bouncers
		bool operator > (const Bouncer& b) const
		{
			float currentBouncerVelocity;
			float otherBouncerVelocity;
			currentBouncerVelocity = sqrtf((mVelocity.x * mVelocity.x) + (mVelocity.y * mVelocity.y));
			otherBouncerVelocity = sqrtf((b.mVelocity.x * b.mVelocity.x) + (b.mVelocity.y * b.mVelocity.y));
			if (currentBouncerVelocity > otherBouncerVelocity)
			{
				return true;
			}
			else //otherBouncerVelocity > currentBouncerVelocity
			{
				return false;
			}
		}

		//float getSpeed();
		//Attempted making a separate function to no avail 
		///Compares the speeds of the bouncers
		bool operator < (const Bouncer& b) const
		{
			float currentBouncerVelocity;
			float otherBouncerVelocity;
			currentBouncerVelocity = sqrtf((mVelocity.x * mVelocity.x) + (mVelocity.y * mVelocity.y));
			otherBouncerVelocity = sqrtf((b.mVelocity.x * b.mVelocity.x) + (b.mVelocity.y * b.mVelocity.y));
			if (currentBouncerVelocity < otherBouncerVelocity)
			{
				return true;
			}
			else //otherBouncerVelocity < currentBouncerVelocity
			{
				return false;
			}
		}
	};
	std::ostream& operator<< (std::ostream& os, Bouncer& bouncerObject);
}
