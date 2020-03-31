#include <prey.h>
#include <utility.h>

Prey::Prey(int x, int y, sf::Texture& t) : Critter(x, y, t, 0.22f)
{
	mTimeToTargetLocationChange = ssuds::rand_float(2.0f, 5.0f);
}


bool Prey::is_scary() const
{
	return false;
}


void Prey::ai_update(float dt, std::vector<Critter*>& clist, int win_w, int win_h)
{
	mTimeToTargetLocationChange -= dt;
	if (mTimeToTargetLocationChange <= 0.0f)
	{
		steer_towards(sf::Vector2f(ssuds::rand_float(10.0f, win_w - 10.0f), ssuds::rand_float(10.0f, win_h - 10.0f)));
		mTimeToTargetLocationChange = ssuds::rand_float(2.0f, 5.0f);
	}
}