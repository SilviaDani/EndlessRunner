//
// Created by user on 05/08/2021.
//

#ifndef ENDLESSRUNNER_STATE_H
#define ENDLESSRUNNER_STATE_H
#include <SFML/Graphics.hpp>
#include "Game.h"


class Game;

class State {
public:
    virtual ~State() = default;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void update() = 0;
    virtual void changeState(State* nextState) = 0;
    virtual void playMusic() = 0;
    virtual void stopMusic() = 0;
protected:
    Game* game;
};


#endif //ENDLESSRUNNER_STATE_H
