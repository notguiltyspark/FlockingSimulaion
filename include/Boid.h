#pragma once
#ifndef BOID_H
#define BOID_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Vector2_ext.h"

class Boid {
private:

	sf::CircleShape shape;

	sf::Vector2f location;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;

	float maxSpeed;
	float maxForce;
	float desiredSeparation = 10; //constexpr or input?
	float visionRadius = 15;
	
	float alignCoef = 0.9;
	float coheseCoef = 0.4;
	float separateCoef = 0.9;

public:

	Boid() {}

	Boid(const sf::RenderWindow& window)
	{
		int win_x = window.getSize().x;
		int win_y = window.getSize().y;
		int sign = pow(-1, randint(1)); // This way sign is fixed, so it doesn't envoke randomness for every call

		location = sf::Vector2f(randint(win_x), randint(win_y));
		velocity = sf::Vector2f(randint(4)*sign, randint(4)* sign);
		acceleration = sf::Vector2f(0, 0);

		maxSpeed = 2.8;
		maxForce = 0.09;

		shape.setRadius(4);
		shape.setFillColor(sf::Color::Black);
	}
	~Boid() {};

	void update(const sf::RenderWindow& window);
	void checkEdges (const sf::RenderWindow& window);
	void ignoreEdges(const sf::RenderWindow& window);
	
	void seek(sf::Vector2f& target);
	void separate(const std::vector<Boid>& v_vec);
	void align   (const std::vector<Boid>& v_vec);
	void cohese  (const std::vector<Boid>& v_vec);
	void swarm   (const std::vector<Boid>& v_vec);

	void applyForce(sf::Vector2f& force) { acceleration += force; }

	int           getRadius()   const { return shape.getRadius(); }
	sf::Vector2f  getLocation() const { return location; }
	sf::Vector2f  getVelocity() const { return velocity; }

	void limit(float f) { if (mag(acceleration) > maxForce) acceleration = norm(acceleration) * maxForce; };
	void draw(sf::RenderWindow& window);

};

#endif
