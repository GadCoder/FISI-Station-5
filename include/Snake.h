#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Textures.h"
#include "Food.h"  


enum class Directions { Left, Right, Up, Down , Static};

class Snake {
    public:
        Food rectangleFood;
        bool keyHasBeenPressed;
        int score;
        std::vector<sf::RectangleShape> snakeBody;
        std::vector<Directions> bodyDirections;
        bool gameOver;
    private:
        Textures snakeTextures;
        bool bodyExists;
        float snakePosX, snakePosY;
        int bodySize;
    //Methods
    private:
        void moveSnake();
        void moveBody();
        void bodyCanMove();
        void makeBody();
        sf::RectangleShape createPart();
        void setPartPosition(sf::RectangleShape &bodyPart);
        void setTextures();
        void handleMovement();
        void foodEaten();
        void isGameOver();
    public:
        Snake();
        void snakeLogic();

};
