//
// Created by user on 05/08/2021.
//

#include "StateGame.h"
#include "StateGameOver.h"


StateGame::StateGame(Game* gameptr) {
    game = gameptr;
    clock.restart();
    coinClock.restart();
}

void StateGame::update() {
    game->getPlayer().move();
    game->getMap().checkCollisions(game->getPlayer());
    game->getMap().moveBackground();
    game->getMap().moveLand();
    game->getMap().moveGrass();
    game->getMap().instantiatePowerUp(game->getPlayer());
    game->getMap().movePowerUp();
    if (clock.getElapsedTime().asSeconds() > timeNextObstacle) {
        timeNextObstacle = rand()%4 + 2 + (rand()%101)/ 100;
        game->getMap().instantiateObstacle();
        clock.restart();
    }
    game->getMap().moveObstacle();
    if (coinClock.getElapsedTime().asSeconds() >= coinTime){
        coinTime = rand()%4 + 2 + (rand()%101)/ 100;
        game->getMap().instantiateCoin();
        coinClock.restart();
    }
    game->getMap().moveCoin();
    if (!game->getPlayer().isAlive())
        changeState(new StateGameOver(game));
}

void StateGame::draw(sf::RenderWindow& window) {
    game->getMap().draw(window);
    game->getPlayer().draw(window);
}

void StateGame::changeState(State *nextState) {
    State* tmpState = game->getState();
    game->setState(nextState);
    delete tmpState;
}

