#include "SnakeTextures.h"
Textures::Textures(){
        //Head textures
        headLeft.loadFromFile("./content/Snake/head_left.png");
        headRight.loadFromFile("./content/Snake/head_right.png");
        headUp.loadFromFile("./content/Snake/head_up.png");
        headDown.loadFromFile("./content/Snake/head_down.png");
        //Body texture
        body.loadFromFile("./content/Snake/body.png");
}