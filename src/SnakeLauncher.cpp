#include "SnakeLauncher.h"
#include <SFML/Graphics.hpp>
#include <iostream>
void gameLogic(sf::RenderWindow &window, Snake &snake, sf::Sprite &background, int *p_score_ptr);
void gameLose(sf::RenderWindow &window, sf::Sprite &background);
void handleKeyPressed(sf::Event event, sf::RenderWindow &window, Snake &snake);


void SnakeLauncher::launchGame(int *p_score_ptr){
sf::RenderWindow window(sf::VideoMode(800, 600), "Loro Machaco Hambrientoo");

    while (window.isOpen()){ 
        sf::Event event;
        while (window.pollEvent(event)){
            switch (event.type){ 
                case sf::Event::Closed:
                    window.close();
                    break;           
                case sf::Event::KeyPressed: {
                    handleKeyPressed(event,window,snake);
                    break;
                    }
                default:
                    break;
            }         
        }

        gameLogic(window,snake, background, p_score_ptr);
    }
}


void gameLogic(sf::RenderWindow &window, Snake &snake, sf::Sprite &background, int *p_score_ptr){
    if(!snake.gameOver){
        window.clear(sf::Color::White);
        window.draw(background);
        snake.snakeLogic();
        for(sf::RectangleShape bodyPart : snake.snakeBody)
            window.draw(bodyPart); 
        window.draw(*snake.rectangleFood.rectangle);
        window.display();
    }else{
        *p_score_ptr = snake.score; 
        gameLose(window, background);
    }
}


void handleKeyPressed(sf::Event event, sf::RenderWindow &window, Snake &snake){
    if(!snake.keyHasBeenPressed)
        snake.keyHasBeenPressed = true;

    if(snake.gameOver){
        window.close();
    } else {    
        if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left) {
            snake.bodyDirections[0] = Directions::Left;
        }
        if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) {
            snake.bodyDirections[0] = Directions::Right;
        }
        if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up) {
            snake.bodyDirections[0]  = Directions::Up;
        }
        if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down) {
            snake.bodyDirections[0] =  Directions::Down;
        }
    }

}

void gameLose(sf::RenderWindow &window, sf::Sprite &background){
    sf::Font font;
    font.loadFromFile("./content/Fonts/Snake_game_over.ttf");
    sf::Text text;
    text.setFont(font);
    text.setString("GAME OVER");
    text.setCharacterSize(48);
    text.setFillColor(sf::Color::Black);
    text.setPosition(340.0f,240.0f);

    window.clear(sf::Color::White);
    window.draw(background);
    window.draw(text);
    window.display();
}