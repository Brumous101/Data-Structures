#pragma once
#include <SFML/Graphics.hpp>
#include <ostream>

namespace ssuds
{
	class Bouncer : public sf::CircleShape
	{
	protected:
		sf::Vector2f mVelocity;
		sf::Vector2f mPos;			// The center of the circle
		int mNumBounces;
		float mRadius;
	public:
		Bouncer(float center_x, float center_y, float radius, float vel_x = 0.0f, float vel_y = 0.0f);
		Bouncer();
		void update(float dt, int width, int height);
		void drawBounces(sf::RenderWindow& win, sf::Font& font) const;
		sf::Vector2f getVelocity() const;
		float getSpeed() const;
		sf::Vector2f getCenter();

		bool operator< (const Bouncer& b) const;
		bool operator> (const Bouncer& b) const;
	};

	std::ostream& operator<<(std::ostream& os, Bouncer& b);
}
