#include <iostream>
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "game_of_life.h"

#define WIN_W 960
#define WIN_H 540

using namespace std;

game_of_life the_game(WIN_W, WIN_H);

void renderingThread(sf::RenderWindow* window) {
	window->setActive(true);

	while (window->isOpen()) {
		window->clear();
		the_game.iscrtaj(window);
		window->display();
	}
}

int main() {
	unsigned int generation_refresh_time = 2000;	//in milliseconds

	sf::Clock PClock;
	sf::Time Elapsed;
	sf::RenderWindow window(sf::VideoMode(WIN_W, WIN_H), "Just another SFML project - &ln(a)", sf::Style::Default);
	window.setFramerateLimit(30);
	the_game.set_framerate(30);
	window.setActive(false);

	sf::Thread rthread(&renderingThread, &window);
	rthread.launch();

	PClock.restart();
	Elapsed = PClock.getElapsedTime();

	cout << "Game of Life - John Horton Conway, 1970\n\nVelicina prozora/celije : " << WIN_W << "x" << WIN_H << "/" << the_game.get_polje() <<
		"\n\n25% sanse da ce prilikom inicijalizacije u celiji biti zivi organizam.\n\nZnacenje boja:\nZelena - novonastali organizam" << endl <<
		"Crvena - nepromijenjeni organizam\nLjubicasta - umiruci organizam\n\nGeneracija / Organizama:\n";

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		Elapsed = PClock.getElapsedTime();
		if (Elapsed.asMilliseconds() > generation_refresh_time) {
			PClock.restart();
			the_game.sljedeca_generacija();
			the_game.kopiraj();
		}

	}

	return 0;
}