#include <Predator.h>
#include <utility.h>

ssuds::Predator::Predator(int x, int y, sf::Texture& t, float sfactor) : Critter(x, y, t, sfactor)
{
	totalPredators++;
};

bool ssuds::Predator::is_scary() const
{
	return true;
}

void ssuds::Predator::ai_update(float dt, std::vector<Critter*>& clist, int win_w, int win_h)
{
	float closest = 1400.5; //furthest possible critter position
	int index = 0;
	bool switched = false;
	//dt.asSeconds()
	if (totalPredators != clist.size())
	{
		for (int i = 0; i < clist.size();)
		{
			bool switched = false;

			if (clist[i]->is_scary())
			{
				// 
			}
			else
			{
				//possibly index should be i
				float distance = clist[i] -> distance_to(get_pos());//predator distance is getting the distance to the closest critter

				if(distance < get_radius() + clist[i]->get_radius() ) // this is a potential issue with them spawning over top of each other
				{
					delete clist[i];
					clist.erase(clist.begin() + i);
					switched = true;
				}
				else if (distance < closest)
				{
					closest = distance;
					index = i;
				}
			}
			if (switched == false)
			{
				i++;
			}
		}
		steer_towards(clist[index]->get_pos());
	}
	
}
void ssuds::Predator::draw(sf::RenderWindow& w, bool debug)
{
	Critter::draw(w, debug);
	if (debug)
	{
		// Draw a line
		sf::VertexArray line(sf::LinesStrip, 2);
		line[0].position = mPos;
		line[0].color = sf::Color::Green;
		line[1].position = get_target();
		line[1].color = sf::Color::White;
		w.draw(line);
	}
}
int ssuds::Predator::totalPredators = 0;