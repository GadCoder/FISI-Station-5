#include "RocotoScore.h"

void RocotoScore::scoreInfo()
{
	fontScore.loadFromFile("./content/Fonts/rocoto_Font.ttf");

	scoreRocoto.setFont(fontScore);
	stageCount.setFont(fontScore);
	gameOverR.setFont(fontScore);

	scoreRocoto.setCharacterSize(15);
	stageCount.setCharacterSize(15);
	gameOverR.setCharacterSize(50);
	gameOverR.setFillColor(sf::Color::Red);

	scoreRocoto.setPosition(10, 590);
	stageCount.setPosition(700, 590);
	gameOverR.setPosition(250, 250);

	pointsRocoto = 0;
	stageNumber = 1;
}

void RocotoScore::scoreToString()
{
	std::string str_scoreR = std::to_string(pointsRocoto);
	std::string str_stageC = std::to_string(stageNumber);

	scoreR = "Points: " + str_scoreR;
	stageC = "Stage: " + str_stageC;

	scoreRocoto.setString(scoreR);
	stageCount.setString(stageC);
}