#include <Line.h>
#include <utility.h>

ssuds::Line::Line(float x1, float y1, float x2, float y2)//mColor is a class variable so the attribute gets edited and keeps the value
{
	//line[0] = sf::Vertex(sf::Vector2f(x1, y1), sf::Color(0, 255, 0));
	//line[1] = sf::Vertex(sf::Vector2f(x2, y2), sf::Color(0, 255, 0));
	float magnitude = ssuds::Line::getMagnitude(x1, y1, x2, y2);
	if (magnitude <= 0)
	{
		mColor = sf::Color(0, 0, 255);
		mVerticalness = 0.0f;
	}
	else
	{
		sf::Vector2f smallerTriangle(fabs(y2 - y1), fabs(x2 - x1));
		smallerTriangle /= magnitude;
		mVerticalness = smallerTriangle.y;
		mColor = sf::Color( (1.0 - mVerticalness) * 255, mVerticalness * 255, 0);
	}
	line[0] = sf::Vertex(sf::Vector2f(x1, y1), mColor);
	line[1] = sf::Vertex(sf::Vector2f(x2, y2), mColor);
	std::cout << line[0].position.x << " " << line[0].position.y << " " << line[1].position.x << " " << line[1].position.y << std::endl;
}


ssuds::Line::Line()
{
	// Intentionally empty -- just here so we can make an ArrayList of Line objects.
}

void ssuds::Line::update(float dt, int width, int height)
{ 
	//
}

void ssuds::Line::draw(sf::RenderWindow& win)
{
	/*maybe maybe not prey.h
	sf::VertexArray line(sf::LinesStrip, 2);
	line[0].position = mPos;
	line[0].color = sf::Color::Red;
	line[1].position = get_point(40, true);
	line[1].color = sf::Color::White;
	win.draw(line);
	*/

	win.draw(line, 2, sf::Lines);
	//std::cout << line[0].position.x<< " " << line[0].position.y << " " << line[1].position.x << " " << line[1].position.y << std::endl;
}

float ssuds::Line::getMagnitude(float x1, float y1, float x2, float y2)
{
	sf::Vector2f smallerTriangle (fabs(y2 - y1), fabs(x2 - x1));
	float magnitude = sqrtf((smallerTriangle.x * smallerTriangle.x) + (smallerTriangle.y * smallerTriangle.y));
	return magnitude;
}