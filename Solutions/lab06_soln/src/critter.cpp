#include <critter.h>
#include <utility.h>
#include <cmath>


Critter::Critter(int x, int y, sf::Texture& t, float sfactor) : mUsingTarget(false)
{
	mPos = sf::Vector2f((float)x, (float)y);
	mSprite.setTexture(t);
	mSprite.setPosition((float)x, (float)y);
	sf::Vector2u tex_size = t.getSize();
	sf::Vector2f test = mSprite.getOrigin();
	
	float x_origin = tex_size.x * 0.5f;
	float y_origin = tex_size.y - x_origin;
	mSprite.setOrigin(x_origin, y_origin);
	mSprite.setScale(sf::Vector2f(sfactor, sfactor));
	mImgSize = sf::Vector2f(tex_size.x * sfactor, tex_size.y * sfactor);
	mRadius = tex_size.x * sfactor * 0.5f;
	

	mAngle = ssuds::rand_float(0.0f, 360.0f);
	mSpeed = ssuds::rand_float(10.0f, 30.0f);
}



void Critter::draw(sf::RenderWindow& w, bool debug) 
{
	// Draw the sprite
	sf::FloatRect bounding_rect = mSprite.getGlobalBounds();
	mSprite.setRotation(mAngle + 90);
	mSprite.setPosition(mPos);
	w.draw(mSprite);

	if (debug)
	{
		// Draw a dot at the center
		float rad = 5.0f;
		sf::CircleShape c(rad);
		c.setFillColor(sf::Color::Red);
		c.setPosition(mPos.x - rad / 2.0f, mPos.y - rad / 2.0f);
		w.draw(c);

		// Draw a line
		sf::VertexArray line(sf::LinesStrip, 2);
		line[0].position = mPos;
		line[0].color = sf::Color::Red;
		line[1].position = get_point(40, true);
		line[1].color = sf::Color::White;
		w.draw(line);
	}
}


sf::Vector2f Critter::get_pos() const
{
	return mPos;
}



float Critter::get_radius() const
{
	return mRadius;
}

sf::Vector2f Critter::get_target() const
{
	return mTarget;
}



float Critter::distance_to(sf::Vector2f pos) const
{
	sf::Vector2f offset = pos - mPos;
	return sqrtf(offset.x * offset.x + offset.y * offset.y);
}



void Critter::steer_towards(sf::Vector2f t)
{
	mUsingTarget = true;
	mTarget = t;
}

void Critter::stop_steering_towards()
{
	mUsingTarget = false;
}



void Critter::update(float dt, std::vector<Critter*>& clist, int screen_w, int screen_h)
{
	// Get the ai to update our steering
	ai_update(dt, clist, screen_w, screen_h);

	// Make sure the angle is between 0.0 and 360.0f
	while (mAngle < 0)
		mAngle += 360.0f;
	while (mAngle > 360)
		mAngle -= 360.0f;

	// Steer towards the target, if we're using one
	if (mUsingTarget)
	{
		if (distance_to(mTarget) < mRadius)
			mUsingTarget = false;
		else
		{

			float desired_degrees = atan2f(mTarget.y - mPos.y, mTarget.x - mPos.x) * 57.29578f;
			while (desired_degrees < 0)
				desired_degrees += 360.0f;
			while (desired_degrees > 360.0f)
				desired_degrees -= 360.0f;
			float angle_offset = desired_degrees - mAngle;
			if (fabs(angle_offset) > 180.0f)
				angle_offset *= -1.0f;

			const float rotation_speed = 90.0f;
			if (angle_offset < -5.0f)
				mAngle -= rotation_speed * dt;
			else if (angle_offset > 5.0f)
				mAngle += rotation_speed * dt;
		}
	}
	

	// Move forward in our current direction
	sf::Vector2f offset = get_point(mSpeed * dt, false);
	mPos += offset;
	if (mPos.x - mRadius < 0)
	{
		mPos.x = mRadius;
		mAngle = 90 - (mAngle - 90);
	}
	if (mPos.y - mRadius < 0)
	{
		mPos.y = mRadius;
		mAngle = 180.0f - (mAngle - 180.0f);
	}
	if (mPos.x > screen_w - mRadius)
	{
		mPos.x = screen_w - mRadius;
		if (mAngle <= 90)
			mAngle = 180.0f - mAngle;
		else
			mAngle = 180.0f + mAngle;
	}
	if (mPos.y > screen_h - mRadius)
	{
		mPos.y = screen_h - mRadius;
		mAngle = (360.0f - mAngle);
	}
}


sf::Vector2f Critter::get_point(float dist, bool add_pos) const
{
	float rad = mAngle * 0.0174533f;		// 0.17 = pi / 180
	float dx = dist * cosf(rad);
	float dy = dist * sinf(rad);
	sf::Vector2f result(dx, dy);
	if (add_pos)
		result += mPos;
	return result;
}