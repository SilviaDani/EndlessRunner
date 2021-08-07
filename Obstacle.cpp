//
// Created by user on 26/02/2021.
//

#include "Obstacle.h"
#include "CONSTANTS.h"
#include "Player.h"
#include "Game.h"

void Obstacle::draw(sf::RenderWindow &window) {
    window.draw(obstacleSprite);
}

void Obstacle::setPosition(float x, float y) {
    obstacleSprite.setPosition(x, y);
}

void Obstacle::move(float x, float y) {
    obstacleSprite.move(x , y);
}

const sf::Sprite &Obstacle::getObstacleSprite() const {
    return obstacleSprite;
}

Rocket::Rocket() {
    if (!obstacleTexture.loadFromFile("../Sprites/rocket.png")) {
        //TODO handle exception
    }
    obstacleSprite.setTexture(obstacleTexture);
    obstacleSprite.setScale(-0.1 , 0.1);
    if (Giant* form = dynamic_cast<Giant*>(Game::getInstance()->getPlayer().getForm())){
        float yCoordinate = -1.0f;
        while(yCoordinate < form->getBodySprite().getGlobalBounds().top + 100 || yCoordinate > LHEIGHT - form->getSprite().getGlobalBounds().height - 0.5f)
            yCoordinate = rand()%int(LHEIGHT - (Game::getInstance()->getPlayer().getGlobalBounds().height)/2
                    - obstacleSprite.getGlobalBounds().height) + (Game::getInstance()->getPlayer().getGlobalBounds().height);
        obstacleSprite.setPosition(SCREENWIDTH + 2, yCoordinate);
    }
    else{
        float yCoordinate = -1.0f;
        while(yCoordinate < 0 || yCoordinate > LHEIGHT - obstacleSprite.getGlobalBounds().height)
            yCoordinate = Game::getInstance()->getPlayer().getPosition().y + rand()%200 - 100;
        obstacleSprite.setPosition(SCREENWIDTH + 2, yCoordinate);
    }
}


void Rocket::doAction() {
    obstacleSprite.move(-5, 0);
}


Stone::Stone() {
    if (!obstacleTexture.loadFromFile("../Sprites/stone.png")) {
        //TODO handle exception
    }
    obstacleSprite.setTexture(obstacleTexture);
    obstacleSprite.setScale(0.65 , 0.65);
    obstacleSprite.setPosition(SCREENWIDTH + 2, 150);
    startingPosition = obstacleSprite.getPosition();
    clock.restart();
}

void Stone::doAction() {
    float fallingTime = rand()%4 + 2.7f + (rand()%101)/100;
    if (clock.getElapsedTime().asSeconds()>fallingTime && !isFalling) {
        isFalling = true;
        hasTouchedGround = false;
    }
    if (isFalling){
        if (obstacleSprite.getPosition().y < LHEIGHT - obstacleSprite.getGlobalBounds().height && !hasTouchedGround)
            obstacleSprite.move(0, 5);
        else if (obstacleSprite.getPosition().y > startingPosition.y + 2)
            obstacleSprite.move(0, - 2);
        else if (obstacleSprite.getPosition().y < startingPosition.y) {
            isFalling = false;
            clock.restart();
        }
        if (obstacleSprite.getPosition().y >= LHEIGHT - obstacleSprite.getGlobalBounds().height )
            hasTouchedGround = true;
    }
}

