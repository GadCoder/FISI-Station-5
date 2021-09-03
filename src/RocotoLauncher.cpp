#include "RocotoLauncher.h"
#include "RocotoBall.h"
#include "RocotoBar.h"
#include "RocotoBricks.h"
#include "RocotoScore.h"
#include "RocotoTextures.h"

#include "SFML/Graphics.hpp"
#include "cmath"

bool colision(sf::CircleShape bola, sf::RectangleShape rectang);
float bouncingBall(sf::CircleShape bola, sf::RectangleShape plato);

void RocotoLauncher::launchGame(int *p_score_ptr)
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Rocoto que bota y rebota");
	sf::Event event;
	Bar stick;
	Ball rocoto;
	RocotoScore scoreStage;
	scoreStage.scoreInfo();

	float directions[2] = { rocoto.directionX, rocoto.directionY };

	Brick ladrillos[5][8];

	while (window.isOpen())
	{
		while (rocoto.alive())
		{
			if (scoreStage.stageProgress == 41)
			{
				for (int j = 0; j < 8; j++)
				{
					for (int i = 0; i < 5; i++)
					{
						ladrillos[i][j].brick->setPosition(100 * j, 40 * i);
					}
				};
				rocoto.gameStatus = false;
				rocoto.bola->setPosition(400, 470);
				rocoto.directionX = 0;
				rocoto.directionY = -0.1 + scoreStage.stageNumber / 10;
				scoreStage.stageProgress = 40;
			}
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();

				if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space))
					rocoto.gameStatus = true;
			}
			window.clear();
			window.draw(*stick.bg);

			if (rocoto.colisionBorders())
			{
				if (rocoto.directionX == 0)
				{
					rocoto.directionX = -rocoto.directionX;
					rocoto.directionY = -rocoto.directionY;
				}
				else
					switch (rocoto.bouncingDir)
					{
						case 0: {
							rocoto.directionX = -rocoto.directionX;
							break;
						}
						case 1: {
							rocoto.directionY = -rocoto.directionY;
							break;
						}
						default: break;
					}
			}

			if (colision(*rocoto.bola, *stick.barrita))
			{
				rocoto.bouncingAngle = bouncingBall(*rocoto.bola, *stick.barrita);
				rocoto.directionX = -(cos(rocoto.bouncingAngle) * directions[0] - sin(rocoto.bouncingAngle) * directions[1]);
				rocoto.directionY = -(sin(rocoto.bouncingAngle) * directions[0] + cos(rocoto.bouncingAngle) * directions[1]);
			}

			for (int j = 0; j < 8; j++)
			{
				for (int i = 0; i < 5; i++)
				{
					if (colision(*rocoto.bola, *ladrillos[i][j].brick))
					{

						if ((rocoto.bola->getPosition().x - ladrillos[i][j].brick->getPosition().x) == 110 || (rocoto.bola->getPosition().x - ladrillos[i][j].brick->getPosition().x) == 10)
							rocoto.directionX = -rocoto.directionX;
						else
							rocoto.directionY = -rocoto.directionY;
						ladrillos[i][j].brick->setPosition(-100, -20);
						scoreStage.pointsRocoto += 10;
						scoreStage.stageProgress -= 1;
						if (scoreStage.stageProgress == 0)
						{
							scoreStage.stageProgress = 41;
							scoreStage.stageNumber += 1;
						}
					}
					window.draw(*ladrillos[i][j].brick);
				};
			};
			scoreStage.scoreToString();
			rocoto.drawBallStart();
			stick.drawBar();

			directions[0] = rocoto.directionX;
			directions[1] = rocoto.directionY;

			window.draw(*stick.barrita);
			window.draw(*stick.chef);
			window.draw(*rocoto.bola);
			window.draw(scoreStage.scoreRocoto);
			window.draw(scoreStage.stageCount);

			window.display();
		}
		*p_score_ptr = scoreStage.pointsRocoto; 
		scoreStage.gameOverR.setString("Game Over");
		window.draw(scoreStage.gameOverR);
		window.draw(*stick.gameOverPic);
		window.display();
		if ((window.pollEvent(event)) && event.type == sf::Event::KeyPressed)
			window.close();
	}
}

bool colision(sf::CircleShape bola, sf::RectangleShape rectang)
{
	sf::FloatRect boundingBoxRocoto = bola.getGlobalBounds();
	sf::FloatRect boundingBoxRectang = rectang.getGlobalBounds();
	if (boundingBoxRocoto.intersects(boundingBoxRectang))
		return true;
	else
		return false;
}

float bouncingBall(sf::CircleShape bola, sf::RectangleShape plato)
{
	int angle;
	if (colision(bola, plato))
	{
		angle = 3.14 + (bola.getPosition().x - plato.getPosition().x) / 120;
	}
	return angle;
}
