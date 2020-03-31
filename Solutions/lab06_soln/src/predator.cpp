#include <predator.h>
#include <list>

Predator::Predator(int x, int y, sf::Texture& t) : Critter(x, y, t, 0.33f)
{

}


bool Predator::is_scary() const
{
	return true;
}


void Predator::ai_update(float dt, std::vector<Critter*>& clist, int win_w, int win_h)
{
	// See if we're gobbling up any prey
	for (int i = (int)clist.size() - 1; i >= 0; i--)
	{
		if (clist[i] != this && !clist[i]->is_scary())
		{
			float new_dist = distance_to(clist[i]->get_pos());
			if (new_dist < mRadius + clist[i]->get_radius())
			{
				clist.erase(clist.begin() + i);
			}
		}
	}

	// Find the closest remaining prey
	int closest = -1;
	float dist = 0.0f;
	for (int i = 0; i < (int)clist.size(); i++)
	{
		if (clist[i] != this && !clist[i]->is_scary())
		{
			float new_dist = distance_to(clist[i]->get_pos());
			if (closest < 0 || new_dist < dist)
			{
				closest = i;
				dist = new_dist;
			}
		}
	}

	// Steer towards that closest prey, if we found one
	if (closest >= 0)
		steer_towards(clist[closest]->get_pos());
}


void Predator::draw(sf::RenderWindow& w, bool debug)
{
	if (debug)
	{
		sf::VertexArray line(sf::LinesStrip, 2);
		line[0].position = mPos;
		line[0].color = sf::Color::Green;
		line[1].position = get_target();
		line[1].color = sf::Color(0, 128, 0);
		w.draw(line);
	}

	Critter::draw(w, debug);

	
}