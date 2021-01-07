//
// Created by danis on 20/12/2020.
//
#include <iostream>
#include "Yoshi.h"

Yoshi::Yoshi() {
    if (!texture.loadFromFile("../Sprites/yoshi.png")) {
        //TODO handle exception
    }
    sprite.setTexture(texture);
    sprite.setPosition(200, 400);
    sprite.setScale(3,3);
}

void Yoshi::draw(sf::RenderWindow &window) {
window.draw(sprite);
}

void Yoshi::move() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        sprite.move(0, 3);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        sprite.move(0, -3);
    }
}

void Yoshi::printPosition() {
std::cout<<"posX:"<<sprite.getPosition().x<<" posY:"<<sprite.getPosition().y<<std::endl;
}
