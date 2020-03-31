#pragma once
#include <critter.h>


class Predator : public Critter
{
protected:

public:
	Predator(int x, int y, sf::Texture& t);
	virtual bool is_scary() const override;
	virtual void ai_update(float dt, std::vector<Critter*>& clist, int win_w, int win_h) override;
	virtual void draw(sf::RenderWindow& w, bool debug) override;
};

