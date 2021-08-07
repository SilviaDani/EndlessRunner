//
// Created by user on 03/03/2021.
//

#ifndef ENDLESSRUNNER_GAME_H
#define ENDLESSRUNNER_GAME_H
#include <iostream>
#include "Player.h"
#include "Map.h"
#include "Achievement.h"
#include "State.h"

class State;

class Game {
public:
    static Game* getInstance();
    void update();
    void draw(sf::RenderWindow &window);
    void save();
    void load();
    AchievementManager *getAm() const;
    State *getState() const;
    void setState(State *state);
    Player& getPlayer();
    Map &getMap();
    sf::Window *getWindow() const;
    void setWindow(sf::Window *window);
private:
    Game();
    Player player;
    Map map;
    sf::Window* window;
    State* state;
    static Game* instance;
    AchievementManager* am;
};


#endif //ENDLESSRUNNER_GAME_H
