//
// Created by danis on 20/12/2020.
//
#include <iostream>
#include "Player.h"
#include "CONSTANTS.h"
#include <math.h>

Player::Player() {
    form = new Yoshi();
}

const sf::Sprite &Form::getSprite() const {
    return sprite;
}

void Player::draw(sf::RenderWindow &window) {
form->draw(window);
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

void Yoshi::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}

Form *Yoshi::nextForm() {
    Form* next = nullptr;
    int dice = rand()%1; //TODO %n n numero di classi figlie di form - 1(perchè c'è yoshi)
    switch (dice) {
        /*case 0:
            next = new Bike(sprite.getPosition().y);
            break;*/
        case 0:
            next = new Giant(sprite.getPosition().y);
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

void Bike::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}

Form *Bike::nextForm() {
    return new Yoshi();
}


Giant::Giant(float y) {
    if (!texture.loadFromFile("../Sprites/yoshitongue.png")) {
        //TODO handle exception
    }
    sprite.setTexture(texture);
    sprite.setPosition(300, y);
    sprite.setOrigin((sprite.getGlobalBounds().width)/2, (sprite.getGlobalBounds().height)/2);
    sprite.setScale(0.4,0.4);

    if (!bodyTexture.loadFromFile("../Sprites/bigyoshi.png")) {
        //TODO handle exception
    }
    bodySprite.setTexture(bodyTexture);
    bodySprite.setOrigin(0, bodySprite.getLocalBounds().height - 2);
    bodySprite.setPosition(-100, LHEIGHT);
    bodySprite.setScale(0.4, 0.4);

    if (!tongueTexture.loadFromFile("../Sprites/yoshitongue2.png")) {
        //TODO handle exception
    }
    tongueSprite.setTexture(tongueTexture);
    tongueSprite.setOrigin(0, (tongueSprite.getLocalBounds().height)/2);
    tongueSprite.setScale(1, 0.5);
    tongueSprite.setPosition((bodySprite.getGlobalBounds().width)/2 - 8, bodySprite.getPosition().y - (bodySprite.getGlobalBounds().height)/2 + 4);
}

void Giant::move() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        sprite.move(0, -2.5);
    else
        sprite.move(0, 3.6);
    tongueSprite.setRotation(atan2((sprite.getPosition().y - tongueSprite.getPosition().y), (sprite.getPosition().x - tongueSprite.getPosition().x)) *180/M_PI);
}

void Giant::draw(sf::RenderWindow &window) {
    window.draw(bodySprite);
    window.draw(tongueSprite);
    window.draw(sprite);
}

Form *Giant::nextForm() {
    return new Yoshi;
}
