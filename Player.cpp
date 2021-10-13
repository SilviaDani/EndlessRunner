//
// Created by danis on 20/12/2020.
//

#include <iostream>
#include "Player.h"
#include "Game.h"
#include "StateGame.h"
#include <math.h>

Player::Player() {
    form = new Yoshi();
    try {
        if (!buffer.loadFromFile("../Sounds/deathSound.wav"))
            throw std::runtime_error("File not found: ../Sounds/deathSound.wav");
        deathSound.setBuffer(buffer);
        deathSound.setLoop(false);
    }
    catch (const std::runtime_error& exc) {
        std::cerr << exc.what() << std::endl;
        exit(-1);
    }
}

const sf::Sprite Form::getSprite() const {
    return sprite.getSprite();
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

sf::FloatRect Player::getGlobalBounds() const {
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
    deathSound.play();
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
    try {
        if (!texture.loadFromFile("../Sprites/yoshi.png")) {
            throw std::runtime_error("File not found: ../Sprites/yoshi.png");
        }
    }
    catch (const std::runtime_error& exc) {
        std::cerr << exc.what() << std::endl;
        exit(-1);
    }
    int nFrames = 2;
    int nRows = 2;
    sprite = AnimatedSprite(texture, texture.getSize().y/nRows, texture.getSize().x/nFrames, nFrames);
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
    if(StateGame* sg = dynamic_cast<StateGame*>(Game::getInstance()->getState())){
        if (sprite.getPosition().y >= LHEIGHT - sprite.getGlobalBounds().height - 3){
            sprite.draw(window, 9/sg->getAcceleration(), 0);
        }
        else
            sprite.draw(window, 9/sg->getAcceleration(), 1);
    }

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


Yoshi::Yoshi() {
    try {
        if (!texture.loadFromFile("../Sprites/yoshi.png")) {
            throw std::runtime_error("File not found: ../Sprites/yoshi.png");
        }
    }
    catch (const std::runtime_error& exc) {
        std::cerr << exc.what() << std::endl;
        exit(-1);
    }
    int nFrames = 2;
    int nRows = 2;
    sprite = AnimatedSprite(texture, texture.getSize().y/nRows, texture.getSize().x/nFrames, nFrames);
    sprite.setPosition(200, LHEIGHT - sprite.getGlobalBounds().height + 2);
    sprite.setScale(3,3);
    resetClock();
}


Bike::Bike(float y) {
    try {
        if (!texture.loadFromFile("../Sprites/yoshibike.png")) {
            throw std::runtime_error("File not found: ../Sprites/yoshibike.png");
        }
    }
    catch (const std::runtime_error& exc) {
        std::cerr << exc.what() << std::endl;
        exit(-1);
    }
    int nFrames = 2;
    sprite = AnimatedSprite(texture, texture.getSize().y, texture.getSize().x/nFrames, nFrames);
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
    if(StateGame* sg = dynamic_cast<StateGame*>(Game::getInstance()->getState())){
        sprite.draw(window, 10/sg->getAcceleration());
    }
}

Form *Bike::nextForm() {
    return new Yoshi(sprite.getPosition().y);
}


Giant::Giant(float y) {
    try {
        if (!bodyTexture.loadFromFile("../Sprites/bigyoshi.png")) {
            throw std::runtime_error("File not found: ../Sprites/bigyoshi.png");
        }
    }
    catch (const std::runtime_error& exc) {
        std::cerr << exc.what() << std::endl;
        exit(-1);
    }
    int nFrames = 3;
    bodySprite = AnimatedSprite(bodyTexture, bodyTexture.getSize().y, bodyTexture.getSize().x/nFrames, nFrames);
    bodySprite.setOrigin(0, bodySprite.getLocalBounds().height - 2);
    bodySprite.setPosition(-93, LHEIGHT - 27);
    bodySprite.setScale(14, 14);


    try {
        if (!tongueTexture.loadFromFile("../Sprites/yoshitongue2.png")) {
            throw std::runtime_error("File not found: ../Sprites/yoshitongue2.png");
        }
    }
    catch (const std::runtime_error& exc) {
        std::cerr << exc.what() << std::endl;
        exit(-1);
    }
    tongueSprite.setTexture(tongueTexture);
    tongueSprite.setOrigin(0, (tongueSprite.getLocalBounds().height)/2);
    tongueSprite.setScale(1, 0.5);
    tongueSprite.setPosition((bodySprite.getGlobalBounds().width)/2 - 8, bodySprite.getPosition().y - (bodySprite.getGlobalBounds().height)/2 + 4);


    try {
        if (!texture.loadFromFile("../Sprites/yoshitongue.png")) {
            throw std::runtime_error("File not found: ../Sprites/yoshitongue.png");
        }
    }
    catch (const std::runtime_error& exc) {
        std::cerr << exc.what() << std::endl;
        exit(-1);
    }
    sprite = AnimatedSprite(texture, texture.getSize().y, texture.getSize().x, 1);
    sprite.setScale(0.4,0.4);
    startingPosition = sf::Vector2f ((bodySprite.getGlobalBounds().width)/2 + (tongueSprite.getGlobalBounds().width)*
                                                                                  sin(acos((LHEIGHT-(sprite.getGlobalBounds().height)/2 - (bodySprite.getPosition().y -
                                                                                                                                           (bodySprite.getGlobalBounds().height)/2 + 4))/tongueSprite.getGlobalBounds().width)) -65, LHEIGHT - sprite.getGlobalBounds().height);
    sprite.setPosition(startingPosition);
}

void Giant::move() {
   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
          if (sprite.getPosition().y > bodySprite.getGlobalBounds().top + 100) {
          sprite.setPosition(sprite.getPosition().x + (sprite.getPosition().y < bodySprite.getGlobalBounds().top + bodySprite.getGlobalBounds().height / 2 ? -0.5f : 0.5f),
                             sprite.getPosition().y - 1.f);
      }
         }
   else{
       if (sprite.getPosition().y < LHEIGHT - sprite.getGlobalBounds().height - 0.5f) {
           sprite.setPosition(sprite.getPosition().x + (sprite.getPosition().y < bodySprite.getGlobalBounds().top + bodySprite.getGlobalBounds().height / 2 ? 0.5f : -0.5f),
                              sprite.getPosition().y + 1.f);
       }else if (sprite.getPosition().y >= LHEIGHT - sprite.getGlobalBounds().height - 0.5f && sprite.getPosition().y < LHEIGHT - sprite.getGlobalBounds().height + 0.5f){
           sprite.setPosition(startingPosition);
       }
   }
    tongueSprite.setRotation(atan2(((sprite.getPosition().y+sprite.getGlobalBounds().height/2) - tongueSprite.getPosition().y), (sprite.getPosition().x - tongueSprite.getPosition().x)) *180/M_PI);
}

void Giant::draw(sf::RenderWindow &window) {
    if(StateGame* sg = dynamic_cast<StateGame*>(Game::getInstance()->getState())){
        bodySprite.draw(window, 2/sg->getAcceleration());
    }
    window.draw(tongueSprite);
    sprite.draw(window, 1);
}

Form *Giant::nextForm() {
    return new Yoshi(sprite.getPosition().y);
}

const sf::Sprite &Giant::getTongueSprite() const {
    return tongueSprite;
}

AnimatedSprite Giant::getBodySprite(){
    return bodySprite;
}


GravityInverter::GravityInverter(float y) {
    try {
        if (!texture.loadFromFile("../Sprites/spaceyoshi.png")) {
            throw std::runtime_error("File not found: ../Sprites/spaceyoshi.png");
        }
    }
    catch (const std::runtime_error& exc) {
        std::cerr << exc.what() << std::endl;
        exit(-1);
    }
    int nFrames = 2;
    int nRows = 2;
    sprite = AnimatedSprite(texture, texture.getSize().y/nRows, texture.getSize().x/nFrames, nFrames);
    sprite.setPosition(200, y);
    sprite.setScale(3,3);
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
    if(StateGame* sg = dynamic_cast<StateGame*>(Game::getInstance()->getState())){
        if (sprite.getPosition().y >= LHEIGHT - sprite.getGlobalBounds().height - 3 && gravity > 0 ||
            sprite.getPosition().y <= sprite.getGlobalBounds().height + 3 && gravity < 0){
            sprite.draw(window, 9/sg->getAcceleration(), 1);
        }
        sprite.draw(window,5, 0);
    }
}

Form *GravityInverter::nextForm() {
    return new Yoshi(sprite.getPosition().y);
}



