//
// Created by danis on 20/12/2020.
//
#include <iostream>
#include "Yoshi.h"
#include "CONSTANTS.h"

Yoshi::Yoshi() {
    if (!texture.loadFromFile("../Sprites/yoshi.png")) {
        //TODO handle exception
    }
    sprite.setTexture(texture);
    sprite.setPosition(200, LHEIGHT - sprite.getGlobalBounds().height + 2);
    sprite.setScale(3,3);
}


void Yoshi::draw(sf::RenderWindow &window) {
window.draw(sprite);
}

void Yoshi::move() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        sprite.move(0, -3.2);
    else
        sprite.move(0, 3.6);
}

sf::Vector2f Yoshi::getPosition() {
    return sprite.getPosition();
}

void Yoshi::printPosition() {
    std::cout<<"posX:"<<sprite.getPosition().x<<" posY:"<<sprite.getPosition().y<<std::endl;
}

void Yoshi::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

sf::Rect<float> Yoshi::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}





