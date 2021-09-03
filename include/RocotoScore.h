#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class RocotoScore
{
public:
	sf::Font fontScore;
	sf::Text scoreRocoto;
	sf::Text stageCount;
	sf::Text gameOverR;

	std::string str_scoreR;
	std::string str_stageC;

	std::string scoreR;
	std::string stageC;

	int pointsRocoto;
	int stageNumber;
	int stageProgress = 41;

	void scoreInfo();
	void scoreToString();
};

