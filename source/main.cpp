#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "Vector2_ext.h"
#include "Boid.h"
#include <thread>

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
	fpsText.setCharacterSize(15);
	fpsText.setFillColor(sf::Color::Red);
	
	sf::Text boidsNumText;
	boidsNumText.setFont(settings_font);
	boidsNumText.setPosition(20, 45);
	boidsNumText.setCharacterSize(15);
	boidsNumText.setFillColor(sf::Color::Red);

	sf::Text parallelStatusText;
	parallelStatusText.setFont(settings_font);
	parallelStatusText.setPosition(20, 70);
	parallelStatusText.setCharacterSize(15);
	parallelStatusText.setFillColor(sf::Color::Red);

	// ---- boids initialization ----
	std::vector<Boid> v_veh;
	std::vector<Boid*> v_ptr;
	v_veh.reserve(boidsNum);
	for (int i = 0; i < boidsNum; ++i) {
		v_veh.push_back(Boid(window));
		v_ptr.push_back(&v_veh[i]);
	}

	// ---- in-loop parameters ----
	std::string fpsString;
	std::string boidsNumString;
	int sz = v_veh.size();
	int cntrTime = 0;
	
	bool isParallel = false;
	auto threadNum   = std::thread::hardware_concurrency() + 10;
	auto thread_sz = sz / threadNum;

	auto v_threads = std::vector<std::thread>(threadNum);
	

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

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::P) {
					isParallel = !isParallel;
					if (isParallel)
						parallelStatusText.setString("multithreading: ON ");
					else
						parallelStatusText.setString("multithreading: OFF ");
				}
			}

			if (event.type == sf::Event::Closed)
				window.close();
		}

		// compute boids
		window.clear(sf::Color::White);
		if (isParallel) {
			std::vector<Boid*>::iterator ptr = v_ptr.begin();

			for (int i = 0; i < threadNum - 1; ++i) {
				ptr = v_ptr.begin() + i*thread_sz;
				v_threads.at(i) = std::thread(parallel_swarm, v_ptr, ptr, ptr + thread_sz);
			}
			// last thread will have to deal with what's left
			v_threads.at(threadNum - 1) = std::thread(parallel_swarm, v_ptr, ptr, v_ptr.end());
			for (int i = 0; i < threadNum; ++i)
				v_threads.at(i).join();

			for (int i = 0; i < sz; ++i) {
				v_veh[i].update(window);
				v_veh[i].draw(window);
			}
		}
		else {

			for (int i = 0; i < sz; ++i)
				v_veh[i].swarm(v_veh);
			for (int i = 0; i < sz; ++i) {
				v_veh[i].update(window);   // this way updates are happening with boids already knowing their next moves
				v_veh[i].draw(window);
			}
		}
		// fps + boidsNum counter + multithreading status
		if (clock.getElapsedTime().asSeconds() < OneSecond.asSeconds())
			++cntrTime;
		else {
			fpsString = "fps: " + std::to_string(cntrTime);
			fpsText.setString(fpsString);
			cntrTime = 0;
			clock.restart();
		}
		boidsNumText.setString("boids: " + std::to_string(sz));
		window.draw(fpsText);
		window.draw(boidsNumText);

		window.draw(parallelStatusText);
		window.draw(boidsNumText);

		//draw everything
		window.display();
	}

	return 0;
}
