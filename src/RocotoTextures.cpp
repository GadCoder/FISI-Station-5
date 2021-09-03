#include "RocotoTextures.h"

RocotoTextures::RocotoTextures()
{
	//Rocoto
	kitchen.loadFromFile("./content/Rocoto/Fondo.png");
	rocotoBall.loadFromFile("./content/Rocoto/rocoto.png");
	platoBar.loadFromFile("./content/Rocoto/Plato.png");
	boxesBricks.loadFromFile("./content/Rocoto/box.png");
	gameOver.loadFromFile("./content/Rocoto/GameOver.png");

	//Chef
	chefStand.loadFromFile("./content/Rocoto/chefStand.png");
	chefR1.loadFromFile("./content/Rocoto/chefR1.png");
	chefR2.loadFromFile("./content/Rocoto/chefR2.png");
	chefL1.loadFromFile("./content/Rocoto/chefL1.png");
	chefL2.loadFromFile("./content/Rocoto/chefL2.png");
}