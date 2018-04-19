#include "game_of_life.h"

/*		PRIVATE		*/

bool game_of_life::slucajna_vrijednost() {
	srand(time(nullptr));
	
	for (unsigned i = 0; i < REDAKA; ++i) {
		for (unsigned j = 0; j < STUPACA; ++j) {
			if (slucajni_broj(0, 3) == 0)_generacija[i][j] = 1;
			else _generacija[i][j] = 0;
		}
	}

	return false;
}

bool game_of_life::celija_zauzeta(int i, int j) {
	return _generacija[i][j];
}

int game_of_life::broj_susjeda(int i, int j) {
	int non = 0;
	int fx = -1, tx = 1;
	int fy = -1, ty = 1;

	if (i - 1 < 0) fy = 0;
	else if (i + 1 > REDAKA - 1) ty = 0;

	if (j - 1 < 0) fx = 0;
	else if (j + 1 > STUPACA - 1) tx = 0;

	for (int x = fy; x <= ty; ++x)
		for (int y = fx; y <= tx; ++y)
			if (!(x == y && x == 0) && 
				celija_zauzeta(i + x, j + y)) ++non;
	return non;
}

int game_of_life::slucajni_broj(unsigned min, unsigned max) {
	return rand() % (max - min + 1) + min;
}

void game_of_life::kopiraj() {
	for (unsigned i = 0; i < REDAKA; ++i) {
		for (unsigned j = 0; j < STUPACA; ++j) {
			_generacija[i][j] = _sljedeca_generacija[i][j];
		}
	}
}

void game_of_life::sljedeca_generacija() {
	for (unsigned i = 0; i < REDAKA; ++i) {
		for (unsigned j = 0; j < STUPACA; ++j) {
			int non = broj_susjeda(i, j);
			if (_generacija[i][j]) {
				if (non < 2 || non > 3)_sljedeca_generacija[i][j] = 0;
				else _sljedeca_generacija[i][j] = 1;
			}
			else {
				if (non == 3)_sljedeca_generacija[i][j] = 1;
				else _sljedeca_generacija[i][j] = 0;
			}
		}
	}
}

/*		PUBLIC		*/

game_of_life::game_of_life(unsigned int width, unsigned int height, int refresh_time, sf::RenderWindow* window) {
	this->width = width;
	this->height = height;
	this->refresh_time = refresh_time;
	this->window = window;

	stepX = (height * 1.f) / STUPACA;
	stepY = (width * 1.f) / REDAKA;
	period = (refresh_time * 1.f);

	for (unsigned i = 0; i < REDAKA; ++i) {
		for (unsigned j = 0; j < STUPACA; ++j) {
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
	delete[] convex;
}

void game_of_life::iscrtaj() {
	system("cls");
	auto tPoint = std::chrono::high_resolution_clock::now();
	sljedeca_generacija();
	auto tPoint2 = std::chrono::high_resolution_clock::now();
	std::cout << "next_gen_time:\t" << std::chrono::duration_cast<std::chrono::microseconds>(tPoint2 - tPoint).count() << std::endl;
	
	tPoint = std::chrono::high_resolution_clock::now();
	for (unsigned i = 0; i < REDAKA; ++i) {
		for (unsigned j = 0; j < STUPACA; ++j) {
			if (_generacija[i][j]) {
				window->draw(*convex[i][j]);
			}
		}
	}
	tPoint2 = std::chrono::high_resolution_clock::now();
	std::cout << "draw_time:\t" << std::chrono::duration_cast<std::chrono::microseconds>(tPoint2 - tPoint).count() << std::endl;

	tPoint = std::chrono::high_resolution_clock::now();
	kopiraj();
	tPoint2 = std::chrono::high_resolution_clock::now();
	std::cout << "kopiraj_time:\t" << std::chrono::duration_cast<std::chrono::microseconds>(tPoint2 - tPoint).count() << std::endl;

}
