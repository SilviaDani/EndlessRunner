//
// Created by danis on 20/12/2020.
//
#include <SFML/Graphics.hpp>
#ifndef ENDLESSRUNNER_YOSHI_H
#define ENDLESSRUNNER_YOSHI_H

class Form;
class Player{
public:
    Player();
    void draw(sf::RenderWindow &window); // passo come argomento la finestra che ora è blu
    void move();
    sf::Vector2f getPosition();
    virtual void setPosition(float x, float y);
    sf::Rect<float> getGlobalBounds() const;
    void changeForm();
    Form* form = nullptr; //TODO make it private
};

class Form{
public:
    virtual void move() = 0;
    virtual Form* nextForm() = 0;
    virtual ~Form() = default;
    void setPosition(float x, float y);
protected:
    sf:: Texture texture;
    sf:: Sprite sprite;
public:
    const sf::Sprite &getSprite() const;
};

class Yoshi : public Form{
public:
    Yoshi();
    void move() override;
    Form* nextForm() override;
};

class Bike : public Form{
public:
    Bike();
    void move() override;
    Form* nextForm() override;
private:
    bool isJumping = false;
};

#endif //ENDLESSRUNNER_YOSHI_H
