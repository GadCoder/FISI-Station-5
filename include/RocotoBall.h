#pragma once
#include <SFML/Graphics.hpp>
#include <RocotoTextures.h>

//Pelota (Rocoto)
class Ball
{
public:
	//info de la pelota
	Ball();
	~Ball();
	sf::CircleShape* bola;
	RocotoTextures ballTexture;

	//Movimiento de bola
	float directionX;
	float directionY;
	float bouncingAngle;
	//float bouncingAngleBorder();
	enum directions
	{
		sides,
		up
	};
	int bouncingDir;

	//condicion
	bool alive();
	bool gameStatus;

	bool colisionBorders();
	void drawBallGame();
	void drawBallStart();
};
