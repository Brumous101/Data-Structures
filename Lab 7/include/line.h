#pragma once
#include <SFML/Graphics.hpp>

namespace ssuds
{
	class Line /*: public sf::CircleShape*/
	{
	protected:
		sf::Vertex line[2];
		float mVerticalness;
		//float mHorizontalness;
		sf::Color mColor;
	public:
		Line(float x1, float y1, float x2, float y2);
		Line();
		void update(float dt, int width, int height);
		void draw(sf::RenderWindow& win);
		float getMagnitude(float x1, float y1, float x2, float y2);

		//< overload
		bool operator < (const Line& OtherLine) const
		{
			if (mVerticalness < OtherLine.mVerticalness)
				return true;
			else
				return false;
		}
		//> overload
		bool operator > (const Line& OtherLine) const
		{
			if (mVerticalness > OtherLine.mVerticalness)
				return true;
			else
				return false;
		}
		//== overload
		bool operator == (const Line& OtherLine) const
		{
			if (mVerticalness == OtherLine.mVerticalness)
				return true;
			else
				return false;
		}
	};
}
