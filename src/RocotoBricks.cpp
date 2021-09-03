#include "RocotoBricks.h"

Brick::Brick()
{
	brick = new sf::RectangleShape(sf::Vector2f(100.f, 40.f));
	brick->setTexture(&brickTextures.boxesBricks);
}

Brick::~Brick()
{
	delete brick;
}