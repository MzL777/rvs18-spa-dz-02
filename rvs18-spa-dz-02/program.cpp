#include <iostream>
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "game_of_life.h"

#define WIN_W 640
#define WIN_H 360

using namespace std;

int main() {
	unsigned int generation_refresh_time = 200;	//in milliseconds

	sf::Clock PClock;
	sf::Time Elapsed;
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(WIN_W, WIN_H), "Just another SFML project - &ln(a)", sf::Style::Default, settings);
	//window.setFramerateLimit(60);
	
	PClock.restart();
	Elapsed = PClock.getElapsedTime();

	game_of_life the_game(WIN_W, WIN_H, generation_refresh_time, &window);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		Elapsed = PClock.getElapsedTime();
		if (Elapsed.asMilliseconds() > generation_refresh_time) {
			PClock.restart();

			window.clear();
			the_game.iscrtaj();
			window.display();
		}

	}

	return 0;
}