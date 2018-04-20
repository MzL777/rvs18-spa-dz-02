#include "game_of_life.h"
#include <sstream>

/*		###PRIVATE###		*/

bool game_of_life::slucajna_vrijednost() {
	srand(time(nullptr));

	for (unsigned i = 0; i < REDAKA; ++i)
		for (unsigned j = 0; j < STUPACA; ++j)
			_generacija[i][j] = slucajni_broj(0, 3) == 0;

	return false;
}

bool game_of_life::celija_zauzeta(int i, int j) {
	return _generacija[i][j];
}

int game_of_life::broj_susjeda(int i, int j) {//~4170-4175
	int non = 0;

	if (i - 1 < 0) {
		non += celija_zauzeta(i + 1, j);
		if (j - 1 < 0) {
			non += celija_zauzeta(i + 1, j + 1);
			non += celija_zauzeta(i, j + 1);
		}
		else if (j + 1 > STUPACA - 1) {
			non += celija_zauzeta(i + 1, j - 1);
			non += celija_zauzeta(i, j - 1);
		}
		else {
			non += celija_zauzeta(i + 1, j + 1);
			non += celija_zauzeta(i, j + 1);
			non += celija_zauzeta(i + 1, j - 1);
			non += celija_zauzeta(i, j - 1);
		}
		return non;
	}
	else if (i + 1 > REDAKA - 1) {
		non += celija_zauzeta(i - 1, j);
		if (j - 1 < 0) {
			non += celija_zauzeta(i - 1, j + 1);
			non += celija_zauzeta(i, j + 1);
		}
		else if (j + 1 > STUPACA - 1) {
			non += celija_zauzeta(i - 1, j - 1);
			non += celija_zauzeta(i, j - 1);
		}
		else {
			non += celija_zauzeta(i - 1, j + 1);
			non += celija_zauzeta(i, j + 1);
			non += celija_zauzeta(i - 1, j - 1);
			non += celija_zauzeta(i, j - 1);
		}
		return non;
	}
	else {
		non += celija_zauzeta(i - 1, j);
		non += celija_zauzeta(i + 1, j);
		if (j - 1 < 0) {
			non += celija_zauzeta(i - 1, j + 1);
			non += celija_zauzeta(i, j + 1);
			non += celija_zauzeta(i + 1, j + 1);
		}
		else if (j + 1 > STUPACA - 1) {
			non += celija_zauzeta(i - 1, j - 1);
			non += celija_zauzeta(i, j - 1);
			non += celija_zauzeta(i + 1, j - 1);
		}
		else {
			non += celija_zauzeta(i - 1, j + 1);
			non += celija_zauzeta(i, j + 1);
			non += celija_zauzeta(i + 1, j + 1);
			non += celija_zauzeta(i - 1, j - 1);
			non += celija_zauzeta(i, j - 1);
			non += celija_zauzeta(i + 1, j - 1);
		}
		return non;
	}
}

int game_of_life::slucajni_broj(unsigned min, unsigned max) {
	return rand() % (max - min + 1) + min;
}

/*		###PUBLIC###		*/

game_of_life::game_of_life(unsigned int width, unsigned int height) {
	this->width = width;
	this->height = height;
	this->window = window;

	stepX = (height * 1.f) / STUPACA;
	stepY = (width * 1.f) / REDAKA;

	for (unsigned i = 0; i < REDAKA; ++i) {
		for (unsigned j = 0; j < STUPACA; ++j) {
			_transition[i][j] = 0;
			convex[i][j] = new sf::ConvexShape;
			convex[i][j]->setPointCount(4);
			convex[i][j]->setFillColor(sf::Color(255, 0, 0));
			convex[i][j]->setPoint(0, sf::Vector2f((i + 1.0000001f) * stepY, (j + 1.0000001f) * stepX));
			convex[i][j]->setPoint(1, sf::Vector2f((i + 0.0000001f) * stepY, (j + 1.0000001f) * stepX));
			convex[i][j]->setPoint(2, sf::Vector2f((i + 0.0000001f) * stepY, (j + 0.0000001f) * stepX));
			convex[i][j]->setPoint(3, sf::Vector2f((i + 1.0000001f) * stepY, (j + 0.0000001f) * stepX));
		}
	}

	slucajna_vrijednost();
}

