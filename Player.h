//
// Created by danis on 20/12/2020.
//
#include <SFML/Graphics.hpp>
#ifndef ENDLESSRUNNER_YOSHI_H
#define ENDLESSRUNNER_YOSHI_H
#include "CONSTANTS.h"

class Form;
class Player{
public:
    Player();
    void draw(sf::RenderWindow &window);
    void move() const;
    sf::Vector2f getPosition() const;
    virtual void setPosition(float x, float y);
    sf::Rect<float> getGlobalBounds() const;
    void changeForm();
    bool isAlive() const;
    void kill();
    void reset();
    Form *getForm() const;
protected:
    bool alive = true;
private:
    Form* form = nullptr;
};

class Form{
public:
    virtual void move() = 0;
    virtual void draw(sf::RenderWindow &window) = 0;
    virtual Form* nextForm() = 0;
    virtual ~Form() = default;
    void setPosition(float x, float y);
    const sf::Sprite &getSprite() const;
protected:
    sf:: Texture texture;
    sf:: Sprite sprite;
};

class Yoshi : public Form{
public:
    Yoshi(float y = LHEIGHT + 500); //TODO settare la posizione post mortem con power up
    void move() override;
    void draw(sf::RenderWindow &window) override;
    Form* nextForm() override;
    const sf::Clock &getClock() const;
    void resetClock();
private:
    sf::Clock clock;
    float y = LHEIGHT - sprite.getGlobalBounds().height + 2;
};

class Bike : public Form{
public:
    Bike(float y);
    void move() override;
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
    void move() override;
    void draw(sf::RenderWindow &window) override;
    Form* nextForm() override;
    const sf::Sprite &getBodySprite() const;
    const sf::Sprite &getTongueSprite() const;
private:
    sf:: Texture bodyTexture;
    sf:: Sprite bodySprite;
    sf:: Texture tongueTexture;
    sf:: Sprite tongueSprite;
    sf:: Vector2f startingPosition;
};

class GravityInverter : public Form{
public:
    GravityInverter(float y);
    void move() override;
    void draw(sf::RenderWindow &window) override;
    Form* nextForm() override;
    void invertGravity();
private:
    float gravity = 3.2;
};
#endif //ENDLESSRUNNER_YOSHI_H
