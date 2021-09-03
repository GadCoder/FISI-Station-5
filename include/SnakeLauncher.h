#include "Snake.h"

class SnakeLauncher{
public:
    void launchGame(int *p_score_ptr);
    SnakeLauncher(){
        bgTexture.loadFromFile("./content/Snake/background.png");
        background.setTexture(bgTexture);
    }
private:   
    Snake snake;
    sf::Sprite background;
    sf::Texture bgTexture;
};