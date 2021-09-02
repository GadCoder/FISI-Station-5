#include "Snake.h"
#include <iostream>
#include <time.h>
#include <chrono>
#include <thread>

//CONSTRUCTOR
Snake::Snake() {
    //Creating the snake head
    sf::RectangleShape head(sf::Vector2f(20.f, 20.f));
    head.setFillColor(sf::Color::White);
    head.setPosition(400.f, 300.f);

    //Creating the food
    rectangleFood.setFoodPosition(snakeBody);

    //Creating snakeBody
    snakeBody.push_back(head);
    bodyDirections.push_back(Directions::Static);

    //Head position
    snakePosX = 400.f;
    snakePosY = 300.f;

    //Game conditions
    gameOver = false;
    keyHasBeenPressed = false;
    bodyExists = false;
    bodySize = snakeBody.size();
    score = 0;


}


void Snake::snakeLogic() {
    handleMovement();
    isGameOver();
    setTextures();
    foodEaten();
}


//START MOVEMENT FUNCTIONS
void Snake::handleMovement() {
    if (keyHasBeenPressed) {
            bodyCanMove();
            moveBody();
            moveSnake();
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
}


void Snake::moveSnake() {
    switch (bodyDirections[0])
    {
    case Directions::Left:
        snakeBody[0].move(-20.f, 0.f);
        break;
    case Directions::Right:
        snakeBody[0].move(20.f, 0.f);
        break;
    case Directions::Up:
        snakeBody[0].move(0.f, -20.f);
        break;
    case Directions::Down:
        snakeBody[0].move(0.f, 20.f);
        break;
    default:
        break;
    }

    snakePosX = snakeBody[0].getPosition().x;
    snakePosY = snakeBody[0].getPosition().y;
};


void Snake::bodyCanMove(){
    Directions *headDir = &bodyDirections[0];
    Directions *prevPartDir = &bodyDirections[1];
    
    switch (*headDir)
    {
    case Directions::Left:{
        if(*prevPartDir == Directions::Right)
            *headDir = *prevPartDir;
        break;
    }
        
    case Directions::Right:{
        if(*prevPartDir == Directions::Left)
            *headDir = *prevPartDir;
        break;

    }
    case Directions::Up:{
        if(*prevPartDir == Directions::Down)
            *headDir = *prevPartDir;     
        break;
    }
       
    case Directions::Down:{
        if(*prevPartDir == Directions::Up)
            *headDir = *prevPartDir;
        break;
    }
    default:
        break;
    }
}


void Snake::moveBody() {
    float nextXPos;
    float nextYPos;
    if (bodyExists) {
        for (int i = bodySize - 1; i > 0; i--) {
            nextXPos = snakeBody[i-1].getPosition().x;
            nextYPos = snakeBody[i-1].getPosition().y;
            snakeBody[i].setPosition(nextXPos,nextYPos);
            bodyDirections[i] = bodyDirections[i-1];
        }
    }
}

//END MOVEMENT FUNCTIONS


//FOOD 
void Snake::foodEaten() {
    sf::FloatRect headBoundingBox = snakeBody[0].getGlobalBounds();
    sf::FloatRect foodBoundingBox = rectangleFood.rectangle->getGlobalBounds();
    if (headBoundingBox.intersects(foodBoundingBox)) {
        rectangleFood.setFoodPosition(snakeBody);
        bodyExists = true;
        score += 10;
        makeBody();
    }
}


//START CREATING BODY FUNCTIONS
void Snake::makeBody() {
    sf::RectangleShape bodyPart = createPart();
    snakeBody.push_back(bodyPart);
    bodyDirections.push_back(bodyDirections[bodySize - 1]);
    bodySize = snakeBody.size();
}


sf::RectangleShape Snake::createPart() {
    sf::RectangleShape temp(sf::Vector2f(20.f, 20.f));
    temp.setFillColor(sf::Color::White);
    setPartPosition(temp);
    return temp;
}


void Snake::setPartPosition(sf::RectangleShape &bodyPart) {
    int index = bodySize - 1;
    float tempPosX, tempPosY;
    switch (bodyDirections[index])
    {
    case Directions::Left:
        tempPosX = 20.0f;
        break;
    case Directions::Right:
        tempPosX = -20.0f;
        break;
    case Directions::Up:
        tempPosY = 20.0f;
        break;
    case Directions::Down:
        tempPosY = -20.0f;
        break;
    default:
        break;
    }

    tempPosX += snakeBody[index].getPosition().x;
    tempPosY += snakeBody[index].getPosition().y;
    bodyPart.setPosition(tempPosX, tempPosY);
}

//END CREATING BODY FUNCTIONS


void Snake::setTextures() {
    switch (bodyDirections[0])
    {
        case Directions::Left:
            snakeBody[0].setTexture(&snakeTextures.headLeft);
            break;
        case Directions::Right:
            snakeBody[0].setTexture(&snakeTextures.headRight);
            break;
        case Directions::Up:
            snakeBody[0].setTexture(&snakeTextures.headUp);
            break;
        case Directions::Down:
            snakeBody[0].setTexture(&snakeTextures.headDown);
            break;
        default:
            snakeBody[0].setTexture(&snakeTextures.headUp);
            break;
    }

    if(bodyExists){
        for(int i = 1; i < bodySize; i++){
            if(i % 2 == 0)
                snakeBody[i].setTexture(&snakeTextures.body_one);
            else
                snakeBody[i].setTexture(&snakeTextures.body_two);
        }
    }  
}

void Snake::isGameOver(){
    sf::FloatRect headBoundingBox = snakeBody[0].getGlobalBounds();
    if(snakePosX > 780 || snakePosX < 0)
        gameOver = true;

    if(snakePosY > 580 || snakePosY < 0)
        gameOver = true;

    if(bodyExists){
        for(int i = 1; i < bodySize; i++){
            sf::FloatRect bodyBoundingBox = snakeBody[i].getGlobalBounds();
            if(headBoundingBox.intersects(bodyBoundingBox))
                gameOver = true;
        }
    }
}
