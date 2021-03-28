//
// Created by danis on 20/12/2020.
//
#include <iostream>
#include "Player.h"
#include "CONSTANTS.h"

Player::Player() {
    form = new Yoshi();
}

const sf::Sprite &Form::getSprite() const {
    return sprite;
}

void Player::draw(sf::RenderWindow &window) {
window.draw(form->getSprite());
}


sf::Vector2f Player::getPosition() {
    return form->getSprite().getPosition();
}

void Player::setPosition(float x, float y) {
    form->setPosition(x, y);
}

void Form::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

sf::Rect<float> Player::getGlobalBounds() const {
    return form->getSprite().getGlobalBounds();
}

void Player::move() {
    form->move();
}

void Player::changeForm() {
    form = form->nextForm();
}


Yoshi::Yoshi() {
    if (!texture.loadFromFile("../Sprites/yoshi.png")) {
        //TODO handle exception
    }
    sprite.setTexture(texture);
    sprite.setPosition(200, LHEIGHT - sprite.getGlobalBounds().height + 2);
    sprite.setScale(3,3);
}

void Yoshi::move() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        sprite.move(0, -3.2);
    else
        sprite.move(0, 3.6);
}

Form *Yoshi::nextForm() {
    Form* next = nullptr;
    int dice = rand()%1; //TODO %n n numero di classi figlie di form - 1(perchè c'è yoshi)
    switch (dice) {
        case 0:
            next = new Bike();
            break;
    }
    return next;
}

Bike::Bike() {
    if (!texture.loadFromFile("../Sprites/yoshibike.png")) {
        //TODO handle exception
    }
    sprite.setTexture(texture);
    sprite.setPosition(200, LHEIGHT - sprite.getGlobalBounds().height + 2);
    sprite.setScale(3,3);
    // TODO regolare setPosition in modo che parta da dove ha preso il power up
}

void Bike::move() { //TODO correggi codice
    if (!isJumping && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        std::cout<<"yyyyyyyyyyyyyyyyy"<<std::endl;
        if (sprite.getPosition().y > MAXJUMP) {
            sprite.move(0, -4);
           // isJumping = true;
        }
        else if (sprite.getPosition().y <= MAXJUMP)
            sprite.move(0, 4);

    }
}

Form *Bike::nextForm() {
    return new Yoshi();
}


