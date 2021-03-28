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
    obstacleSprite.setPosition(SCREENWIDTH + 2, Game::getInstance()->player.getPosition().y);
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
    if (clock.getElapsedTime().asSeconds()>2.f && !isFalling) {
        isFalling = true;
        hasTouchedGround = false;
    }
    if (isFalling){
        if (obstacleSprite.getPosition().y < LHEIGHT - obstacleSprite.getGlobalBounds().height && !hasTouchedGround)
            obstacleSprite.move(0, 5);
        else if (obstacleSprite.getPosition().y > startingPosition.y + 2)
            obstacleSprite.move(0, -2);
        else if (obstacleSprite.getPosition().y < startingPosition.y) {
            isFalling = false;
            clock.restart();
        }
        if (obstacleSprite.getPosition().y >= LHEIGHT - obstacleSprite.getGlobalBounds().height )
            hasTouchedGround = true;

    }
}

