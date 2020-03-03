#include <bouncer.h>
#include <utility.h>

ssuds::Bouncer::Bouncer(float center_x, float center_y, float radius, float vel_x, float vel_y) : mRadius(radius), mNumBounces(0)
{
	mVelocity = sf::Vector2f(vel_x, vel_y);
	mPos = sf::Vector2f(center_x, center_y);
	setRadius(radius);
	setFillColor(sf::Color(rand_float(64.0f, 255.0f), rand_float(64.0f, 255.0f), rand_float(64.0f, 255.0f)));
	setPosition(center_x - radius, center_y - radius);
}


ssuds::Bouncer::Bouncer()
{
	// Intentionally empty -- just here so we can make an ArrayList of Bouncer objects.
}

void ssuds::Bouncer::update(float dt, int width, int height)
{
	mPos += mVelocity * dt;

	if (mPos.x < mRadius)
	{
		mPos.x = mRadius;
		mVelocity.x = -mVelocity.x;
		mNumBounces++;
	}
	if (mPos.y < mRadius)
	{
		mPos.y = mRadius;
		mVelocity.y = -mVelocity.y;
		mNumBounces++;
	}
	if (mPos.x > width - mRadius)
	{
		mPos.x = width - mRadius;
		mVelocity.x = -mVelocity.x;
		mNumBounces++;
	}
	if (mPos.y > height - mRadius)
	{
		mPos.y = height - mRadius;
		mVelocity.y = -mVelocity.y;
		mNumBounces++;
	}

	// In SFML, the position is the upper-left.  Adjust it to match our new position
	setPosition(mPos.x - mRadius, mPos.y - mRadius);
}

void ssuds::Bouncer::drawBounces(sf::RenderWindow& win, sf::Font& font)
{
	sf::Text t;
	t.setFont(font);
	t.setString(std::to_string(mNumBounces));
	t.setCharacterSize(20);
	t.setFillColor(sf::Color::White);
	sf::FloatRect fr = t.getGlobalBounds();
	t.setPosition(mPos.x - fr.left - fr.width / 2.0f, mPos.y - fr.top - fr.height / 2.0f);
	win.draw(t);
}


