#pragma once
#ifndef BOID_H
#define BOID_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Vector2_ext.h"
#include "BoidParameters.h"
#include <memory>
#include "Settings.h"

/* To do:
- BoidFactory maybe?
- Need some sort of inertia for boids when aligning, cohesing and separating? (/10 in seel mb?)
- settings update function (as of growing size etc)
- WanderDistance incorporate in BoidParams
*/

class Boid {
private:

	sf::CircleShape shape;
	sf::CircleShape dotOnHead;
	
	sf::Vector2f location;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;

	BoidParameters boid_params;

public:

	Boid() {}
	
	Boid(const sf::RenderWindow& window, const Settings& settings)
	{
		boid_params = settings.getBoidParameters();
		auto shapeRadius = 7;

		int win_x = window.getSize().x;
		int win_y = window.getSize().y;
		int sign = pow(-1, randint(1)); // This way sign is fixed, so it doesn't envoke randomness for every call

		location = sf::Vector2f(randint(win_x), randint(win_y));
		
		velocity = sf::Vector2f(randint(4)*sign, randint(4)* sign);
		acceleration = sf::Vector2f(0, 0);

		
		shape = sf::CircleShape(shapeRadius, 3);
		
		shape.setOrigin(shapeRadius, shapeRadius);
		shape.setFillColor(sf::Color::Color(130,0,0,250));
		shape.setPosition(location);
		
		dotOnHead.setRadius(1);
		dotOnHead.setOrigin(0.5, 1 + 7);
		dotOnHead.setPosition(location.x , location.y );
		dotOnHead.setFillColor(sf::Color::Color(0, 130, 0, 250));
	}
	
   ~Boid() {};

	void update(const sf::RenderWindow& window);
	void checkEdges (const sf::RenderWindow& window);
	void ignoreEdges(const sf::RenderWindow& window);
	
	void seek(sf::Vector2f& target);
	void swarm   (const std::vector<Boid>& v_vec);
	
	void applyForce(sf::Vector2f& force) { acceleration += force; }

	int            getRadius()     const { return shape.getRadius(); }
	sf::Vector2f   getLocation()   const { return location; }
	sf::Vector2f   getVelocity()   const { return velocity; }
	BoidParameters getBoidParams() const { return boid_params; }

	void limit(float f) { if (mag(acceleration) > boid_params.maxForce) acceleration = norm(acceleration) * boid_params.maxForce; };
	void draw(sf::RenderWindow& window, bool drawDirection);


	//Boid(Boid&&);
	//Boid(const Boid&);

};

void parallel_swarm(const std::vector< Boid*>& v_ptr,
	const std::vector< Boid* >::iterator& start,
	const std::vector< Boid* >::iterator& end);


#endif
