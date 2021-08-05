//
// Created by user on 05/08/2021.
//

#ifndef ENDLESSRUNNER_STATEGAME_H
#define ENDLESSRUNNER_STATEGAME_H
#include "State.h"
#include "Game.h"

class StateGame : public State {
public:
    StateGame(Game* gameptr);
    void draw(sf::RenderWindow& window) override;
    void update() override;
    void changeState(State* nextState) override;
private:
    sf::Clock clock;
    float timeNextObstacle = 3.f;
};


#endif //ENDLESSRUNNER_STATEGAME_H
