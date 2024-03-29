//
// Created by danis on 20/12/2020.
//
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#ifndef ENDLESSRUNNER_YOSHI_H
#define ENDLESSRUNNER_YOSHI_H
#include "CONSTANTS.h"
#include "AnimatedSprite.h"

class Form;
class Player{
public:
    Player();
    void draw(sf::RenderWindow &window);
    void move(bool spacePressed) const;
    sf::Vector2f getPosition() const;
    virtual void setPosition(float x, float y);
    sf::FloatRect getGlobalBounds() const;
    void changeForm();
    bool isAlive() const;
    void kill();
    void reset();
    Form *getForm() const;
protected:
    bool alive = true;
private:
    Form* form = nullptr;
    sf::SoundBuffer buffer;
    sf::Sound deathSound;
};

class Form{
public:
    virtual void move(bool spacePressed) = 0;
    virtual void draw(sf::RenderWindow &window) = 0;
    virtual Form* nextForm() = 0;
    virtual ~Form() = default;
    void setPosition(float x, float y);
    const sf::Sprite getSprite() const;
protected:
    sf:: Texture texture;
    AnimatedSprite sprite;
};

class Yoshi : public Form{
public:
    Yoshi();
    Yoshi(float y);
    void move(bool spacePressed) override;
    void draw(sf::RenderWindow &window) override;
    Form* nextForm() override;
    const sf::Clock &getClock() const;
    void resetClock();
private:
    sf::Clock clock;
};

class Bike : public Form{
public:
    Bike(float y);
    void move(bool spacePressed) override;
    void draw(sf::RenderWindow &window) override;
    Form* nextForm() override;
private:
    bool isJumping = false;
    bool hasReachedTop = false;
    bool hasTouchedGround = false;
};

class Giant : public Form{
public:
    Giant(float y);
    void move(bool spacePressed) override;
    void draw(sf::RenderWindow &window) override;
    Form* nextForm() override;
    AnimatedSprite getBodySprite();
    const sf::Sprite &getTongueSprite() const;
private:
    sf:: Texture bodyTexture;
    AnimatedSprite bodySprite;
    sf:: Texture tongueTexture;
    sf:: Sprite tongueSprite;
    sf:: Vector2f startingPosition;
};

class GravityInverter : public Form{
public:
    GravityInverter(float y);
    void move(bool spacePressed) override;
    void draw(sf::RenderWindow &window) override;
    Form* nextForm() override;
    void invertGravity();
private:
    float gravity = 3.2;
};
#endif //ENDLESSRUNNER_YOSHI_H
