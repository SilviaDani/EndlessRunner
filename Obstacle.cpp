//
// Created by user on 26/02/2021.
//

#include "Obstacle.h"
#include "CONSTANTS.h"
#include "Yoshi.h"

void Obstacle::draw(sf::RenderWindow &window) {
    window.draw(obstacleSprite);
}

void Obstacle::setPosition(float x, float y) {
    obstacleSprite.setPosition(x, y);
}

void Obstacle::move(float x, float y) {
    obstacleSprite.move(x , y);
}

Rocket::Rocket() {
    if (!obstacleTexture.loadFromFile("../Sprites/rocket.png")) {
        //TODO handle exception
    }
    obstacleSprite.setTexture(obstacleTexture);
    obstacleSprite.setScale(-0.1 , 0.1);
    obstacleSprite.setPosition(SCREENWIDTH + 2, 350);
}

void Rocket::doAction() {
    obstacleSprite.move(-5, 0);
    std::cout<<"wuuuum"<<std::endl;
}


Stone::Stone() {
    if (!obstacleTexture.loadFromFile("../Sprites/stone.png")) {
        //TODO handle exception
    }
    obstacleSprite.setTexture(obstacleTexture);
    obstacleSprite.setScale(0.65 , 0.65);
    obstacleSprite.setPosition(SCREENWIDTH + 2, 150);
    clock.restart();

}

void Stone::doAction() {
    std::cout<<"bzzzzz"<<std::endl;
    if (clock.getElapsedTime().asSeconds()>3.f) {
        //TODO metodo per far "schiacciare" la roccia
        clock.restart();
    }
}
