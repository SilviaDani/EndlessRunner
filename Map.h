//
// Created by danis on 06/01/2021.
//

#ifndef ENDLESSRUNNER_MAP_H
#define ENDLESSRUNNER_MAP_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include "Obstacle.h"
#include "ObstacleFactory.h"
#include "Subject.h"


class Map : public Subject {
public:
    Map();
    void draw(sf::RenderWindow &window);
    void moveBackground();
    void moveLand();
    void moveGrass();
    void checkCollisions(Player& player);
    void moveObstacle();
    void instantiateObstacle();
    void movePowerUp();
    void instantiatePowerUp(Player& player);
private:
    sf::Texture backgroundTexture;
    std::vector <sf::Sprite>backgroundSprites;
    sf::Texture landTexture;
    std::vector <sf::Sprite>landSprites;
    sf::Texture grassTexture;
    std::vector <sf::Sprite>grassSprites;
    std::vector <Obstacle*>obstacles;
    StoneFactory stoneFactory;
    RocketFactory rocketFactory;
    sf:: Texture powerUpTexture;
    std::vector <sf::Sprite>powerUpSprite;
    sf::Clock clock;
    sf:: Text distance;
    sf:: Font font;
};


#endif //ENDLESSRUNNER_MAP_H
