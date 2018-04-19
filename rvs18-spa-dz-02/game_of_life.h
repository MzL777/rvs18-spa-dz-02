#ifndef _GAME_OF_LIFE_H_
#define _GAME_OF_LIFE_H_

#include <ctime>
#include <SFML\Graphics.hpp>
#include <iostream>
#include <chrono>

using namespace std;

class game_of_life {
private:
	static const unsigned int STUPACA = 270;
	static const unsigned int REDAKA = 480;
	float stepX, stepY, period;
	unsigned int width, height, refresh_time;
	bool _generacija[REDAKA][STUPACA];
	bool _sljedeca_generacija[REDAKA][STUPACA];
	sf::ConvexShape* convex[REDAKA][STUPACA];
	sf::RenderWindow* window;
	bool slucajna_vrijednost();
	bool celija_zauzeta(int i, int j);
	int broj_susjeda(int i, int j);
	int slucajni_broj(unsigned min, unsigned max);
	void kopiraj();
	void sljedeca_generacija();
public:
	game_of_life(unsigned int width, unsigned int height, int refresh_time, sf::RenderWindow* window);
	~game_of_life();
	void iscrtaj();
};

#endif
