//
// Created by user on 05/08/2021.
//

#include "StateGame.h"
#include "StateGameOver.h"


StateGame::StateGame(Game* gameptr) {
    game = gameptr;
    clock.restart();
}

void StateGame::update() {
    game->player.move();
    game->map.checkCollisions(game->player);
    game->map.moveBackground();
    game->map.moveLand();
    game->map.moveGrass();
    game->map.instantiatePowerUp(game->player);
    game->map.movePowerUp();
    if (clock.getElapsedTime().asSeconds() > timeNextObstacle) {
        timeNextObstacle = rand()%4 + 2 + (rand()%101)/ 100;
        game->map.instantiateObstacle();
        clock.restart();
    }
    game->map.moveObstacle();
    if (!game->player.isAlive())
        changeState(new StateGameOver(game));
}

void StateGame::draw(sf::RenderWindow& window) {
    game->map.draw(window);
    game->player.draw(window);
}

void StateGame::changeState(State *nextState) {
    State* tmpState = game->getState();
    game->setState(nextState);
    delete tmpState;
}

