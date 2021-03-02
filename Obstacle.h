//
// Created by user on 26/02/2021.
//

#ifndef ENDLESSRUNNER_OBSTACLE_H
#define ENDLESSRUNNER_OBSTACLE_H
#include <iostream>
#include <SFML/Graphics.hpp>

/*
 * enum class ObstacleType{
    STONE, ROCKET
};
*/

class Obstacle {
public:
    virtual void doAction()=0;
    void draw(sf::RenderWindow &window);
    void setPosition(float x, float y);
    void move(float x, float y);
protected:
    sf:: Texture obstacleTexture;
    sf:: Sprite obstacleSprite;
};

class Stone: public Obstacle{
public:
 Stone();
 void doAction() override;
private:
 sf::Clock clock;
};

class Rocket: public Obstacle{
public:
    Rocket();
    void doAction() override;
};
#endif //ENDLESSRUNNER_OBSTACLE_H
