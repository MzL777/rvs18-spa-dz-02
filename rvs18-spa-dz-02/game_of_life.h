#ifndef _GAME_OF_LIFE_H_
#define _GAME_OF_LIFE_H_

#include <ctime>
#include <SFML\Graphics.hpp>
#include <iostream>
#include <chrono>
#include <string>

using namespace std;

class game_of_life {
private:
	static const unsigned int STUPACA = 90;//320;
	static const unsigned int REDAKA = 160;//180;
	unsigned long long broj_generacije = 0;
	int framerate = 30;
	float stepX, stepY, period = 255.f / framerate;
	unsigned int width, height;
	int _transition[REDAKA][STUPACA];
	bool _generacija[REDAKA][STUPACA];
	bool _sljedeca_generacija[REDAKA][STUPACA];
	sf::ConvexShape* convex[REDAKA][STUPACA];
	sf::RenderWindow* window;
	bool slucajna_vrijednost();
	bool celija_zauzeta(int i, int j);
	int broj_susjeda(int i, int j);
	int slucajni_broj(unsigned min, unsigned max);
public:
	game_of_life(unsigned int width, unsigned int height);
	~game_of_life();
	void kopiraj();
	void set_framerate(int fps);
	void sljedeca_generacija();
	void iscrtaj(sf::RenderWindow* window);
	std::string get_polje();
};

#endif
