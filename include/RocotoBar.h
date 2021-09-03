#pragma once
#include <SFML/Graphics.hpp>
#include <RocotoTextures.h>

//Barra de Juego
class Bar
{
public:
	RocotoTextures barTextures;
	int frames = 2;

	//Dibujar
	Bar();
	~Bar();
	sf::RectangleShape* chef;
	sf::RectangleShape* barrita;
	sf::RectangleShape* bg;
	sf::RectangleShape* gameOverPic;

	//mover
	void drawBar();
};
