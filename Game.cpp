//
// Created by user on 03/03/2021.
//

#include <fstream>
#include "Game.h"
#include "Player.h"

Game* Game::instance = nullptr;

Game::Game() {
    clock.restart();
    am = new AchievementManager();
    map.addObserver(am);
}

Game* Game::getInstance(){
    if (instance == nullptr)
    {
        instance = new Game();
    }
    return instance;
}

void Game::update() {
    player.move();
    map.checkCollisions(player);
    map.moveBackground();
    map.moveLand();
    map.moveGrass();
    map.instantiatePowerUp(player);
    map.movePowerUp();
    if (clock.getElapsedTime().asSeconds() > 3.f) {
        map.instantiateObstacle();
        clock.restart();
    }
    map.moveObstacle();

    //player.printPosition();
}

void Game::draw(sf::RenderWindow &window) {
    map.draw(window);
    player.draw(window);
    am->draw(window);
}

void Game::save() {
    //highscore, total covered distance, //TODO total runs played, unlocked achievements
    std::ofstream saveFile("../saves.txt");
    if (saveFile.is_open()){
        saveFile << map.getHighscore() << ",";
        saveFile << map.getTotalDistance() << ",";
    }
    saveFile.close();
}


