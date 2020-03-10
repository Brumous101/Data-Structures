#pragma once
#include <SFML/Graphics.hpp>



/// A base class for real objects (Prey and Predator, in our case)
class Critter
{
protected:
	/// The sprite used to render this image.  It contains a reference to a texture
	sf::Sprite mSprite;

	/// The angle (in degrees) that we're facing
	float mAngle;

	/// The speed (in px/s) that we're 
	float mSpeed;

	/// The dimensions (w, h) of the image we're using for rendering
	sf::Vector2f mImgSize;

	/// The (center) position of this critter
	sf::Vector2f mPos;

	/// The radius of this critter (based on the image x-dimensions)
	float mRadius;

	/// The target we're steering towards (if any)
	sf::Vector2f mTarget;

	/// True if we've been told to go towards the target point (by steer_towards)
	bool mUsingTarget;
public:
	/// The only constructor
	Critter(int x, int y, sf::Texture& t, float sfactor);

	/// Draws this critter to the given window.  If debug is true, draw some visualizations of direction
	virtual void draw(sf::RenderWindow& w, bool debug);

	/// Gets the center point of this critter
	virtual sf::Vector2f get_pos() const;

	/// Gets the radius of this critter
	float get_radius() const;

	/// Gets the target point
	sf::Vector2f get_target() const;

	/// Gets the euclidean distance (in pixels) from our center position to the given point
	virtual float distance_to(const sf::Vector2f pos) const;

	/// Makes the given point the steer target.  This will stay in effect until mUsing target is set to false
	virtual void steer_towards(sf::Vector2f t);

	/// Makes this object stop steering towards the target (it will just go in its facing direction)
	virtual void stop_steering_towards();

	/// Returns true if this is scary (for us, Predators are scary, Prey is not)
	virtual bool is_scary() const = 0;

protected:
	/// This is called by update.  It gives the derived class a chance to update their steering
	virtual void ai_update(float dt, std::vector<Critter*>& clist, int win_w, int win_h) = 0;

public:
	/// Calls ai_update, then moves the object forward, bouncing off the walls if necessary
	virtual void update(float dt, std::vector<Critter*>& clist, int screen_w, int screen_h);

	/// Gets a point dist pixels from the center in the facing direction if add_pos is true.  
	/// If add_pos is false, just gets a vector (e.g. velocity) offset with dist hypotenuse 
	sf::Vector2f get_point(float dist, bool add_pos) const;
};