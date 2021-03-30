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


Yoshi::Yoshi(float y) {
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
            next = new Bike(sprite.getPosition().y);
            break;
    }
    return next;
}

Bike::Bike(float y) {
    if (!texture.loadFromFile("../Sprites/yoshibike.png")) {
        //TODO handle exception
    }
    sprite.setTexture(texture);
    sprite.setPosition(200, y);
    sprite.setScale(3,3);
    // TODO regolare setPosition in modo che parta da dove ha preso il power up
}

void Bike::move() { //TODO mettere condizioni più stringenti sugli if
    if (sprite.getPosition().y > LHEIGHT - sprite.getGlobalBounds().height - 2)
        hasTouchedGround = true;
    if (!hasTouchedGround)
        sprite.move(0, 8);
    if (!isJumping && sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && hasTouchedGround) {
        isJumping = true;
        hasReachedTop = false;
    }
    if (isJumping) {
        if (sprite.getPosition().y > MAXJUMP && !hasReachedTop)
            sprite.move(0, -4);
        else if (sprite.getPosition().y < LHEIGHT - sprite.getGlobalBounds().height - 2) {
            hasReachedTop = true;
            sprite.move(0, 4);
        }
        else if (sprite.getPosition().y >= LHEIGHT - sprite.getGlobalBounds().height - 2)
            isJumping = false;
    }
}

Form *Bike::nextForm() {
    return new Yoshi();
}


