//
// Created by user on 05/08/2021.
//

#include "StateGame.h"
#include "StateGameOver.h"


StateGame::StateGame(Game* gameptr) {
    game = gameptr;
    clock.restart();
    coinClock.restart();

    try {
        if (!buffer.loadFromFile("./Sounds/gameMusic.wav"))
            throw std::runtime_error("File not found: ./Sounds/gameMusic.wav");
        gameMusic.setBuffer(buffer);
        gameMusic.setLoop(true);
    }
    catch (const std::runtime_error& exc) {
        std::cerr << exc.what() << std::endl;
        exit(-1);
    }
}

void StateGame::update() {
    game->getPlayer().move(isSpacePressed());
    game->getMap().checkCollisions(game->getPlayer());
    game->getMap().moveBackground();
    game->getMap().moveLand();
    game->getMap().moveGrass();
    game->getMap().instantiatePowerUp(game->getPlayer());
    game->getMap().movePowerUp();
    acceleration = 1/(game->getMap().getClock().getElapsedTime().asSeconds()/20 + 1);
    if (clock.getElapsedTime().asSeconds() > (timeNextObstacle * acceleration)) {
        timeNextObstacle = rand()%4 + 2 + (rand()%101)/ 100;
        game->getMap().instantiateObstacle();
        clock.restart();
    }
   game->getMap().moveObstacle();
    if (coinClock.getElapsedTime().asSeconds() >= (coinTime * acceleration)){
        coinTime = rand()%4 + 2 + (rand()%101)/ 100;
        game->getMap().instantiateCoin();
        coinClock.restart();
    }
    game->getMap().moveCoin();
    if (!game->getPlayer().isAlive()) {
        game->getState()->stopMusic();
        changeState(new StateGameOver(game));
    }
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

float StateGame::getAcceleration() const {
    return acceleration;
}

void StateGame::playMusic() {
    gameMusic.play();
}

void StateGame::stopMusic() {
    gameMusic.stop();
}

bool StateGame::isSpacePressed() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        return true;
    else
        return false;
}



