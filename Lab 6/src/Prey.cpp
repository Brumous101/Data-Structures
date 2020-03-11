#include <Prey.h>
#include <utility.h>

ssuds::Prey::Prey(int x, int y, sf::Texture& t, float sfactor) : Critter(x, y, t, sfactor)
{
	mCounter =0;
};

bool ssuds::Prey::is_scary() const
{
	return false;//false means it is a prey true means its a predator
}

void ssuds::Prey::ai_update(float dt, std::vector<Critter*>& clist, int win_w, int win_h)
{
	float timeInSeconds = rand_int(2, 5);
	mCounter = mCounter + dt;

	if (mCounter > timeInSeconds)
	{
		float x = rand_float(-1000, 1000);
		float y = rand_float(-1000, 1000);
		steer_towards(sf::Vector2f{ x, y });
		mCounter = 0;
	}
}