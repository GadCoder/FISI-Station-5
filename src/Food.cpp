#include "Food.h"

Food::Food() {
    rectangle = new sf::RectangleShape(sf::Vector2f(20.f, 20.f));
    rectangle->setFillColor(sf::Color::Red);
}


Food::~Food() {
    delete rectangle;
}


void Food::setFoodPosition(std::vector<sf::RectangleShape> snakeBody) {
    do {
        srand(time(0));
        foodPosX = (rand() % 39) * 20 + 0.0f;
        foodPosY = (rand() % 29) * 20 + 0.0f;
    } while (foodInBody(snakeBody));
    rectangle->setPosition(foodPosX,foodPosY);
};


bool Food::foodInBody(std::vector<sf::RectangleShape> snakeBody){
    //bool inBody = false;
    for(sf::RectangleShape bodyPart : snakeBody){
        if(bodyPart.getPosition().x == foodPosX && bodyPart.getPosition().y == foodPosY)
            return true;  
    }
    return false;
}