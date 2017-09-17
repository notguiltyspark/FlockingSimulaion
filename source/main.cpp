#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "Vector2_ext.h"
#include "Boid.h"


int main() {
	int win_x_sz{ 0 };
	int win_y_sz{ 0 };
	int boidsNum{ 0 };
	
	// ---- simulation parameters ----
	std::cout << "Enter x-size of the window:" << std::endl;
	std::cin  >> win_x_sz;
	std::cout << "Enter y-size of the window:" << std::endl;
	std::cin  >> win_y_sz;
	std::cout << "Enter number of boids:"      << std::endl;
	std::cin  >> boidsNum;

	// ---- window + text design ---- 
	sf::RenderWindow window(sf::VideoMode(win_x_sz, win_y_sz), "Autonomous Agents");
	window.setFramerateLimit(100);
	window.clear(sf::Color::White);

	sf::Font settings_font;
	if (!settings_font.loadFromFile("Inconsolata-Regular.ttf"))
	{
		std::cout << "Error: can't load fonts" << std::endl;
	}

	sf::Text fpsText;
	fpsText.setFont(settings_font);
	fpsText.setPosition(20,20);
	fpsText.setCharacterSize(20);
	fpsText.setFillColor(sf::Color::Red);
	
	sf::Text boidsNumText;
	boidsNumText.setFont(settings_font);
	boidsNumText.setPosition(20, 50);
	boidsNumText.setCharacterSize(20);
	boidsNumText.setFillColor(sf::Color::Red);

	// ---- boids initialization ----
	std::vector<Boid> v_veh;
	
	v_veh.reserve(boidsNum);
	for (int i = 0; i < boidsNum; ++i) {
		v_veh.push_back(Boid(window));
	}

	// ---- in-loop parameters ----
	std::string fpsString;
	std::string boidsNumString;
	int sz = v_veh.size();
	int cntrTime = 0;
	
	const sf::Time OneSecond = sf::seconds(1);
	sf::Clock clock;
	
	while (window.isOpen()) {
		
		// input handling
		sf::Event event;
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::MouseButtonPressed) {
				v_veh.push_back(Boid(window));
				++sz;
			}

			if (event.type == sf::Event::Closed)
				window.close();
		}

		// compute boids
		window.clear(sf::Color::White);
		for (int i = 0; i < sz; ++i) {
			v_veh[i].swarm(v_veh);
			v_veh[i].update(window);
			v_veh[i].draw(window);
		}

		// fps + boidsNum counter
		if (clock.getElapsedTime().asSeconds() < OneSecond.asSeconds())
			++cntrTime;
		else {
			fpsString = "fps: " + std::to_string(cntrTime);
			fpsText.setString(fpsString);
			cntrTime = 0;
			clock.restart();
		}
		boidsNumText.setString("boidsNum: " + std::to_string(sz));
		window.draw(fpsText);
		window.draw(boidsNumText);

		//draw everything
		window.display();
	}

	return 0;
}
