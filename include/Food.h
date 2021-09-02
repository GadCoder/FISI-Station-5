#pragma once
#include <SFML/Graphics.hpp>

struct Food {
    sf::RectangleShape* rectangle;
    float foodPosX, foodPosY;
    Food();
    ~Food();
    void setFoodPosition(std::vector<sf::RectangleShape> snakeBody);   
    bool foodInBody(std::vector<sf::RectangleShape> snakeBody);
};

