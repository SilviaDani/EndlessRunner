//
// Created by danis on 20/12/2020.
//
#include <iostream>
#include "Player.h"
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

sf::Vector2f Player::getPosition() const {
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

void Player::move() const {
    form->move();
}

void Player::changeForm() {
    form = form->nextForm();
}

bool Player::isAlive() const{
    return alive;
}

void Player::kill() {
    Player::alive = false;
}

void Player::reset() {
    if (Yoshi* y = dynamic_cast<Yoshi*>(form)){
        alive = true;
        setPosition(200, LHEIGHT - y->getSprite().getGlobalBounds().height + 2);
        y->resetClock();
    }

}

Form *Player::getForm() const {
    return form;
}


Yoshi::Yoshi(float y) {
    if (!texture.loadFromFile("../Sprites/yoshi.png")) {
        //TODO handle exception
    }
    sprite.setTexture(texture);
    sprite.setPosition(200, y);
    sprite.setScale(3,3);
    resetClock();
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
    int dice = rand()%3; // %n n numero di classi figlie di form - 1(perchè c'è yoshi)
    switch (dice) {
        case 0:
            next = new Bike(sprite.getPosition().y);
            break;
        case 1:
            next = new Giant(sprite.getPosition().y);
            break;
        case 2:
            next = new GravityInverter(sprite.getPosition().y);
            break;
    }
    return next;
}

const sf::Clock &Yoshi::getClock() const {
    return clock;
}

void Yoshi::resetClock() {
    clock.restart();
}


Bike::Bike(float y) {
    if (!texture.loadFromFile("../Sprites/yoshibike.png")) {
        //TODO handle exception
    }
    sprite.setTexture(texture);
    sprite.setPosition(200, y);
    sprite.setScale(3,3);
}

void Bike::move() {
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
    return new Yoshi(sprite.getPosition().y);
}


Giant::Giant(float y) {
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

    if (!texture.loadFromFile("../Sprites/yoshitongue.png")) {
        //TODO handle exception
    }
    sprite.setTexture(texture);
    sprite.setScale(0.4,0.4);
    startingPosition = sf::Vector2f ((bodySprite.getGlobalBounds().width)/2 + (tongueSprite.getGlobalBounds().width)*
                                                                                  sin(acos((LHEIGHT-(sprite.getGlobalBounds().height)/2 - (bodySprite.getPosition().y -
                                                                                                                                           (bodySprite.getGlobalBounds().height)/2 + 4))/tongueSprite.getGlobalBounds().width)) -65, LHEIGHT - sprite.getGlobalBounds().height);
    sprite.setPosition(startingPosition);
}

void Giant::move() {
   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
          if(sprite.getPosition().y > bodySprite.getGlobalBounds().top + 100) {
          sprite.setPosition(sprite.getPosition().x + (sprite.getPosition().y < bodySprite.getGlobalBounds().top + bodySprite.getGlobalBounds().height / 2 ? -0.5f : 0.5f),
                             sprite.getPosition().y - 1.f);
      }
         }
   else{
       if(sprite.getPosition().y < LHEIGHT - sprite.getGlobalBounds().height - 0.5f) {
           sprite.setPosition(sprite.getPosition().x + (sprite.getPosition().y < bodySprite.getGlobalBounds().top + bodySprite.getGlobalBounds().height / 2 ? 0.5f : -0.5f),
                              sprite.getPosition().y + 1.f);
       }else if(sprite.getPosition().y >= LHEIGHT - sprite.getGlobalBounds().height - 0.5f && sprite.getPosition().y < LHEIGHT - sprite.getGlobalBounds().height + 0.5f){
           sprite.setPosition(startingPosition);
       }
   }
//TODO AGGIUSTARE LO SPOSTAMENTO CIRCOLARE
    tongueSprite.setRotation(atan2(((sprite.getPosition().y+sprite.getGlobalBounds().height/2) - tongueSprite.getPosition().y), (sprite.getPosition().x - tongueSprite.getPosition().x)) *180/M_PI);
}

void Giant::draw(sf::RenderWindow &window) {
    window.draw(bodySprite);
    window.draw(tongueSprite);
    window.draw(sprite);
}

Form *Giant::nextForm() {
    return new Yoshi(sprite.getPosition().y);
}

const sf::Sprite &Giant::getTongueSprite() const {
    return tongueSprite;
}

const sf::Sprite &Giant::getBodySprite() const {
    return bodySprite;
}


GravityInverter::GravityInverter(float y) {
    if (!texture.loadFromFile("../Sprites/spaceyoshi.png")) {
        //TODO handle exception
    }
    sprite.setTexture(texture);
    sprite.setPosition(200, y);
    sprite.setScale(0.3,0.3);
    sprite.setOrigin(sprite.getOrigin().x, sprite.getOrigin().y + sprite.getLocalBounds().height/2);
}

void GravityInverter::move() {
    sprite.move(0, gravity);
}

void GravityInverter::invertGravity() {
    gravity *= -1;
    sprite.setScale(sprite.getScale().x,-sprite.getScale().y);
}

void GravityInverter::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}

Form *GravityInverter::nextForm() {
    return new Yoshi();
}



