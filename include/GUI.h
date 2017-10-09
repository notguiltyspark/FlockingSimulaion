#pragma once

#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include <iostream>

class GUI{
private:

	sf::Text fps;
	sf::Text boidsNumber;
	sf::Text parallel_status;
	
	sf::Font settings_font;
	
	
public:
	
	GUI();
	~GUI() {};

	void setFps(const int frames);
	void setBoidsNumber(const int sz);
	void setParallelStatus(const bool isParallel);

	//void update();
	/*
		- How to incorporate Clock (and Settings)?
		- window as argument to constructor ? (i.e. check if window's size allows UI)
	*/
	void draw(sf::RenderWindow& window);
};

#endif 
