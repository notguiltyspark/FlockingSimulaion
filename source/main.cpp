#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <thread>
#include <exception>
#include <stdexcept>

#include "BoidParameters.h"
#include "Vector2_ext.h"
#include "Settings.h"
#include "Boid.h"
#include "GUI.h"

int main() {
	try {
		Settings settings;
		GUI gui;

		settings.init();

		sf::RenderWindow window(sf::VideoMode(settings.getWinX(), settings.getWinY()), "Autonomous Agents");
		window.setFramerateLimit(100);
		window.clear(sf::Color::Black);



		// ---- boids initialization ----
		std::vector<Boid> v_veh;
		std::vector<Boid*> v_ptr;
		v_veh.reserve(settings.getBoidsNumber());
		v_ptr.reserve(settings.getBoidsNumber());
		
		for (int i = 0; i < v_veh.capacity(); ++i) {
			v_veh.push_back(Boid(window, settings));
			v_ptr.push_back(&v_veh[i]);
		}

		auto sz = v_veh.size();
		
		// ----- Parallel options -----
		auto thread_sz = sz / settings.getThreadsNumber();
		auto v_threads = std::vector<std::thread>(settings.getThreadsNumber());
		bool isParallel = false;

		// ----- Time options -----
		const sf::Time OneSecond = sf::seconds(1);
		sf::Clock clock;
		int cntrTime = 0;
		
		
		//	----- [SIMULATION LOOP] ------

		while (window.isOpen()) {

			// ---- input handling -----
			sf::Event event;
			while (window.pollEvent(event)) {

				if (event.type == sf::Event::MouseButtonPressed) {
					if (v_veh.size() == v_veh.capacity()) {
						v_veh.push_back(Boid(window, settings));
						v_ptr.clear();
						v_ptr.reserve(2 * sz);
						++sz;	// - increment implicitly in settings? Or reference? 
					
						for (int i = 0; i < sz; ++i) {
							v_ptr.push_back(&v_veh[i]); 
						}
					}
					else {
						v_veh.push_back(Boid(window, settings));
						++sz;
						v_ptr.push_back(&v_veh[sz - 1]);
					}
					thread_sz = sz / settings.getThreadsNumber();
				}


				if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::P) {
						isParallel = !isParallel;
					}
				}

				if (event.type == sf::Event::Closed)
					window.close();
			}

			window.clear(sf::Color::Black);

			// ------ boids update -----
			//      simple traverse  
			if (!isParallel) {
				for (int i = 0; i < sz; ++i) {
					v_veh[i].swarm(v_veh);
				}
				for (int i = 0; i < sz; ++i) {
					v_veh[i].update(window);
					v_veh[i].draw(window, true);
				}
			}
			else {
			//      parallel traverse 
				std::vector<Boid*>::iterator ptr = v_ptr.begin();

				for (int i = 0; i < settings.getThreadsNumber() - 1; ++i) {
					ptr = v_ptr.begin() + i*thread_sz;
					v_threads.at(i) = std::thread(parallel_swarm, v_ptr, ptr, ptr + thread_sz);
				}
				// last thread will have to deal with what's left
				v_threads.at(settings.getThreadsNumber() - 1) = std::thread(parallel_swarm, v_ptr, ptr, v_ptr.end());
				for (int i = 0; i < settings.getThreadsNumber(); ++i)
					v_threads.at(i).join();

				for (int i = 0; i < sz; ++i) {
					v_veh[i].update(window);
					v_veh[i].draw(window, true);
				}
			}
			
			// gui update
			if (clock.getElapsedTime().asSeconds() < OneSecond.asSeconds())
				++cntrTime;
			else {
				gui.setFps(cntrTime);
				cntrTime = 0;
				clock.restart();
			}
			gui.setBoidsNumber(sz);
			gui.setParallelStatus(isParallel);
			gui.draw(window);
			
			//draw everything
			window.display();
		}
		return 0;
	}
	catch (std::exception& e) {
		std::cout << "noot-noot, error: " << e.what() << std::endl;
		return 1;
	}

}
