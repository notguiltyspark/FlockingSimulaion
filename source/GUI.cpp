#include "GUI.h"

GUI::GUI() {
	if (!settings_font.loadFromFile("Inconsolata-Regular.ttf"))
	{
		std::cout << "Error: can't load fonts" << std::endl;
	}
	fps.setFont(settings_font);
	fps.setPosition(20, 20);
	fps.setCharacterSize(15);
	fps.setFillColor(sf::Color::White);

	boidsNumber.setFont(settings_font);
	boidsNumber.setPosition(20, 45);
	boidsNumber.setCharacterSize(15);
	boidsNumber.setFillColor(sf::Color::White);

	parallel_status.setFont(settings_font);
	parallel_status.setPosition(20, 70);
	parallel_status.setCharacterSize(15);
	parallel_status.setFillColor(sf::Color::White);

}

void GUI::setFps(const int frames){
	fps.setString("fps: " + std::to_string(frames));

}


void GUI::setBoidsNumber(const int sz){
	boidsNumber.setString("boids: " + std::to_string(sz));
}

void GUI::setParallelStatus(const bool isParallel){
	if (isParallel)
		parallel_status.setString("multithreading: ON");
	else
		parallel_status.setString("multithreading: OFF");
}

void GUI::draw(sf::RenderWindow& window) {
	window.draw(fps);
	window.draw(boidsNumber);
	window.draw(parallel_status);
}
