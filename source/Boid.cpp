#include "Boid.h"


void Boid::seek(sf::Vector2f& target) {
	auto desired = target - location;
	desired = boid_params.maxSpeed * norm(desired);
	auto steer = desired - velocity;
	if (mag(steer) > boid_params.maxForce) {
		steer = norm(steer) * boid_params.coheseCoef * boid_params.maxForce;
	}
	applyForce(steer);
};

void Boid::swarm(const std::vector<Boid>& v_vec) {
	auto averageRepulsVec = sf::Vector2f{ 0,0 };
	auto averageAlignVec  = averageRepulsVec;
	auto averageCoheseVec = averageRepulsVec;

	int cntrRepuls = 0;
	int cntrAC = 0;

	for (auto& veh : v_vec) {
		auto otherVec = veh.getLocation();
		auto d = mag(location - otherVec);

		if (d > 0 && d < boid_params.visionRadius) {
			averageAlignVec  += veh.getVelocity();
			averageCoheseVec += otherVec;
			++cntrAC;
			if (d > 0 && d < boid_params.desiredSeparation) {
				averageRepulsVec += norm(location - otherVec) / d;
				++cntrRepuls;
			}
		}
	}

	if (cntrRepuls > 0) {
		averageRepulsVec = boid_params.maxSpeed * norm(averageRepulsVec) / cntrRepuls;
		auto steer = averageRepulsVec - velocity;
		if (mag(steer) > boid_params.maxForce)
			steer = norm(steer) *boid_params.separateCoef* boid_params.maxForce;
		applyForce(steer);
	}

	if (cntrAC > 0) {
		averageAlignVec = boid_params.maxSpeed * norm(averageAlignVec) / cntrAC;
		auto steer = averageAlignVec - velocity;
		if (mag(steer) > boid_params.maxForce)
			steer = norm(steer) * boid_params.alignCoef * boid_params.maxForce;
		applyForce(steer);
		
		averageCoheseVec = averageCoheseVec / cntrAC;
		seek(averageCoheseVec);
	}
}


void parallel_swarm(const std::vector<Boid*>& v_ptr,
	const std::vector<Boid*>::iterator& start,
	const std::vector<Boid*>::iterator& end)
{
	// check if ( v_boids().empty() ) ?
	auto& boid_params = v_ptr[0]->getBoidParams();
	
	for (auto ptr = start; ptr != end; ++ptr){
		
		auto averageRepulsVec = sf::Vector2f{ 0,0 };
		auto averageAlignVec = averageRepulsVec;
		auto averageCoheseVec = averageRepulsVec;

		int cntrRepuls = 0;
		int cntrAC = 0;

		auto& curr_boid = **ptr; // hmm

		for (auto& boid : v_ptr) {
			auto d = mag(curr_boid.getLocation() - boid->getLocation());

			if (d > 0 && d < boid_params.visionRadius) {
				averageAlignVec += boid->getVelocity();
				averageCoheseVec += boid->getLocation();
				++cntrAC;

				if (d < boid_params.desiredSeparation) {
					averageRepulsVec += norm(curr_boid.getLocation() - boid->getLocation()) / d;
					++cntrRepuls;
				}
			}

		}

		if (cntrRepuls > 0) {
			averageRepulsVec = boid_params.maxSpeed * norm(averageRepulsVec) / cntrRepuls;
			auto steer = averageRepulsVec - curr_boid.getVelocity();
			if (mag(steer) > boid_params.maxForce)
				steer = norm(steer) * boid_params.separateCoef * boid_params.maxForce;
			curr_boid.applyForce(steer);
		}

		if (cntrAC > 0) {
			averageAlignVec = boid_params.maxSpeed * norm(averageAlignVec) / cntrAC;
			auto steer = averageAlignVec - curr_boid.getVelocity();
			if (mag(steer) > boid_params.maxForce)
				steer = norm(steer) * boid_params.alignCoef * boid_params.maxForce;
			curr_boid.applyForce(steer);

			averageCoheseVec = averageCoheseVec / cntrAC;
			curr_boid.seek(averageCoheseVec);
		}
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
	limit(boid_params.maxSpeed);
	location += velocity;
	ignoreEdges(window);
	shape.setPosition(location);
	acceleration = sf::Vector2f(0, 0);
}


void Boid::draw(sf::RenderWindow& window) {
	window.draw(shape);
}
  
