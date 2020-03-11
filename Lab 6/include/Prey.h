#pragma once
#include <critter.h>

namespace ssuds
{
	class Prey : public Critter
	{
	protected:
		sf::Vector2f mVelocity;
		//sf::Vector2f mPos;                                                                 // The center of the circle
		//int mNumBounces;
		//float mRadius;
		float mCounter;
	public:
		Prey(int x, int y, sf::Texture& t, float sfactor);                                 //constructor no return type
		bool is_scary() const override;
		void ai_update(float dt, std::vector<Critter*>& clist, int win_w, int win_h);
	};
}