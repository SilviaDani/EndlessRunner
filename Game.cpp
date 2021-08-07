//
// Created by user on 03/03/2021.
//

#include <fstream>
#include "Game.h"
#include "Player.h"
#include "StateGame.h"
#include "StateMainMenu.h"

Game* Game::instance = nullptr;

Game::Game() {
    am = new AchievementManager();
    map.addObserver(am);
    state = new StateMainMenu(this);
}

Game* Game::getInstance(){
    if (instance == nullptr)
        instance = new Game();
    return instance;
}

void Game::update() {
  state->update();
}

void Game::draw(sf::RenderWindow &window) {
    state->draw(window);
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

AchievementManager *Game::getAm() const {
    return am;
}

State *Game::getState() const {
    return state;
}

void Game::setState(State *state) {
    Game::state = state;
}

Player& Game::getPlayer() {
    return player;
}

Map& Game::getMap() {
    return map;
}

void Game::setWindow(sf::Window *window) {
    Game::window = window;
}

sf::Window *Game::getWindow() const {
    return window;
}


