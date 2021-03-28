//
// Created by user on 03/03/2021.
//

#ifndef ENDLESSRUNNER_GAME_H
#define ENDLESSRUNNER_GAME_H
#include <iostream>
#include "Player.h"
#include "Map.h"

class Game {
public:
    static Game* getInstance();
    Player player;
    Map map;
    sf::Clock clock;
    void update();
    void draw(sf::RenderWindow &window);
private:
    Game();
static Game* instance;

};


#endif //ENDLESSRUNNER_GAME_H
