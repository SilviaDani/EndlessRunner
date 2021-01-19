//
// Created by danis on 06/01/2021.
//

#ifndef ENDLESSRUNNER_MAP_H
#define ENDLESSRUNNER_MAP_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "Yoshi.h"


class Map {
public:
    Map();
    void draw(sf::RenderWindow &window);
    void moveBackground();
    void moveLand();
    void moveGrass();
    void checkCollisions(Yoshi& player);
private:
    sf::Texture backgroundTexture;
    std::vector <sf::Sprite>backgroundSprites;
    sf::Texture landTexture;
    std::vector <sf::Sprite>landSprites;
    sf::Texture grassTexture;
    std::vector <sf::Sprite>grassSprites;
};


#endif //ENDLESSRUNNER_MAP_H
