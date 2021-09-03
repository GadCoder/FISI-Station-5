#pragma once
#include <SFML/Graphics.hpp>
#include <RocotoTextures.h>

class Brick
{
public:
	//Dibujar Brick
	Brick();
	~Brick();
	sf::RectangleShape* brick;
	RocotoTextures brickTextures;
};



