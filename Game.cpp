//
// Created by user on 03/03/2021.
//

#include <fstream>
#include "Game.h"
#include "Player.h"
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
    //highscore, total covered distance, //TODO total runs played
    std::ofstream saveFile("../saves.txt");
    if (saveFile.is_open()){
        saveFile << map.getHighscore() << ",";
        saveFile << map.getTotalDistance() << ",";
        saveFile << am->getAchUnlocked().size() << ",";
        for (auto i : am->getAchUnlocked()){
            std::string title = i->getTitle().getString();
            saveFile << title << ",";
        }
    }
    saveFile.close();
}

void Game::load() {
    if (std::ifstream("../saves.txt").good()){
        std::ifstream saveFile ("../saves.txt");
        if(saveFile.is_open()){
            std::string highscoreString, totalDistanceString, nAchievementsString;
            std::getline(saveFile, highscoreString, ',');
            std::getline(saveFile, totalDistanceString, ',');
            std::getline(saveFile, nAchievementsString, ',');
            map.setHighscore(std::stoi(highscoreString));
            map.setTotalDistance(std::stoi(totalDistanceString));
            int nAchievements = std::stoi(nAchievementsString);
            for (int i = 0; i<nAchievements; i++){
                std::string currentAchString;
                std::getline(saveFile, currentAchString, ',');
                Achievement* ach = new Achievement(currentAchString, "");
                ach->unlock();
                am->setAchUnlocked(ach);
            }
        }
    }
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




