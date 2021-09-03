#include "RocotoBar.h"


//Definir barra
Bar ::Bar()
{
	barrita = new sf::RectangleShape(sf::Vector2f(120.f, 20.f));
	barrita->setOrigin(60.f, 10.f);
	barrita->setPosition(400, 490);
	barrita->setTexture(&barTextures.platoBar);

	chef = new sf::RectangleShape(sf::Vector2f(80.f, 80.f));
	chef->setOrigin(40.f, 40.f);
	chef->setPosition(400, 540);
	chef->setTexture(&barTextures.chefStand);

	bg = new sf::RectangleShape(sf::Vector2f(800.f, 600.f));
	bg->setTexture(&barTextures.kitchen);

	gameOverPic = new sf::RectangleShape(sf::Vector2f(200.f, 300.f));
	gameOverPic->setTexture(&barTextures.gameOver);
	gameOverPic->setOrigin(100, 150);
	gameOverPic->setPosition(400, 450.f);
}

Bar ::~Bar()
{
	delete barrita;
	delete chef;
	delete bg;
	delete gameOverPic;
}

//DibujarBarra
void Bar ::drawBar()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && barrita->getPosition().x >= 60)
	{
		frames -= 1;
		barrita->move(-0.1, 0);
		chef->move(-0.1, 0);
		if (frames >= -20)
			chef->setTexture(&barTextures.chefL1);
		else if (frames >= -40)
			chef->setTexture(&barTextures.chefL2);
		else
			chef->setTexture(&barTextures.chefStand);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && barrita->getPosition().x <= 740)
	{
		frames += 1;
		barrita->move(+0.1, 0);
		chef->move(+0.1, 0);
		if (frames <= 20)
			chef->setTexture(&barTextures.chefR1);
		else if (frames <= 40)
			chef->setTexture(&barTextures.chefR2);
		else
			chef->setTexture(&barTextures.chefStand);
	}
	else
		chef->setTexture(&barTextures.chefStand);
	if (frames < -60 || frames > 60)
		frames = 2;
}