game_of_life::~game_of_life() {
	for (unsigned i = 0; i < REDAKA; ++i)
		for (unsigned j = 0; j < STUPACA; ++j)
			delete convex[i][j];
}

void game_of_life::kopiraj() {
	for (unsigned i = 0; i < REDAKA; ++i) {
		for (unsigned j = 0; j < STUPACA; ++j) {
			_generacija[i][j] = _sljedeca_generacija[i][j];
		}
	}
}

void game_of_life::set_framerate(int fps) {
	framerate = fps;
	period = 255.f / framerate;
}

void game_of_life::sljedeca_generacija() {
	int alive = 0;
	for (unsigned i = 0; i < REDAKA; ++i) {
		for (unsigned j = 0; j < STUPACA; ++j) {
			int non = broj_susjeda(i, j);
			if (_generacija[i][j]) {
				++alive;
				if (non < 2 || non > 3) {
					_sljedeca_generacija[i][j] = 0;
					_transition[i][j] = framerate;
				}
				else _sljedeca_generacija[i][j] = 1;
			}
			else {
				if (non == 3) {
					_sljedeca_generacija[i][j] = 1;
					_transition[i][j] = framerate;
				}
				else _sljedeca_generacija[i][j] = 0;
			}
		}
	}
	std::stringstream ss;
	ss << ++broj_generacije << "x" << alive;
	cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
	std::cout << broj_generacije << "/" << alive;// << endl;
}

void game_of_life::iscrtaj(sf::RenderWindow* window) {
	//auto tPoint = std::chrono::high_resolution_clock::now();
	for (unsigned i = 0; i < REDAKA; ++i) {
		for (unsigned j = 0; j < STUPACA; ++j) {
			if (_transition[i][j] > framerate / 2) {
				if (_generacija[i][j]) {
					//creating - part 1
					//transition framerate -> framerate / 2		30 -> 15
					//green 0 -> 191
					//red 0 -> 0
					convex[i][j]->setFillColor(sf::Color(0, (framerate - _transition[i][j]) * period * 1.5f, 0));
				}
				else {
					//dying - part 1
					//transition framerate -> framerate / 2		30 -> 15
					//blue/green 0 -> 127
					//red 255 -> 127
					convex[i][j]->setFillColor(sf::Color(_transition[i][j] * period, 0, (framerate - _transition[i][j]) * period));
				}
				--_transition[i][j];
				window->draw(*convex[i][j]);
			}
			else if (_transition[i][j] > 0) {
				if (_generacija[i][j]) {
					//creating - part 2
					//transition framerate / 2 -> 0		15 -> 0
					//green 191 -> 0
					//red 0 -> 255
					convex[i][j]->setFillColor(sf::Color((framerate - _transition[i][j] * 2) * period, _transition[i][j] * period * 1.5f, 0));
				}
				else {
					//dying - part 2
					//transition framerate / 2 -> 0		15 -> 0
					//blue/green 127 -> 0
					//red 127 -> 0
					convex[i][j]->setFillColor(sf::Color(_transition[i][j] * period, 0, _transition[i][j] * period));
				}
				--_transition[i][j];
				window->draw(*convex[i][j]);
			}
			else {
				if (_generacija[i][j]) {
					convex[i][j]->setFillColor(sf::Color(255, 0, 0));
					window->draw(*convex[i][j]);
				}
			}
		}
	}
	//auto tPoint2 = std::chrono::high_resolution_clock::now();
	//std::cout << "draw_time:\t" << std::chrono::duration_cast<std::chrono::microseconds>(tPoint2 - tPoint).count() << "\tus\n";
}

std::string game_of_life::get_polje() {
	std::stringstream ss;
	ss << REDAKA << "x" << STUPACA;
	return ss.str();
}
