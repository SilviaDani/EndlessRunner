//
// Created by danis on 20/12/2020.
//
#include <SFML/Graphics.hpp>
#ifndef ENDLESSRUNNER_YOSHI_H
#define ENDLESSRUNNER_YOSHI_H


class Yoshi {
public:
    Yoshi();
    void draw(sf::RenderWindow &window); // passo come argomento la finestra che ora è blu
    void move();
    sf::Vector2f getPosition();
    void setPosition(float x, float y);
    sf::Rect<float> getGlobalBounds() const;
    void printPosition();

private:
    sf:: Texture texture;
    sf:: Sprite sprite;
};


#endif //ENDLESSRUNNER_YOSHI_H
