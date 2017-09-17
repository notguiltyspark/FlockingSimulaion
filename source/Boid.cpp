#include "Boid.h"

void Boid::seek(sf::Vector2f& target) {
	auto desired = target - location;
	desired = maxSpeed * norm(desired);
	auto steer = desired - velocity;
	if (mag(steer) > maxForce) {
		steer = norm(steer) * coheseCoef * maxForce;
	}
	applyForce(steer);
};


void Boid::separate(const std::vector<Boid>& v_vec) {
	auto averageRepulsVec = sf::Vector2f{ 0,0 };
	int cntr = 0;
	for (auto veh : v_vec) {
		auto d = mag(location - veh.getLocation());

		if (d > 0 && d < desiredSeparation) {
			averageRepulsVec += norm(location - veh.getLocation()) / d;
			++cntr;
		}

	}
	if (cntr > 0) {
		averageRepulsVec = maxSpeed * norm(averageRepulsVec) / cntr;
		auto steer = averageRepulsVec - velocity;
		if (mag(steer) > maxForce)
			steer = norm(steer) *separateCoef* maxForce;
		applyForce(steer);
	}

}


void Boid::align(const std::vector<Boid>& v_vec) {
	auto averageAlignVec = sf::Vector2f{ 0,0 };
	int cntr = 0;
	for (auto veh : v_vec) {
		auto d = mag(location - veh.getLocation());

		if (d > 0 && d < visionRadius) {
			averageAlignVec += veh.getVelocity();
			++cntr;
		}

	}
	if (cntr > 0) {
		averageAlignVec = maxSpeed * norm(averageAlignVec) / cntr;
		auto steer = averageAlignVec - velocity;
		if (mag(steer) > maxForce)
			steer = norm(steer) * alignCoef * maxForce;
		applyForce(steer);
	}
}


void Boid::cohese(const std::vector<Boid>& v_vec) {
	auto averageCoheseVec = sf::Vector2f{ 0,0 };
	int cntr = 0;
	for (auto veh : v_vec) {
		auto d = mag(location - veh.getLocation());

		if (d > 0 && d < visionRadius) {
			averageCoheseVec += veh.getLocation();
			++cntr;
		}

	}
	if (cntr > 0) {
		averageCoheseVec = averageCoheseVec / cntr;
		seek(averageCoheseVec);
	}
}


void Boid::swarm(const std::vector<Boid>& v_vec) {
	auto averageRepulsVec = sf::Vector2f{ 0,0 };
	auto averageAlignVec  = averageRepulsVec;
	auto averageCoheseVec = averageRepulsVec;

	int cntrRepuls = 0;
	int cntrAC = 0;

	for (auto& veh : v_vec) {
		auto otherVec = veh.getLocation();
		auto d = mag(location - otherVec);

		if (d > 0 && d < visionRadius) {
			averageAlignVec  += veh.getVelocity();
			averageCoheseVec += otherVec;
			++cntrAC;
			if (d > 0 && d < desiredSeparation) {
				averageRepulsVec += norm(location - otherVec) / d;
				++cntrRepuls;
			}
		}
	}

	if (cntrRepuls > 0) {
		averageRepulsVec = maxSpeed * norm(averageRepulsVec) / cntrRepuls;
		auto steer = averageRepulsVec - velocity;
		if (mag(steer) > maxForce)
			steer = norm(steer) *separateCoef* maxForce;
		applyForce(steer);
	}

	if (cntrAC > 0) {
		averageAlignVec = maxSpeed * norm(averageAlignVec) / cntrAC;
		auto steer = averageAlignVec - velocity;
		if (mag(steer) > maxForce)
			steer = norm(steer) * alignCoef * maxForce;
		applyForce(steer);
		
		averageCoheseVec = averageCoheseVec / cntrAC;
		seek(averageCoheseVec);
	}
}


void Boid::ignoreEdges(const sf::RenderWindow& window) {
	int win_x = window.getSize().x;
	int win_y = window.getSize().y;
	int diameter = 2 * getRadius();

	if (location.x > win_x) {
		location.x = 0;
	}
	else if (location.x < 0) {
		location.x = win_x;
	}

	if (location.y > win_y) {
		location.y = 0;
	}
	else if (location.y < 0) {
		location.y = win_y ;
	}
}


void Boid::checkEdges(const sf::RenderWindow& window) {
	int win_x = window.getSize().x;
	int win_y = window.getSize().y;
	int diameter = 2 * getRadius();

	if (location.x >= win_x - diameter) {
		velocity.x *= -1;
		location.x = win_x - diameter;
	}
	else if (location.x <= 0) {
		velocity.x *= -1;
		location.x = 0;
	}

	if (location.y >= win_y - diameter) {
		velocity.y *= -1;
		location.y = win_y - diameter;
	}
	else if (location.y <= 0) {
		velocity.y *= -1;
		location.y = 0;
	}
}


void Boid::update(const sf::RenderWindow& window) {
	velocity += acceleration;
	limit(maxSpeed);
	location += velocity;
	ignoreEdges(window);
	shape.setPosition(location);
	acceleration = sf::Vector2f(0, 0);
}


void Boid::draw(sf::RenderWindow& window) {
	window.draw(shape);
}
  
