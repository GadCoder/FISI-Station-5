#include "RocotoBall.h"
//Pelota (Rocoto)

Ball::Ball()
{
	bola = new sf::CircleShape(10.f);
	bola->setOrigin(10.f, 10.f);
	bola->setPosition(400, 470);
	bola->setTexture(&ballTexture.rocotoBall);
	gameStatus = false;
	directionX = 0;
	directionY = -0.1;
	bouncingAngle = 0;
}

Ball::~Ball()
{
	delete bola;
}

//se choco el rocoto?
bool Ball::colisionBorders()
{
	if (bola->getPosition().y <= 10)
	{
		bouncingDir = up;
		return true;
	}
	else if (bola->getPosition().x <= 10 || bola->getPosition().x >= 790)
	{
		bouncingDir = sides;
		return true;
	}
	else
		return false;
}

//Pelota rebotando (analisis de rebote)
void Ball ::drawBallGame()
{
	bola->move(directionX, directionY);
}

//Pelota rebotando
void Ball ::drawBallStart()
{
	if (!gameStatus)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && bola->getPosition().x >= 60)
			bola->move(-0.1, 0);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && bola->getPosition().x <= 740)
			bola->move(+0.1, 0);
	}
	else
		drawBallGame();
}

bool Ball::alive()
{
	if (bola->getPosition().y >= 610)
		return false;
	else
		return true;
}
